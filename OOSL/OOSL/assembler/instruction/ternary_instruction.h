#pragma once

#ifndef OOSL_TERNARY_INSTRUCTION_H
#define OOSL_TERNARY_INSTRUCTION_H

#include "instruction_base.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class ternary : public base{
			public:
				ternary(operand_type left, operand_type right, operand_type last)
					: left_(left), right_(right), last_(last){}

				virtual ~ternary() = default;

				virtual size_type instruction_bytes() const override{
					return (left_->instruction_bytes() + right_->instruction_bytes() + last_->instruction_bytes() + 2u);
				}

				virtual void print(writer_type &writer) const override{
					writer.write(id_to_string(id()));
					writer.write(" ");
					left_->print(writer);
					writer.write(", ");
					right_->print(writer);
					writer.write(", ");
					last_->print(writer);
				}

			protected:
				operand_type left_;
				operand_type right_;
				operand_type last_;
			};
		}
	}
}

#endif /* !OOSL_TERNARY_INSTRUCTION_H */
