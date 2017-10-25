#pragma once

#ifndef OOSL_INT_INSTRUCTION_H
#define OOSL_INT_INSTRUCTION_H

#include "unary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class int_ : public unary{
			public:
				typedef unary base_type;

				OOSL_INS_CTORS(int_)

				virtual id_type id() const override{
					return id_type::int_;
				}

				virtual size_type instruction_bytes() const override{
					return 6u;
				}

				virtual void execute() const override{
					assembler::vm::interrupt_handlers.handle(operand_->read_dword());
				}
			};
		}
	}
}

#endif /* !OOSL_INT_INSTRUCTION_H */
