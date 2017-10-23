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

				OOSL_INS_CTORS(label)

				virtual id_type id() const override{
					return id_type::label;
				}

				virtual size_type instruction_bytes() const override{
					return 0u;
				}

				virtual void execute() const override{}
			};
		}
	}
}

#endif /* !OOSL_LABEL_INSTRUCTION_H */
