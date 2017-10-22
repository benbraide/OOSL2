#pragma once

#ifndef OOSL_VM_H
#define OOSL_VM_H

#include "../memory/memory_register.h"

namespace oosl{
	namespace assembler{
		class vm{
		public:
			typedef oosl::memory::stack stack_type;
			typedef oosl::memory::register_ register_type;

			static thread_local stack_type stack;
			static thread_local register_type register_;
		};
	}
}

#endif /* !OOSL_VM_H */
