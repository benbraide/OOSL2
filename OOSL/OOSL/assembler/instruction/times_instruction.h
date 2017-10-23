#pragma once

#ifndef OOSL_TIMES_INSTRUCTION_H
#define OOSL_TIMES_INSTRUCTION_H

#include "binary_instruction.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class times : public base{
			public:
				typedef std::shared_ptr<base> ptr_type;

				times(unsigned int left, ptr_type right)
					: left_(left), right_(right){}

				virtual ~times() = default;

				virtual id_type id() const override{
					return id_type::times;
				}

				virtual size_type instruction_bytes() const override{
					return (left_ * right_->instruction_bytes());
				}

				virtual void execute_and_update_instruction_pointer() const override{
					execute();
				}

				virtual void execute() const override{
					for (auto i = 0u; i < left_; ++i)
						right_->execute_and_update_instruction_pointer();//Execute instruction specified times
				}

			private:
				unsigned int left_;
				ptr_type right_;
			};
		}
	}
}

#endif /* !OOSL_TIMES_INSTRUCTION_H */
