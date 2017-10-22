#pragma once

#ifndef OOSL_UNARY_INSTRUCTION_H
#define OOSL_UNARY_INSTRUCTION_H

#include "instruction_base.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class unary : public base{
			public:
				explicit unary(operand_type operand)
					: operand_(operand){}

				virtual ~unary() = default;

				virtual void print(writer_type &writer) const override{
					writer.write(id_to_string(id()));
					writer.write(" ");
					operand_->print(writer);
				}

			protected:
				operand_type operand_;
			};
		}
	}
}

#endif /* !OOSL_UNARY_INSTRUCTION_H */
