#pragma once

#ifndef OOSL_INTERRUPT_BASE_H
#define OOSL_INTERRUPT_BASE_H

namespace oosl{
	namespace assembler{
		namespace interrupt{
			enum class error{
				nil,
				not_found,
				sys_call_not_found,
			};

			class base{
			public:
				virtual ~base() = default;

				virtual void handle() = 0;
			};
		}
	}
}

#endif /* !OOSL_INTERRUPT_BASE_H */
