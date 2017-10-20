#pragma once

#ifndef OOSL_MEMORY_BLOCK_EXTRA_H
#define OOSL_MEMORY_BLOCK_EXTRA_H

namespace oosl{
	namespace memory{
		class block_extra{
		public:
			virtual ~block_extra() = default;
		};

		template <class memory_type, class block_id_type, class deallocation_option_type>
		class basic_linked_block : public block_extra{
		public:
			basic_linked_block(memory_type &memory, const block_id_type &id)
				: memory_(memory), id_(id){}

			virtual ~basic_linked_block(){
				memory_.deallocate(id_, deallocation_option_type::no_throw);
			}

			const block_id_type &id() const{
				return id_;
			}

		private:
			memory_type &memory_;
			block_id_type id_;
		};
	}
}

#endif /* !OOSL_MEMORY_BLOCK_EXTRA_H */
