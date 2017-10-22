#pragma once

#ifndef OOSL_INT_INSTRUCTION_H
#define OOSL_INT_INSTRUCTION_H

#include "../vm.h"

#include "unary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class int_ : public unary{
			public:
				typedef unary base_type;

				OOSL_INS_CTORS(int_)

				virtual id_type id() const override{
					return id_type::int_;
				}

				virtual void execute() const override{
					//#TODO: Implement
				}
			};
		}
	}
}

#endif /* !OOSL_INT_INSTRUCTION_H */
