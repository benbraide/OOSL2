#pragma once

#ifndef OOSL_BINARY_INSTRUCTION_H
#define OOSL_BINARY_INSTRUCTION_H

#include "instruction_base.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class binary : public base{
			public:
				binary(operand_type left, operand_type right)
					: left_(left), right_(right){}

				virtual ~binary() = default;

				virtual void print(writer_type &writer) const override{
					writer.write(id_to_string(id()));
					writer.write(" ");
					left_->print(writer);
					writer.write(", ");
					right_->print(writer);
				}

			protected:
				operand_type left_;
				operand_type right_;
			};
		}
	}
}

#endif /* !OOSL_BINARY_INSTRUCTION_H */
