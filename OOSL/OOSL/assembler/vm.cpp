#include "instruction/instruction_base.h"
#include "vm.h"

void oosl::assembler::vm::set_section(section_id id){
	auto entry = instructions_section_map.find(id);
	if (entry != instructions_section_map.end())//Use existing
		active_section = entry->second.get();
	else if (id != section_id::nil)//Create new
		active_section = (instructions_section_map[id] = std::make_shared<instructions_section>(id)).get();
}

oosl::assembler::instructions_section *oosl::assembler::vm::find_section(section_id id){
	auto entry = instructions_section_map.find(id);
	return ((entry == instructions_section_map.end()) ? nullptr : entry->second.get());
}

void oosl::assembler::vm::bundle(){
	auto section = find_section(section_id::rodata);//Read-only data
	if (section != nullptr)
		section->bundle();

	if ((section = find_section(section_id::data)) != nullptr)//Data
		section->bundle();

	if ((section = find_section(section_id::text)) != nullptr)//Executable
		section->bundle();
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
