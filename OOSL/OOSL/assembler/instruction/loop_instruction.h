#pragma once

#ifndef OOSL_LOOP_INSTRUCTION_H
#define OOSL_LOOP_INSTRUCTION_H

#include "../vm.h"

#include "unary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class loop : public unary{
			public:
				typedef unary base_type;

				OOSL_INS_CTORS(loop)

				virtual id_type id() const override{
					return id_type::loop;
				}

				virtual void execute() const override{
					//#TODO: Implement
				}
			};
		}
	}
}

#endif /* !OOSL_LOOP_INSTRUCTION_H */
