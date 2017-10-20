#pragma once

#ifndef OOSL_MEMORY_BLOCK_H
#define OOSL_MEMORY_BLOCK_H

#include <memory>

#include "memory_block_extra.h"

namespace oosl{
	namespace memory{
		struct block{
			typedef unsigned __int64 uint64_type;
			typedef std::size_t size_type;

			typedef std::unique_ptr<char[]> data_type;
			typedef std::shared_ptr<block_extra> block_extra_type;

			size_type ref_count;
			uint64_type address;
			size_type size;
			size_type actual_size;
			data_type data;
			block_extra_type extra;
		};

		struct block_id{
			block::uint64_type address;
			block::size_type size;
		};
	}
}

#endif /* !OOSL_MEMORY_BLOCK_H */
