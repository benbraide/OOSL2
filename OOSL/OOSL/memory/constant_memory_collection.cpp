#include "constant_memory_collection.h"

oosl::memory::constant_collection::block_type *oosl::memory::constant_collection::insert(const char *value){
	return insert(value, std::strlen(value) + 1u);
}

oosl::memory::constant_collection::block_type *oosl::memory::constant_collection::insert(const wchar_t *value){
	return insert(value, std::wcslen(value) + 1u);
}

void oosl::memory::constant_collection::deallocate(uint64_type address){
	auto entry = map_.find(address);
	if (entry == map_.end())//Error
		throw error_code_type::invalid_address;

	if (entry->second.ref_count == 0u || --entry->second.ref_count == 0u)
		map_.erase(entry);
}

oosl::memory::constant_collection::block_type *oosl::memory::constant_collection::find(uint64_type address){
	auto entry = map_.find(address);
	return ((entry == map_.end()) ? nullptr : &entry->second);
}

oosl::memory::constant_collection::block_type *oosl::memory::constant_collection::allocate_(size_type size){
	try{
		block_type block{
			1u,								//Reference count
			0u,								//Address
			size,							//Size
			0u,								//Actual size -- 0 for constant block
			std::make_unique<char[]>(size)	//Data
		};

		if (block.data.get() != nullptr){//Add entry
			block.address = *reinterpret_cast<uint64_type *>(block.data.get());
			return &(map_[block.address] = std::move(block));
		}
	}
	catch (...){}

	throw error_code_type::out_of_memory;
}
