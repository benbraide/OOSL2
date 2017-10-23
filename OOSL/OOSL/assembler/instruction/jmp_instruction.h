#pragma once

#ifndef OOSL_JMP_INSTRUCTION_H
#define OOSL_JMP_INSTRUCTION_H

#include "unary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class jmp : public unary{
			public:
				typedef unary base_type;

				OOSL_INS_CTORS(jmp)

				virtual id_type id() const override{
					return id_type::jmp;
				}

				virtual void execute_and_update_instruction_pointer() const override{
					return execute();//Prevent advancing Instruction Pointer
				}

				virtual void execute() const override{
					if (test_())//Test passed
						do_jump(operand_->read_qword());
				}

				static void do_jump(instruction_operand_base::qword_type address){
					assembler::vm::register_.find("rip")->write_qword(address);
				}

			protected:
				virtual bool test_() const{
					return true;
				}
			};

			using register_flag = oosl::memory::register_flag;

			template <id id_value, bool truth, register_flag first, register_flag second = register_flag::nil>
			class conditional_jmp : public jmp{
			public:
				typedef jmp base_type;

				OOSL_INS_CTORS(jmp)

				virtual id_type id() const override{
					return id_value;
				}

			protected:
				virtual bool test_() const{
					auto first_truth = vm::register_.has_flag(first);
					auto second_truth = ((second == register_flag::nil) ? truth : vm::register_.has_flag(second));

					if (truth)//Either
						return (first_truth || second_truth);

					return !(first_truth || second_truth);//Not any
				}
			};

			using jz	= conditional_jmp<id::jz, true, register_flag::zero>;
			using jnz	= conditional_jmp<id::jnz, false, register_flag::zero>;

			using je	= conditional_jmp<id::je, true, register_flag::zero>;
			using jne	= conditional_jmp<id::jne, false, register_flag::zero>;

			using jl	= conditional_jmp<id::jl, true, register_flag::less>;
			using jnl	= conditional_jmp<id::jnl, false, register_flag::less>;

			using jle	= conditional_jmp<id::jle, true, register_flag::less, register_flag::zero>;
			using jnle	= conditional_jmp<id::jnle, false, register_flag::less, register_flag::zero>;

			using jg	= conditional_jmp<id::jg, false, register_flag::less, register_flag::zero>;
			using jng	= conditional_jmp<id::jng, true, register_flag::less, register_flag::zero>;

			using jge	= conditional_jmp<id::jge, false, register_flag::less>;
			using jnge	= conditional_jmp<id::jnge, true, register_flag::less>;
		}
	}
}

#endif /* !OOSL_JMP_INSTRUCTION_H */
