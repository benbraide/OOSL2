#pragma once

#ifndef OOSL_CONSTANT_VALUE_INSTRUCTION_OPERAND_H
#define OOSL_CONSTANT_VALUE_INSTRUCTION_OPERAND_H

#include "instruction_operand_base.h"

namespace oosl{
	namespace assembler{
		template <class value_type>
		class constant_value_instruction_operand : public instruction_operand_base{
		public:
			typedef value_type value_type;

			explicit constant_value_instruction_operand(value_type value = value_type())
				: value_(value){}

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

		private:
			value_type value_;
		};
	}
}

#endif /* !OOSL_CONSTANT_VALUE_INSTRUCTION_OPERAND_H */
