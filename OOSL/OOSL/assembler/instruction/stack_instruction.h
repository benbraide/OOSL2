#pragma once

#ifndef OOSL_STACK_INSTRUCTION_H
#define OOSL_STACK_INSTRUCTION_H

#include "../vm.h"

#include "unary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			template <bool push>
			class stack : public unary{
			public:
				typedef unary base_type;

				OOSL_INS_CTORS(stack)

				virtual id_type id() const override{
					return (push ? id_type::push : id_type::pop);
				}

				virtual void execute() const override{
					if (push)
						operand_->push_onto_stack(vm::stack);
					else//Pop
						operand_->pop_from_stack(vm::stack);
				}
			};

			using push = stack<true>;
			using pop = stack<false>;
		}
	}
}

#endif /* !OOSL_STACK_INSTRUCTION_H */
