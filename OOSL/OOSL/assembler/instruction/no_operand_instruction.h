#pragma once

#ifndef OOSL_NO_OPERAND_INSTRUCTION_H
#define OOSL_NO_OPERAND_INSTRUCTION_H

#include "instruction_base.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class no_operand : public base{
			public:
				virtual ~no_operand() = default;

				virtual size_type instruction_bytes() const override{
					return 2u;
				}

				virtual void print(writer_type &writer) const override{
					writer.write(id_to_string(id()));
				}
			};
		}
	}
}

#endif /* !OOSL_NO_OPERAND_INSTRUCTION_H */
