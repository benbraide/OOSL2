#pragma once

#ifndef OOSL_LABEL_INSTRUCTION_H
#define OOSL_LABEL_INSTRUCTION_H

#include "no_operand_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class label : public no_operand{
			public:
				template <class... args_type>
				explicit label(const std::string &value, args_type &&... args)
					: no_operand(std::forward<args_type>(args)...), value_(value){}

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

				virtual const std::string &absolute_label_value() const override{
					return value_;
				}

				virtual void create_or_add_to_section() override{
					assembler::vm::active_label = this;
					assembler::vm::active_relative_label = nullptr;
					no_operand::create_or_add_to_section();
				}

				virtual void execute() const override{}

				virtual void print(writer_type &writer) const override{
					writer.write(value_).write(":");
				}

			protected:
				std::string value_;
			};

			class relative_label : public label{
			public:
				template <class... args_type>
				explicit relative_label(const std::string &value, args_type &&... args)
					: label(value, std::forward<args_type>(args)...){}

				virtual ~relative_label() = default;

				virtual const std::string &absolute_label_value() const override{
					return absolute_value_;
				}

				virtual void create_or_add_to_section() override{
					assembler::vm::active_relative_label = this;
					if (assembler::vm::active_label == nullptr)
						absolute_value_ = value_;
					else//Construct absolute label
						absolute_value_ = (assembler::vm::active_label->absolute_label_value() + "." + value_);
					no_operand::create_or_add_to_section();
				}

				virtual void print(writer_type &writer) const override{
					writer.write(".").write(value_).write(":");
				}

			private:
				std::string absolute_value_;
			};
		}
	}
}

#endif /* !OOSL_LABEL_INSTRUCTION_H */
