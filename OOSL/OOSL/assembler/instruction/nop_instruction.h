#pragma once

#ifndef OOSL_NOP_INSTRUCTION_H
#define OOSL_NOP_INSTRUCTION_H

#include "no_operand_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class nop : public no_operand{
			public:
				typedef no_operand base_type;

				OOSL_INS_CTORS(nop)

				virtual id_type id() const override{
					return id_type::nop;
				}

				virtual void execute() const override{}
			};
		}
	}
}

#endif /* !OOSL_NOP_INSTRUCTION_H */
