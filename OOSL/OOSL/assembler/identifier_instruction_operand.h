#pragma once

#ifndef OOSL_IDENTIFIER_INSTRUCTION_OPERAND_H
#define OOSL_IDENTIFIER_INSTRUCTION_OPERAND_H

#include "constant_value_instruction_operand.h"

namespace oosl{
	namespace assembler{
		class identifier_instruction_operand : public instruction_operand_base{
		public:
			explicit identifier_instruction_operand(const std::string &value);

			virtual instruction_operand_type type() const override;

			virtual code_type code() const override;

			virtual void print(writer_type &writer) const override;

			virtual ptr_type apply_operator(operator_type op, instruction_operand_base &rhs) override;

			virtual byte_type read_byte() const override;

			virtual word_type read_word() const override;

			virtual dword_type read_dword() const override;

			virtual qword_type read_qword() const override;

			virtual float read_float() const override;

			virtual double read_double() const override;

			virtual long double read_ldouble() const override;

		private:
			qword_type read_() const;

			template <typename value_type>
			ptr_type eval_(operator_type op, value_type lhs, value_type rhs){
				typedef constant_value_instruction_operand<value_type> constant_value_instruction_operand_type;
				switch (op){
				case operator_type::sub:
					return std::make_shared<constant_value_instruction_operand_type>(lhs - rhs);
				case operator_type::mult:
					return std::make_shared<constant_value_instruction_operand_type>(lhs * rhs);
				case operator_type::div:
					return std::make_shared<constant_value_instruction_operand_type>(lhs / rhs);
				default:
					break;
				}

				throw instruction_error::bad_operation;
			}

			template <typename value_type>
			ptr_type eval_integral_(operator_type op, value_type lhs, value_type rhs){
				typedef constant_value_instruction_operand<value_type> constant_value_instruction_operand_type;
				switch (op){
				case operator_type::mod:
					return std::make_shared<constant_value_instruction_operand_type>(lhs % rhs);
				case operator_type::bit_and:
					return std::make_shared<constant_value_instruction_operand_type>(lhs & rhs);
				case operator_type::bit_or:
					return std::make_shared<constant_value_instruction_operand_type>(lhs | rhs);
				case operator_type::bit_xor:
					return std::make_shared<constant_value_instruction_operand_type>(lhs ^ rhs);
				case operator_type::lshift:
					return std::make_shared<constant_value_instruction_operand_type>(lhs << rhs);
				case operator_type::rshift:
					return std::make_shared<constant_value_instruction_operand_type>(lhs >> rhs);
				default:
					break;
				}

				return eval_(op, lhs, rhs);
			}

			std::string value_;
		};
	}
}

#endif /* !OOSL_IDENTIFIER_INSTRUCTION_OPERAND_H */
