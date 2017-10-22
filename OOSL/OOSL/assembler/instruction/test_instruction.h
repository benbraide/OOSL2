#pragma once

#ifndef OOSL_TEST_INSTRUCTION_H
#define OOSL_TEST_INSTRUCTION_H

#include "binary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class test : public binary{
			public:
				typedef binary base_type;

				OOSL_INS_CTORS(test)

				virtual id_type id() const override{
					return id_type::test;
				}

				virtual void execute() const override{
					*left_ = *right_;//Assignment
				}
			};
		}
	}
}

#endif /* !OOSL_TEST_INSTRUCTION_H */
