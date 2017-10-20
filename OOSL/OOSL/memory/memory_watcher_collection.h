#pragma once

#ifndef OOSL_MEMORY_WATCHER_COLLECTION_H
#define OOSL_MEMORY_WATCHER_COLLECTION_H

#include <list>
#include <memory>

#include "memory_watcher.h"

namespace oosl{
	namespace memory{
		template <class memory_type>
		class basic_watcher_collection{
		public:
			typedef memory_type memory_type;
			typedef basic_watcher<memory_type> watcher_type;

			typedef typename watcher_type::block_type block_type;
			typedef typename watcher_type::uint64_type uint64_type;
			typedef typename watcher_type::range_type range_type;

			typedef std::shared_ptr<watcher_type> watcher_ptr_type;
			typedef std::list<watcher_ptr_type> list_type;

			explicit basic_watcher_collection(const range_type &range)
				: range_(range){}

			void add(watcher_ptr_type watcher){
				list_.push_back(watcher);
			}

			void remove(watcher_type &watcher){
				for (auto item = list_.begin(); item != list_.end(); ++item){
					if (item->get() == &watcher){
						list_.erase(item);
						break;
					}
				}
			}

			void on_change(memory_type &memory, const range_type &changed){
				auto list_copy = list_;//Copy list -- enable multi-threaded re-entrance
				for (auto item : list_copy)
					item->on_change(memory, range_, changed);
			}

			const range_type &range() const{
				return range_;
			}

		private:
			list_type list_;
			range_type range_;
		};
	}
}

#endif /* !OOSL_MEMORY_WATCHER_COLLECTION_H */
