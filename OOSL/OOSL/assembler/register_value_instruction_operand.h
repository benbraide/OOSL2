#pragma once

#ifndef OOSL_REGISTER_VALUE_INSTRUCTION_OPERAND_H
#define OOSL_REGISTER_VALUE_INSTRUCTION_OPERAND_H

#include "instruction_operand_base.h"

namespace oosl{
	namespace assembler{
		class register_value_instruction_operand : public instruction_operand_base{
		public:
			typedef oosl::memory::register_value_base register_value_type;

			enum class operator_type{
				add,
				sub,
				mult,
				div,
				mod,
				bit_and,
				bit_or,
				bit_xor,
				lshift,
				rshift,
			};

			explicit register_value_instruction_operand(register_value_type &value);

			virtual instruction_operand_base &operator =(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator +=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator -=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator *=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator /=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator %=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator &=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator |=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator ^=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator <<=(const instruction_operand_base &rhs);

			virtual instruction_operand_base &operator >>=(const instruction_operand_base &rhs);

			virtual bool operator <(const instruction_operand_base &rhs) const;

			virtual bool operator ==(const instruction_operand_base &rhs) const;

			virtual byte_type read_byte() const override;

			virtual word_type read_word() const override;

			virtual dword_type read_dword() const override;

			virtual qword_type read_qword() const override;

			virtual float read_float() const override;

			virtual double read_double() const override;

			virtual long double read_ldouble() const override;

		private:
			instruction_operand_base &eval_(operator_type op, const instruction_operand_base &rhs);

			template <typename value_type>
			instruction_operand_base &eval_(operator_type op, value_type lhs, value_type rhs){
				switch (op){
				case operator_type::sub:
					return assign_(lhs - rhs);
				case operator_type::mult:
					return assign_(lhs * rhs);
				case operator_type::div:
					return assign_(lhs / rhs);
				default:
					break;
				}

				return assign_(lhs + rhs);
			}

			template <typename value_type>
			instruction_operand_base &eval_integral_(operator_type op, value_type lhs, value_type rhs){
				switch (op){
				case operator_type::mod:
					return assign_(lhs % rhs);
				case operator_type::bit_and:
					return assign_(lhs & rhs);
				case operator_type::bit_or:
					return assign_(lhs | rhs);
				case operator_type::bit_xor:
					return assign_(lhs ^ rhs);
				case operator_type::lshift:
					return assign_(lhs << rhs);
				case operator_type::rshift:
					return assign_(lhs >> rhs);
				default:
					break;
				}

				return eval_(op, lhs, rhs);
			}

			template <typename value_type>
			instruction_operand_base &assign_(value_type value){
				value_->write(value);
				return *this;
			}

			bool comp_(bool less, const instruction_operand_base &rhs) const;

			template <typename value_type>
			bool comp_(bool less, value_type lhs, value_type rhs) const{
				return (less ? (lhs < rhs) : (lhs == rhs));
			}

			register_value_type *value_;
		};
	}
}

#endif /* !OOSL_REGISTER_VALUE_INSTRUCTION_OPERAND_H */
