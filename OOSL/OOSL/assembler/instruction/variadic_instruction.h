#pragma once

#ifndef OOSL_VARIADIC_INSTRUCTION_H
#define OOSL_VARIADIC_INSTRUCTION_H

#include <vector>

#include "instruction_base.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class variadic : public base{
			public:
				typedef std::vector<operand_type> operand_list_type;

				explicit variadic(const operand_list_type &operands)
					: operands_(operands){}

				explicit variadic(operand_list_type &&operands)
					: operands_(std::move(operands)){}

				virtual ~variadic() = default;

				virtual size_type instruction_bytes() const override{
					size_type bytes = 0u;
					for (auto item : operands_)
						bytes += item->instruction_bytes();

					return (bytes + 2u);
				}

				virtual void create_or_add_to_section() override{
					base::create_or_add_to_section();
					for (auto item : operands_)
						item->resolve_label();
				}

				virtual void print(writer_type &writer) const override{
					writer.write(id_to_string(id()));
					writer.write(" ");

					auto is_first = true;
					for (auto item : operands_){
						if (is_first)
							is_first = false;
						else//Print delimiter
							writer.write(", ");

						item->print(writer);
					}
				}

			protected:
				operand_list_type operands_;
			};
		}
	}
}

#endif /* !OOSL_VARIADIC_INSTRUCTION_H */
