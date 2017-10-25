#pragma once

#ifndef OOSL_RET_INSTRUCTION_H
#define OOSL_RET_INSTRUCTION_H

#include "no_operand_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class ret : public no_operand{
			public:
				typedef no_operand base_type;

				OOSL_INS_CTORS(ret)

				virtual id_type id() const override{
					return id_type::ret;
				}

				virtual void execute_and_update_instruction_pointer() const override{
					return execute();//Prevent advancing Instruction Pointer
				}

				virtual void execute() const override{
					assembler::vm::rip->pop_from_stack(assembler::vm::stack);
				}
			};
		}
	}
}

#endif /* !OOSL_RET_INSTRUCTION_H */
