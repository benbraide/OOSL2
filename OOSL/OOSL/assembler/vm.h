#pragma once

#ifndef OOSL_VM_H
#define OOSL_VM_H

#include "../memory/memory_register.h"
#include "../memory/memory_collection.h"

namespace oosl{
	namespace assembler{
		class vm{
		public:
			typedef std::size_t size_type;

			typedef oosl::memory::stack stack_type;
			typedef oosl::memory::register_ register_type;
			typedef oosl::memory::collection memory_type;

			static size_type stack_size;
			static memory_type memory;

			static thread_local stack_type stack;
			static thread_local register_type register_;
		};
	}
}

#endif /* !OOSL_VM_H */
