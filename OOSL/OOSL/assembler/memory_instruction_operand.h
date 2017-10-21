#pragma once

#include <memory>

#include "instruction_operand_base.h"

namespace oosl{
	namespace assembler{
		class memory_instruction_operand : public instruction_operand_base{
		public:
			typedef std::size_t size_type;
			typedef std::shared_ptr<instruction_operand_base> instruction_operand_base_ptr_type;

			explicit memory_instruction_operand(code_type code, instruction_operand_base_ptr_type value);

			virtual instruction_operand_type type() const override;

			virtual code_type code() const override;

			virtual void print(writer_type &writer) const override;

			virtual instruction_operand_base &operator =(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator +=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator -=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator *=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator /=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator %=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator &=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator |=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator ^=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator <<=(const instruction_operand_base &rhs) override;

			virtual instruction_operand_base &operator >>=(const instruction_operand_base &rhs) override;

			virtual bool operator <(const instruction_operand_base &rhs) const override;

			virtual bool operator ==(const instruction_operand_base &rhs) const override;

			virtual byte_type read_byte() const override;

			virtual word_type read_word() const override;

			virtual dword_type read_dword() const override;

			virtual qword_type read_qword() const override;

			virtual float read_float() const override;

			virtual double read_double() const override;

			virtual long double read_ldouble() const override;

		private:
			template <typename target_type>
			target_type read_(code_type code = code_type::unknown) const{
				switch ((code == code_type::unknown) ? code_ : code){
				case code_type::byte:
					return read_<target_type, __int8>();
				case code_type::word:
					return read_<target_type, __int16>();
				case code_type::dword:
					return read_<target_type, __int32>();
				case code_type::qword:
					return read_<target_type, __int64>();
				case code_type::float_:
					return read_<target_type, float>();
				case code_type::double_:
					return read_<target_type, double>();
				case code_type::ldouble:
					return read_<target_type, long double>();
				default:
					break;
				}

				throw instruction_error::bad_conversion;
			}

			template <typename target_type, typename source_type>
			target_type read_() const{
				auto source = source_type();
				memcpy(&source, reinterpret_cast<void *>(value_->type()), sizeof(source_type));
				return static_cast<target_type>(source);
			}

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
				auto address = reinterpret_cast<void *>(value_->type());
				memcpy(address, &value, sizeof(value_type));
				return *this;
			}

			bool comp_(bool less, const instruction_operand_base &rhs) const;

			template <typename value_type>
			bool comp_(bool less, value_type lhs, value_type rhs) const{
				return (less ? (lhs < rhs) : (lhs == rhs));
			}

			code_type code_;
			instruction_operand_base_ptr_type value_;
		};
	}
}
