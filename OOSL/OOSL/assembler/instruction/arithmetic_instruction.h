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
				typedef unary base_type;

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
				typedef binary base_type;

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

			using add		= binary_arithmetic<id::add>;
			using sub		= binary_arithmetic<id::sub>;

			using mult		= binary_arithmetic<id::mult>;
			using div		= binary_arithmetic<id::div>;
			using mod		= binary_arithmetic<id::mod>;

			using and_		= binary_arithmetic<id::and_>;
			using xor_		= binary_arithmetic<id::xor_>;
			using or_		= binary_arithmetic<id::or_>;

			using lshift	= binary_arithmetic<id::lshift>;
			using rshift	= binary_arithmetic<id::rshift>;
		}
	}
}

#endif /* !OOSL_ARITHMETIC_INSTRUCTION_H */
