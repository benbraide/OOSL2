#include "instruction/instruction_base.h"
#include "vm.h"

void oosl::assembler::vm::add_section(section_id id){
	if (instructions_section_map.find(id) != instructions_section_map.end())
		throw instruction_error::section_redifinition;

	if (active_section != nullptr){//Bundle currently active section
		active_section->bundle();
		active_section = nullptr;
	}

	switch (id){
	case section_id::nil:
		break;//Do nothing
	default:
		active_section = (instructions_section_map[id] = std::make_shared<instructions_section>(id)).get();
		break;
	}
}

void oosl::assembler::vm::execute(){
	OOSL_REMOVE(thread_states, vm_state::exit);
	while (!OOSL_IS(thread_states, vm_state::exit) && !OOSL_IS(global_states, vm_state::exit)){
		auto next_instruction = instructions.find_instruction(register_.find("rip")->read_qword());
		if (next_instruction == nullptr)
			throw instruction_error::bad_instruction;
		else//Execute instruction
			next_instruction->execute_and_update_instruction_pointer();
	}
}

oosl::assembler::vm_state oosl::assembler::vm::global_states = vm_state::nil;

thread_local oosl::assembler::vm_state oosl::assembler::vm::thread_states = vm_state::nil;

oosl::assembler::vm::size_type oosl::assembler::vm::stack_size = (1024 * 1024);//Default size is 1MB

oosl::assembler::vm::memory_type oosl::assembler::vm::memory;

oosl::assembler::instructions_set oosl::assembler::vm::instructions;

oosl::assembler::vm::instructions_section_map_type oosl::assembler::vm::instructions_section_map;

oosl::assembler::instructions_section *oosl::assembler::vm::active_section = nullptr;

thread_local oosl::assembler::vm::stack_type oosl::assembler::vm::stack;

thread_local oosl::assembler::vm::register_type oosl::assembler::vm::register_;
