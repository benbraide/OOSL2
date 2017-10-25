#pragma once

#ifndef OOSL_CALL_INSTRUCTION_H
#define OOSL_CALL_INSTRUCTION_H

#include "jmp_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class call : public unary{
			public:
				typedef unary base_type;

				OOSL_INS_CTORS(call)

				virtual id_type id() const override{
					return id_type::call;
				}

				virtual void execute_and_update_instruction_pointer() const override{
					return execute();//Prevent advancing Instruction Pointer
				}

				virtual void execute() const override{
					assembler::vm::rip->write_qword(assembler::vm::rip->read_qword() + instruction_bytes());//Return address is after this instruction
					assembler::vm::rip->push_onto_stack(assembler::vm::stack);
					jmp::do_jump(operand_->read_qword());
				}
			};
		}
	}
}

#endif /* !OOSL_CALL_INSTRUCTION_H */
