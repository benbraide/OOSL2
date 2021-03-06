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

				virtual size_type instruction_bytes() const override{
					auto value = left_->instruction_bytes();
					try{
						value += right_->instruction_bytes();
					}
					catch (...){//Use left operand's size
						value += value;
					}

					return (value + 2u);
				}

				virtual void create_or_add_to_section() override{
					base::create_or_add_to_section();
					left_->resolve_label();
					right_->resolve_label();
				}

				virtual void resolve_constant() override{
					left_->resolve_constant();
					right_->resolve_constant();
				}

				virtual void print(writer_type &writer) const override{
					writer.write(id_to_string(id())).write(" ");
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
