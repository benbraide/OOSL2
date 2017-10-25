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

				virtual size_type instruction_bytes() const override{
					return (operand_->instruction_bytes() + 2u);
				}

				virtual void create_or_add_to_section() override{
					base::create_or_add_to_section();
					operand_->resolve_label();
				}

				virtual void resolve_constant() override{
					operand_->resolve_constant();
				}

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
