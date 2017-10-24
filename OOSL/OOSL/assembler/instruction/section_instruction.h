#pragma once

#ifndef OOSL_SECTION_INSTRUCTION_H
#define OOSL_SECTION_INSTRUCTION_H

#include "../instructions_section.h"

#include "instruction_base.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class section : public base{
			public:
				explicit section(section_id id)
					: id_(id){}

				virtual ~section() = default;

				virtual id_type id() const override{
					return id_type::section;
				}

				virtual size_type instruction_bytes() const override{
					return 0u;
				}

				virtual void create_or_add_to_section() override{
					assembler::vm::set_section(id_);
				}

				virtual void execute() const override{}

				virtual void print(writer_type &writer) const override{
					writer.write("section ");
					switch (id_){
					case section_id::rodata:
						writer.write(".rodata");
						break;
					case section_id::data:
						writer.write(".data");
						break;
					case section_id::text:
						writer.write(".text");
						break;
					default:
						writer.write(".<unknown>");
						break;
					}
				}

			protected:
				section_id id_;
			};
		}
	}
}

#endif /* !OOSL_SECTION_INSTRUCTION_H */
