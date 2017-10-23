#pragma once

#ifndef OOSL_VM_H
#define OOSL_VM_H

#include "../memory/memory_register.h"
#include "../memory/memory_collection.h"

namespace oosl{
	namespace assembler{
		class vm{
		public:
			typedef unsigned __int64 uint64_type;
			typedef std::size_t size_type;

			typedef oosl::memory::stack stack_type;
			typedef oosl::memory::register_ register_type;
			typedef oosl::memory::collection memory_type;

			typedef std::unordered_map<std::string, uint64_type> map_type;

			static uint64_type find_identifier(const std::string &key);

			static size_type stack_size;
			static memory_type memory;

			static thread_local stack_type stack;
			static thread_local register_type register_;

			static thread_local map_type map;
		};
	}
}

#endif /* !OOSL_VM_H */
