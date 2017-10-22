#pragma once

#ifndef OOSL_MOV_INSTRUCTION_H
#define OOSL_MOV_INSTRUCTION_H

#include "binary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class mov : public binary{
			public:
				OOSL_INS_CTORS(mov)

				virtual id_type id() const override{
					return id_type::mov;
				}

				virtual void execute() const override{
					*left_ = *right_;//Assignment
				}
			};
		}
	}
}

#endif /* !OOSL_MOV_INSTRUCTION_H */
