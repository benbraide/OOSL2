#pragma once

#ifndef OOSL_GROUPED_EXPRESSION_INSTRUCTION_OPERAND_H
#define OOSL_GROUPED_EXPRESSION_INSTRUCTION_OPERAND_H

#include "instruction_operand_base.h"

namespace oosl{
	namespace assembler{
		class grouped_expression_instruction_operand : public instruction_operand_base{
		public:
			explicit grouped_expression_instruction_operand(ptr_type value);

			virtual instruction_operand_type type() const override;

			virtual code_type code() const override;

			virtual size_type instruction_bytes() const override;

			virtual void print(writer_type &writer) const override;

			virtual ptr_type eval() override;

			virtual ptr_type apply_operator(operator_type op, instruction_operand_base &rhs) override;

			virtual byte_type read_byte() const override;

			virtual word_type read_word() const override;

			virtual dword_type read_dword() const override;

			virtual qword_type read_qword() const override;

			virtual float read_float() const override;

			virtual double read_double() const override;

			virtual long double read_ldouble() const override;

		private:
			ptr_type value_;
		};
	}
}

#endif /* !OOSL_GROUPED_EXPRESSION_INSTRUCTION_OPERAND_H */
