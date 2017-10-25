#pragma once

#ifndef OOSL_VM_H
#define OOSL_VM_H

#include "../memory/memory_register.h"
#include "../memory/memory_collection.h"

#include "instruction_set.h"
#include "instructions_section.h"

namespace oosl{
	namespace assembler{
		enum class vm_state : unsigned int{
			nil				= (0 << 0x0000),
			exit			= (1 << 0x0000),
		};

		class vm{
		public:
			typedef unsigned __int64 uint64_type;
			typedef std::size_t size_type;

			typedef oosl::memory::stack stack_type;
			typedef oosl::memory::register_ register_type;
			typedef oosl::memory::collection memory_type;

			typedef instruction::base instruction_type;
			typedef std::shared_ptr<instruction_type> instruction_ptr_type;
			typedef std::shared_ptr<instructions_section> instructions_section_ptr_type;
			typedef std::unordered_map<section_id, instructions_section_ptr_type> instructions_section_map_type;

			static void set_section(section_id id);

			static instructions_section *find_section(section_id id);

			static void add_instruction(instruction_ptr_type instruction);

			static void bundle();

			static void execute();

			static vm_state global_states;
			static thread_local vm_state thread_states;

			static size_type stack_size;
			static memory_type memory;

			static instructions_set instructions;
			static instructions_section_map_type instructions_section_map;

			static instructions_section *active_section;
			static instruction_type *active_label;
			static instruction_type *active_relative_label;

			static thread_local stack_type stack;
			static thread_local register_type register_;
		};

		OOSL_MAKE_OPERATORS(vm_state);
	}
}

#endif /* !OOSL_VM_H */
