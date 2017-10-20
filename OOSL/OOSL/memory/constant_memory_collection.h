#pragma once

#ifndef OOSL_CONSTANT_MEMORY_COLLECTION_H
#define OOSL_CONSTANT_MEMORY_COLLECTION_H

#include <unordered_map>

#include "memory_block.h"
#include "memory_error.h"

namespace oosl{
	namespace memory{
		class constant_collection{
		public:
			typedef error_code error_code_type;
			typedef block block_type;

			typedef block_type::uint64_type uint64_type;
			typedef block_type::size_type size_type;
			typedef block_type::data_type data_type;

			typedef std::unordered_map<uint64_type, block_type> map_type;

			template <typename value_type>
			block_type *insert(value_type value){
				auto block = allocate_(sizeof(value_type));
				memcpy(block->data.get(), &value, block->size);
				return block;
			}

			template <typename value_type>
			block_type *insert(const value_type *value, size_type count){
				auto block = allocate_(sizeof(value_type) * count);
				memcpy(block->data.get(), value, block->size);
				return block;
			}

			block_type *insert(const char *value);

			block_type *insert(const wchar_t *value);

			void deallocate(uint64_type address);

			block_type *find(uint64_type address);

		private:
			block_type *allocate_(size_type size);

			map_type map_;
		};
	}
}

#endif /* !OOSL_CONSTANT_MEMORY_COLLECTION_H */
