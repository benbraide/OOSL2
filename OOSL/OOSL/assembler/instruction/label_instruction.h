#pragma once

#ifndef OOSL_LABEL_INSTRUCTION_H
#define OOSL_LABEL_INSTRUCTION_H

#include "no_operand_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class label : public no_operand{
			public:
				typedef no_operand base_type;

				template <class... args_type>
				explicit label(const std::string &value, args_type &&... args)
					: base_type(std::forward<args_type>(args)...), value_(value){}

				virtual ~label() = default;

				virtual id_type id() const override{
					return id_type::label;
				}

				virtual size_type instruction_bytes() const override{
					return 0u;
				}

				virtual const std::string &label_value() const override{
					return value_;
				}

				virtual void execute() const override{}

				virtual void print(writer_type &writer) const override{
					writer.write(value_).write(":");
				}

			private:
				std::string value_;
			};
		}
	}
}

#endif /* !OOSL_LABEL_INSTRUCTION_H */
