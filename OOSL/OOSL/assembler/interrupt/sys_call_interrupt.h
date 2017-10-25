#pragma once

#ifndef OOSL_SYS_CALL_INTERRUPT_H
#define OOSL_SYS_CALL_INTERRUPT_H

#include "interrupt_base.h"

namespace oosl{
	namespace assembler{
		namespace interrupt{
			class sys_call : public base{
			public:
				enum class id : unsigned int{
					exit = 1,
					write = 4,
					read = 5,
				};

				virtual ~sys_call() = default;

				virtual void handle() override;
			};
		}
	}
}

#endif /* !OOSL_SYS_CALL_INTERRUPT_H */
