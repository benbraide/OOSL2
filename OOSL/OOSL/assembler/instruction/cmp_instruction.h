#pragma once

#ifndef OOSL_CMP_INSTRUCTION_H
#define OOSL_CMP_INSTRUCTION_H

#include "../vm.h"

#include "binary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class cmp : public binary{
			public:
				typedef binary base_type;

				OOSL_INS_CTORS(cmp)

				virtual id_type id() const override{
					return id_type::cmp;
				}

				virtual void execute() const override{
					if (*left_ < *right_)//Set less flag
						vm::register_.update_less_flag(false);
					else if (*left_ == *right_)//Set zero flag
						vm::register_.update_zero_flag(false);
					else//Clear flags
						vm::register_.update_zero_flag(true);
				}
			};
		}
	}
}

#endif /* !OOSL_CMP_INSTRUCTION_H */
