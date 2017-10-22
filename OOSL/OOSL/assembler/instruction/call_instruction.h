#pragma once

#ifndef OOSL_CALL_INSTRUCTION_H
#define OOSL_CALL_INSTRUCTION_H

#include "../vm.h"

#include "unary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class call : public unary{
			public:
				typedef unary base_type;

				OOSL_INS_CTORS(call)

				virtual id_type id() const override{
					return id_type::call;
				}

				virtual void execute() const override{
					//#TODO: Implement
				}
			};
		}
	}
}

#endif /* !OOSL_CALL_INSTRUCTION_H */
