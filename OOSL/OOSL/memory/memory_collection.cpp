#include "memory_collection.h"

oosl::memory::collection::collection()
	: states_(state_type::nil), protected_(0u), next_address_(1u){}

void oosl::memory::collection::enter_protected_mode(){
	++protected_mode_count;
}

void oosl::memory::collection::leave_protected_mode(){
	if (protected_mode_count > 0u)
		--protected_mode_count;
}

bool oosl::memory::collection::is_protected_mode(){
	return (protected_mode_count > 0u);
}

void oosl::memory::collection::protect(uint64_type address_){
	if (address_ == 0u){
		protected_ = next_address_;
		++next_address_;
	}
	else if (next_address_ == 1u){
		protected_ = address_;
		next_address_ = (address_ + 1);
	}
}

bool oosl::memory::collection::is_protected(uint64_type address){
	return (!is_protected_mode() && (address <= protected_));
}

void oosl::memory::collection::add_watcher(const range_type &range, watcher_ptr_type watcher){
	auto entry = watcher_collection_map_.find(range);
	if (entry == watcher_collection_map_.end())//Add new
		entry = watcher_collection_map_.try_emplace(range, range).first;
	entry->second.add(watcher);//Insert
}

void oosl::memory::collection::remove_watcher(const range_type &range, watcher_type &watcher){
	auto entry = watcher_collection_map_.find(range);
	if (entry != watcher_collection_map_.end())
		entry->second.remove(watcher);//Remove
}

void oosl::memory::collection::remove_watcher(watcher_type &watcher){
	for (auto &entry : watcher_collection_map_)
		entry.second.remove(watcher);
}

void oosl::memory::collection::deallocate(const block_id_type &id, deallocation_option options){
	lock_.lock();
	try{
		if (id.size == 0u)//Constant block
			constant_collection_.deallocate(id.address);
		else//Deallocate
			deallocate_(id.address, options);
	}
	catch (...){
		lock_.unlock();
	}
}

oosl::memory::collection::uint64_type oosl::memory::collection::reserve(size_type size){
	lock_guard_type lock_guard(lock_);
	return reserve_(size);
}

oosl::memory::collection::block_type *oosl::memory::collection::allocate(size_type size, uint64_type address_hint){
	lock_guard_type lock_guard(lock_);
	return allocate_(size, address_hint);
}

oosl::memory::collection::block_type *oosl::memory::collection::allocate_contiguous(size_type count, size_type size){
	lock_guard_type lock_guard(lock_);
	return allocate_contiguous_(count, size);
}

oosl::memory::collection::block_type *oosl::memory::collection::allocate_linked(size_type size, const block_id_type &target_id, uint64_type address_hint){
	lock_guard_type lock_guard(lock_);
	return allocate_linked_(size, target_id, address_hint);
}

oosl::memory::collection::block_type *oosl::memory::collection::reallocate(uint64_type address, size_type size){
	lock_guard_type lock_guard(lock_);
	return reallocate_(address, size);
}

oosl::memory::collection::block_type *oosl::memory::collection::duplicate_string(const block_id_type &target_id, uint64_type address_hint){
	lock_guard_type lock_guard(lock_);
	return duplicate_string_(target_id, address_hint);
}

void oosl::memory::collection::fill(uint64_type address, char source, size_type count){
	writing_([=](watcher_info_list_type &watcher_list){
		shared_lock_guard_type lock_guard(lock_);
		fill_(address, source, count, watcher_list);
	});
}

void oosl::memory::collection::copy(uint64_type destination, const block_id_type &source, size_type size){
	writing_([=](watcher_info_list_type &watcher_list){
		shared_lock_guard_type lock_guard(lock_);
		copy_(destination, source, size, watcher_list);
	});
}

void oosl::memory::collection::write(uint64_type destination, const char *source, size_type size){
	writing_([=](watcher_info_list_type &watcher_list){
		shared_lock_guard_type lock_guard(lock_);
		write_(destination, source, size, true, watcher_list);
	});
}

void oosl::memory::collection::read(const block_id_type &source, char *destination, size_type size){
	shared_lock_guard_type lock_guard(lock_);
	read_(source, destination, size);
}

oosl::memory::collection::block_type *oosl::memory::collection::find(const block_id_type &id){
	shared_lock_guard_type lock_guard(lock_);
	return find_(id);
}

oosl::memory::collection::block_type *oosl::memory::collection::find_nearest(uint64_type address){
	shared_lock_guard_type lock_guard(lock_);
	return find_nearest_(address);
}

thread_local oosl::memory::collection::size_type oosl::memory::collection::protected_mode_count = 0u;

void oosl::memory::collection::add_available_(uint64_type value, size_type size){
	if (size == 0u)
		return;

	auto entry = available_.begin();
	for (; entry != available_.end(); ++entry){
		if ((entry->first + entry->second) == value)
			break;//Previous in sequence
	}

	if (entry != available_.end()){//Merge with previous
		entry->second += size;
		value = entry->first;
		size = entry->second;
	}

	auto next = available_.find(value + size);
	if (next != available_.end()){//Merge with next
		entry->second += next->second;
		available_.erase(next);
	}
	else//Add entry
		available_[value] = size;

	if (!available_.empty()){
		auto last = std::prev(available_.end());
		if ((last->first + last->second) == next_address_){//Move next address backwards
			next_address_ = last->first;
			available_.erase(last);
		}
	}
}

oosl::memory::collection::uint64_type oosl::memory::collection::find_available_(size_type size, uint64_type match){
	for (auto &entry : available_){
		if (match != 0ull && entry.first != match){
			if (match < entry.first)
				break;
			continue;
		}

		if (size < entry.second){//Use required
			available_[entry.first + size] = (entry.second - size);
			return entry.first;
		}

		if (size == entry.second)
			return entry.first;
	}

	return 0ull;
}

void oosl::memory::collection::deallocate_(uint64_type address, deallocation_option options){
	auto entry = find_raw_(address);
	if (entry == map_.end()){//Invalid address
		if (!OOSL_IS(options, deallocation_option::no_throw))
			throw error_code_type::invalid_address;
		return;//Do nothing
	}

	if (entry->second.ref_count > 0u && --entry->second.ref_count > 0u)
		return;//Block is still referenced

	auto extra = entry->second.extra;//Defer destruction of extra object
	if (!OOSL_IS(options, deallocation_option::no_merge))//Add to available list
		add_available_(address, entry->second.actual_size);

	map_.erase(entry);
	lock_.unlock();
}

oosl::memory::collection::uint64_type oosl::memory::collection::reserve_(size_type size){
	if (size == 0u)
		return 0ull;

	auto address = find_available_(size);
	if (address == 0ull){//Use next value
		if ((std::numeric_limits<uint64_type>::max() - size) < address)
			throw error_code_type::out_of_memory;//Out of address space

		address = next_address_;
		next_address_ += size;
	}
	else//Remove from list
		available_.erase(address);

	return address;
}

oosl::memory::collection::block_type *oosl::memory::collection::allocate_block_(size_type size, uint64_type address){
	try{
		size_type actual_size = ((size == 0u) ? 1u : size);
		block_type block{
			1u,										//Reference count
			address,								//Address
			size,									//Size
			actual_size,							//Actual size -- 0 for constant block
			std::make_unique<char[]>(actual_size)	//Data
		};

		if (block.data.get() != nullptr)//Add entry
			return &(map_[block.address] = std::move(block));
	}
	catch (...){}

	throw error_code_type::out_of_memory;
}

oosl::memory::collection::block_type *oosl::memory::collection::allocate_(size_type size, uint64_type address_hint){
	if (map_.max_size() <= map_.size())
		throw error_code_type::out_of_memory;//Out of address space

	auto merge = false;
	auto actual_size = ((size == 0u) ? 1u : size);

	if (address_hint == 0ull){//Determine address
		merge = true;
		if ((address_hint = find_available_(actual_size)) == 0ull){//Use next address
			if ((std::numeric_limits<uint64_type>::max() - actual_size) < address_hint)
				throw error_code_type::out_of_memory;//Out of address space

			address_hint = next_address_;
			next_address_ += actual_size;
		}
		else//Remove from list
			available_.erase(address_hint);
	}
	else if (is_protected(address_hint))
		throw error_code_type::protected_address;
	else if (find_nearest_(address_hint) != nullptr)
		throw error_code_type::invalid_address;

	try{
		return allocate_block_(size, address_hint);
	}
	catch (...){
		if (merge)//Return address to available list
			add_available_(address_hint, actual_size);
		throw;//Forward exception
	}

	return nullptr;
}

oosl::memory::collection::block_type *oosl::memory::collection::allocate_contiguous_(size_type count, size_type size){
	if (count == 0u)
		return nullptr;

	auto actual_size = ((size == 0u) ? 1u : size);
	auto address = reserve_(actual_size * count);

	auto start_value = address;
	std::vector<block_type *> blocks(size);

	for (auto i = 0u; i < count; ++i, address += actual_size){
		try{//Guard allocation
			blocks[i] = allocate_(size, address);
		}
		catch (...){
			for (auto j = 0u; j < i; ++j)//Rollback
				deallocate_(blocks[j]->address, deallocation_option::no_merge);

			add_available_(start_value, actual_size * count);
			throw;//Forward exception
		}
	}

	return *blocks.begin();
}

oosl::memory::collection::block_type *oosl::memory::collection::allocate_linked_(size_type size, const block_id_type &target_id, uint64_type address_hint){
	auto block = allocate_(size, address_hint);
	block->extra = std::make_shared<linked_block_type>(*this, target_id);
	return block;
}

oosl::memory::collection::block_type *oosl::memory::collection::reallocate_(uint64_type address, size_type size){
	auto block = find_nearest_(address);
	if (block == nullptr)
		throw error_code_type::invalid_address;

	if (block->size < size){//Expand
		if (block->actual_size < size){//Reallocate
			data_type old_data = std::move(block->data);
			auto old_size = block->actual_size;

			deallocate_(block->address, deallocation_option::nil);
			block = allocate_(size, 0u);
			memcpy(block->data.get(), old_data.get(), old_size);
		}
		else//Expand size
			block->size = size;
	}
	else if (size < block->size)//Shrink
		block->size = size;

	return block;
}

oosl::memory::collection::block_type *oosl::memory::collection::duplicate_string_(const block_id_type &target_id, uint64_type address_hint){
	auto target = find_(target_id);
	if (target == nullptr || target->extra == nullptr)//Error
		throw error_code_type::invalid_address;

	auto extra = dynamic_cast<linked_block_type *>(target->extra.get());
	if (extra == nullptr)//Error
		throw error_code_type::invalid_address;

	return allocate_linked_(sizeof(uint64_type), extra->id(), address_hint);//Ignore data -- extra info is used
}

void oosl::memory::collection::writing_(writing_callback_type callback){
	watcher_info_list_type watcher_list;
	callback(watcher_list);
	for (auto &item : watcher_list)//Call watchers
		item.collection->on_change(*this, item.range);
}

void oosl::memory::collection::fill_(uint64_type address, char source, size_type count, watcher_info_list_type &watcher_list){
	write_(address, &source, count, false, watcher_list);
}

void oosl::memory::collection::copy_(uint64_type destination, const block_id_type &source, size_type size, watcher_info_list_type &watcher_list){
	block_type *block = nullptr;
	size_type available_size = 0u, target_size = 0u, ptr_index = 0u;
	auto source_address = source.address;

	while (size > 0u){
		if ((block = (block == nullptr && source.size > 0u) ? find_nearest_(source_address) : find_(source)) != nullptr){//Valid block
			ptr_index = static_cast<size_type>(source_address - block->address);
			available_size = (block->actual_size - ptr_index);
		}
		else//No next block
			throw error_code_type::invalid_address;

		target_size = (available_size < size) ? available_size : size;
		write_(destination, block->data.get() + ptr_index, target_size, true, watcher_list);

		source_address += target_size;
		destination += target_size;
		size -= target_size;
	}
}

void oosl::memory::collection::write_(uint64_type destination, const char *source, size_type size, bool is_array, watcher_info_list_type &watcher_list){
	if (size == 0u)//Do nothing
		return;

	block_type *block = nullptr;
	size_type available_size = 0u, min_size = 0u, ptr_index = 0u;

	while (size > 0u){
		if ((block = ((block == nullptr) ? find_nearest_(destination) : find_(destination))) != nullptr){//Valid block
			ptr_index = static_cast<size_type>(destination - block->address);
			available_size = (block->actual_size - ptr_index);
		}
		else//No next block
			throw error_code_type::invalid_address;

		min_size = (available_size < size) ? available_size : size;
		if (is_array)
			memcpy_s(block->data.get() + ptr_index, size, source, min_size);
		else//Set applicable
			std::memset(block->data.get() + ptr_index, *source, min_size);

		find_watchers_(range_type{ destination, (destination + (min_size - 1u)) }, watcher_list);
		if (is_array)//Advance source pointer
			source += min_size;

		destination += min_size;
		size -= min_size;
	}
}

void oosl::memory::collection::read_(const block_id_type &source, char *destination, size_type size){
	block_type *block = nullptr;
	size_type available_size = 0u, min_size = 0u, ptr_index = 0u;
	auto source_address = source.address;

	while (size > 0u){
		if ((block = (block == nullptr && source.size > 0u) ? find_nearest_(source_address) : find_(source_address)) != nullptr){//Valid block
			ptr_index = static_cast<size_type>(source_address - block->address);
			available_size = (block->actual_size - ptr_index);
		}
		else//No next block
			throw error_code_type::invalid_address;

		min_size = (available_size < size) ? available_size : size;
		memcpy_s(destination, size, block->data.get(), min_size);//Read block

		destination += min_size;
		source_address += min_size;
		size -= min_size;
	}
}

oosl::memory::collection::map_iterator_type oosl::memory::collection::find_raw_(uint64_type address){
	if (is_protected(address))
		throw error_code_type::protected_address;
	return map_.find(address);
}

oosl::memory::collection::block_type *oosl::memory::collection::find_(const block_id_type &id){
	if (id.size == 0u)//Constant block
		return constant_collection_.find(id.address);
	return find_(id.address);
}

oosl::memory::collection::block_type *oosl::memory::collection::find_(uint64_type address){
	auto entry = find_raw_(address);
	return ((entry == map_.end()) ? nullptr : &entry->second);
}

oosl::memory::collection::block_type *oosl::memory::collection::find_nearest_(uint64_type address){
	if (is_protected(address))
		throw error_code_type::protected_address;

	block_type *block = nullptr;
	for (auto &entry : map_){
		if (entry.first == address || (entry.first < address && address < (entry.first + entry.second.actual_size))){
			block = &entry.second;
			break;
		}
	}

	return block;
}

void oosl::memory::collection::find_watchers_(const range_type &range, watcher_info_list_type &watcher_list){
	for (auto &item : watcher_collection_map_){
		if (item.first.contains(range))//Add to list
			watcher_list.push_back(watcher_info{ &item.second, range });
	}
}
