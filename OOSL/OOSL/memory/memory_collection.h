#pragma once

#ifndef OOSL_MEMORY_COLLECTION_H
#define OOSL_MEMORY_COLLECTION_H

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <shared_mutex>

#include "../common/macro.h"

#include "constant_memory_collection.h"
#include "memory_watcher_collection.h"

namespace oosl{
	namespace memory{
		enum class state_type : unsigned int{
			nil					= (0 << 0x0000),
			protected_mode		= (1 << 0x0000),
		};

		enum class deallocation_option : unsigned int{
			nil					= (0 << 0x0000),
			no_merge			= (1 << 0x0000),
			no_throw			= (1 << 0x0001),
		};

		class collection{
		public:
			typedef constant_collection constant_collection_type;
			typedef error_code error_code_type;
			typedef block_id block_id_type;
			typedef block block_type;

			typedef basic_linked_block<collection, block_id_type, deallocation_option> linked_block_type;
			typedef basic_watcher_collection<collection> watcher_collection_type;

			typedef block_type::uint64_type uint64_type;
			typedef block_type::size_type size_type;
			typedef block_type::data_type data_type;

			typedef watcher_collection_type::range_type range_type;
			typedef watcher_collection_type::watcher_type watcher_type;
			typedef watcher_collection_type::watcher_ptr_type watcher_ptr_type;

			typedef std::map<range_type, watcher_collection_type> watcher_collection_map_type;
			typedef std::unordered_map<uint64_type, block_type> map_type;
			typedef std::map<uint64_type, size_type> size_map_type;

			struct watcher_info{
				watcher_collection_type *collection;
				range_type range;
			};

			typedef std::list<watcher_info> watcher_info_list_type;
			typedef std::function<void(watcher_info_list_type &)> writing_callback_type;

			typedef map_type::iterator map_iterator_type;

			typedef std::shared_mutex lock_type;
			typedef std::lock_guard<lock_type> lock_guard_type;
			typedef std::shared_lock<lock_type> shared_lock_guard_type;

			collection();

			void enter_protected_mode();

			void leave_protected_mode();

			bool is_protected_mode();

			void protect(uint64_type address_ = 0u);

			bool is_protected(uint64_type address);

			void add_watcher(const range_type &range, watcher_ptr_type watcher);

			void remove_watcher(const range_type &range, watcher_type &watcher);

			void remove_watcher(watcher_type &watcher);

			void deallocate(const block_id_type &id, deallocation_option options = deallocation_option::nil);

			uint64_type reserve(size_type size);

			block_type *allocate(size_type size, uint64_type address_hint = 0ull);

			block_type *allocate_contiguous(size_type count, size_type size);

			block_type *allocate_linked(size_type size, const block_id_type &target_id, uint64_type address_hint = 0ull);

			block_type *reallocate(uint64_type address, size_type size);

			template <typename value_type>
			block_type *insert(value_type value){
				lock_guard_type lock_guard(lock_);
				return insert_(value);
			}

			template <typename value_type>
			block_type *insert_linked(value_type value, const block_id_type &target_id){
				lock_guard_type lock_guard(lock_);
				return insert_linked_(value, target_id);
			}

			template <typename char_type>
			block_type *insert_string(const char_type *value, size_type count){
				lock_guard_type lock_guard(lock_);
				return insert_string_(value);
			}

			template <typename string_type>
			block_type *insert_string(const string_type &value){
				return insert_string(value.data(), value.size());
			}

			block_type *duplicate_string(const block_id_type &target_id, uint64_type address_hint = 0ull);

			void fill(uint64_type address, char source, size_type count);

			void copy(uint64_type destination, const block_id_type &source, size_type size);

			template <typename value_type>
			void write(uint64_type destination, value_type value){
				return write(destination, reinterpret_cast<char *>(&value), sizeof(value_type));
			}

			template <typename value_type>
			void write(uint64_type destination, const value_type *value, size_type count){
				return write(destination, reinterpret_cast<const char *>(value), sizeof(value_type) * count);
			}

			void write(uint64_type destination, const char *source, size_type size);

			template <typename target_type>
			target_type read(const block_id_type &source){
				auto value = target_type();
				read(source, (char *)&value, sizeof(target_type));
				return value;
			}

			void read(const block_id_type &source, char *destination, size_type size);

			block_type *find(const block_id_type &id);

			block_type *find_nearest(uint64_type address);

			static thread_local size_type protected_mode_count;

		private:
			void add_available_(uint64_type value, size_type size);

			uint64_type find_available_(size_type size, uint64_type match = 0ull);

			void deallocate_(uint64_type address, deallocation_option options);

			uint64_type reserve_(size_type size);

			block_type *allocate_block_(size_type size, uint64_type address);

			block_type *allocate_(size_type size, uint64_type address_hint);

			block_type *allocate_contiguous_(size_type count, size_type size);

			block_type *allocate_linked_(size_type size, const block_id_type &target_id, uint64_type address_hint);

			block_type *reallocate_(uint64_type address, size_type size);

			template <typename value_type>
			block_type *insert_(value_type value){
				return constant_collection_.insert(value);
			}

			template <typename value_type>
			block_type *insert_linked_(value_type value, const block_id_type &target_id){
				auto block = constant_collection_.insert(value);
				block->extra = std::make_shared<linked_block_type>(*this, target_id);
				return block;
			}

			template <typename char_type>
			block_type *insert_string_(const char_type *value, size_type count){
				auto target = constant_collection_.insert(value, count);
				return insert_linked_(*reinterpret_cast<uint64_type *>(target), block_id_type{ target->address, 0u });
			}

			block_type *duplicate_string_(const block_id_type &target_id, uint64_type address_hint);

			void writing_(writing_callback_type callback);

			void fill_(uint64_type address, char source, size_type count, watcher_info_list_type &watcher_list);

			void copy_(uint64_type destination, const block_id_type &source, size_type size, watcher_info_list_type &watcher_list);

			void write_(uint64_type destination, const char *source, size_type size, bool is_array, watcher_info_list_type &watcher_list);

			void read_(const block_id_type &source, char *destination, size_type size);

			map_iterator_type find_raw_(uint64_type address);

			block_type *find_(const block_id_type &id);

			block_type *find_(uint64_type address);

			block_type *find_nearest_(uint64_type address);

			void find_watchers_(const range_type &range, watcher_info_list_type &watcher_list);

			state_type states_;
			constant_collection_type constant_collection_;
			watcher_collection_map_type watcher_collection_map_;
			uint64_type protected_;
			uint64_type next_address_;
			map_type map_;
			size_map_type available_;
			lock_type lock_;
		};

		using linked_block			= basic_linked_block<collection, block_id, deallocation_option>;
		using watcher				= basic_watcher<collection>;
		using watcher_collection	= basic_watcher_collection<collection>;

		OOSL_MAKE_OPERATORS(state_type);
		OOSL_MAKE_OPERATORS(deallocation_option);
	}
}

#endif /* !OOSL_MEMORY_COLLECTION_H */
