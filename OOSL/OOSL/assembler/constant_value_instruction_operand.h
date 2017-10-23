#pragma once

#ifndef OOSL_CONSTANT_VALUE_INSTRUCTION_OPERAND_H
#define OOSL_CONSTANT_VALUE_INSTRUCTION_OPERAND_H

#include "instruction_operand_base.h"

namespace oosl{
	namespace assembler{
		template <class value_type>
		struct constant_value_code{
			static const oosl::memory::register_value_type code = oosl::memory::register_value_type::unknown;
		};

		template <>
		struct constant_value_code<unsigned __int8>{
			static const oosl::memory::register_value_type code = oosl::memory::register_value_type::byte;
		};

		template <>
		struct constant_value_code<unsigned __int16>{
			static const oosl::memory::register_value_type code = oosl::memory::register_value_type::word;
		};

		template <>
		struct constant_value_code<unsigned __int32>{
			static const oosl::memory::register_value_type code = oosl::memory::register_value_type::dword;
		};

		template <>
		struct constant_value_code<unsigned __int64>{
			static const oosl::memory::register_value_type code = oosl::memory::register_value_type::qword;
		};

		template <>
		struct constant_value_code<float>{
			static const oosl::memory::register_value_type code = oosl::memory::register_value_type::float_;
		};

		template <>
		struct constant_value_code<double>{
			static const oosl::memory::register_value_type code = oosl::memory::register_value_type::double_;
		};

		template <>
		struct constant_value_code<long double>{
			static const oosl::memory::register_value_type code = oosl::memory::register_value_type::ldouble;
		};

		template <class value_type>
		class constant_value_instruction_operand : public instruction_operand_base{
		public:
			typedef value_type value_type;

			explicit constant_value_instruction_operand(value_type value = value_type())
				: value_(value){}

			virtual instruction_operand_type type() const override{
				return instruction_operand_type::constant_value;
			}

			virtual code_type code() const override{
				return constant_value_code<value_type>::code;
			}

			virtual void print(writer_type &writer) const override{
				writer.write(std::to_string(value_));
			}

			virtual ptr_type apply_operator(operator_type op, instruction_operand_base &rhs) override{
				auto resolved_rhs = rhs.eval();
				if (resolved_rhs->type() != instruction_operand_type::constant_value)
					throw instruction_error::bad_operation;

				switch (code()){
				case code_type::byte:
					return eval_integral_(op, static_cast<byte_type>(value_), resolved_rhs->read_byte());
				case code_type::word:
					return eval_integral_(op, static_cast<word_type>(value_), resolved_rhs->read_word());
				case code_type::dword:
					return eval_integral_(op, static_cast<dword_type>(value_), resolved_rhs->read_dword());
				case code_type::qword:
					return eval_integral_(op, static_cast<qword_type>(value_), resolved_rhs->read_qword());
				case code_type::float_:
					return eval_(op, static_cast<float>(value_), resolved_rhs->read_float());
				case code_type::double_:
					return eval_(op, static_cast<double>(value_), resolved_rhs->read_double());
				case code_type::ldouble:
					return eval_(op, static_cast<long double>(value_), resolved_rhs->read_ldouble());
				default:
					break;
				}

				throw instruction_error::bad_operation;
			}

			virtual byte_type read_byte() const override{
				return static_cast<byte_type>(value_);
			}

			virtual word_type read_word() const override{
				return static_cast<word_type>(value_);
			}

			virtual dword_type read_dword() const override{
				return static_cast<dword_type>(value_);
			}

			virtual qword_type read_qword() const override{
				return static_cast<qword_type>(value_);
			}

			virtual float read_float() const override{
				return static_cast<float>(value_);
			}

			virtual double read_double() const override{
				return static_cast<double>(value_);
			}

			virtual long double read_ldouble() const override{
				return static_cast<long double>(value_);
			}

		private:
			template <typename value_type>
			ptr_type eval_(operator_type op, value_type lhs, value_type rhs){
				switch (op){
				case operator_type::add:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs + rhs));
				case operator_type::sub:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs - rhs));
				case operator_type::mult:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs * rhs));
				case operator_type::div:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs / rhs));
				default:
					break;
				}

				throw instruction_error::bad_operation;
			}

			template <typename value_type>
			ptr_type eval_integral_(operator_type op, value_type lhs, value_type rhs){
				switch (op){
				case operator_type::mod:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs % rhs));
				case operator_type::bit_and:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs & rhs));
				case operator_type::bit_or:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs | rhs));
				case operator_type::bit_xor:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs ^ rhs));
				case operator_type::lshift:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs << rhs));
				case operator_type::rshift:
					return std::make_shared<constant_value_instruction_operand<value_type>>(static_cast<value_type>(lhs >> rhs));
				default:
					break;
				}

				return eval_(op, lhs, rhs);
			}

			value_type value_;
		};
	}
}

#endif /* !OOSL_CONSTANT_VALUE_INSTRUCTION_OPERAND_H */
