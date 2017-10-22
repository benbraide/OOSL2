#pragma once

#ifndef OOSL_ARITHMETIC_INSTRUCTION_H
#define OOSL_ARITHMETIC_INSTRUCTION_H

#include "unary_instruction.h"
#include "binary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			template <instruction::id id_value>
			class unary_arithmetic : public unary{
			public:
				OOSL_INS_CTORS(unary_arithmetic)

				virtual id_type id() const override{
					return id_value;
				}

				virtual void execute() const override{
					switch (id_value){
					case id_type::not:
						~(*operand_);
						break;
					case id_type::inc:
						++(*operand_);
						break;
					case id_type::dec:
						--(*operand_);
						break;
					default:
						break;
					}
				}
			};

			template <instruction::id id_value>
			class binary_arithmetic : public binary{
			public:
				OOSL_INS_CTORS(binary_arithmetic)

				virtual id_type id() const override{
					return id_value;
				}

				virtual void execute() const override{
					switch (id_value){
					case id_type::add:
						*left_ += *right_;
						break;
					case id_type::sub:
						*left_ -= *right_;
						break;
					case id_type::mult:
						*left_ *= *right_;
						break;
					case id_type::div:
						*left_ /= *right_;
						break;
					case id_type::mod:
						*left_ %= *right_;
						break;
					case id_type::and_:
						*left_ &= *right_;
						break;
					case id_type::xor_:
						*left_ ^= *right_;
						break;
					case id_type::or_:
						*left_ |= *right_;
						break;
					case id_type::lshift:
						*left_ <<= *right_;
						break;
					case id_type::rshift:
						*left_ >>= *right_;
						break;
					default:
						break;
					}
				}
			};

			using not		= unary_arithmetic<id::not>;
			using inc		= unary_arithmetic<id::inc>;
			using dec		= unary_arithmetic<id::dec>;

			using add		= unary_arithmetic<id::add>;
			using sub		= unary_arithmetic<id::sub>;

			using mult		= unary_arithmetic<id::mult>;
			using div		= unary_arithmetic<id::div>;
			using mod		= unary_arithmetic<id::mod>;

			using and_		= unary_arithmetic<id::and_>;
			using xor_		= unary_arithmetic<id::xor_>;
			using or_		= unary_arithmetic<id::or_>;

			using lshift	= unary_arithmetic<id::lshift>;
			using rshift	= unary_arithmetic<id::rshift>;
		}
	}
}

#endif /* !OOSL_ARITHMETIC_INSTRUCTION_H */
