#pragma once

#ifndef OOSL_INTERRUPT_HANDLERS_H
#define OOSL_INTERRUPT_HANDLERS_H

#include <memory>
#include <unordered_map>

#include "sys_call_interrupt.h"

namespace oosl{
	namespace assembler{
		namespace interrupt{
			enum class handler_id : unsigned int{
				sys_call = 0x80,
			};

			class handlers{
			public:
				typedef std::shared_ptr<base> handler_type;
				typedef std::unordered_map<handler_id, handler_type> map_type;

				handlers();

				void handle(unsigned int id);

			private:
				map_type map_;
			};
		}
	}
}

#endif /* !OOSL_INTERRUPT_HANDLERS_H */
