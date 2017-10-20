#pragma once

#ifndef OOSL_MEMORY_WATCHER_H
#define OOSL_MEMORY_WATCHER_H

#include "../common/range.h"

#include "memory_block.h"

namespace oosl{
	namespace memory{
		template <class memory_type>
		class basic_watcher{
		public:
			typedef memory_type memory_type;
			typedef block block_type;

			typedef block_type::uint64_type uint64_type;
			typedef oosl::common::range<uint64_type> range_type;

			virtual ~basic_watcher() = default;

			virtual void on_change(memory_type &memory, const range_type &range, const range_type &changed) = 0;
		};
	}
}

#endif /* !OOSL_MEMORY_WATCHER_H */
