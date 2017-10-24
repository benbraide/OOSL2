#include "instruction/instruction_base.h"
#include "instructions_section.h"

oosl::assembler::instructions_section::instructions_section(section_id id)
	: id_(id), next_(0){}

void oosl::assembler::instructions_section::add(instruction_ptr_type instruction){
	if (instruction->id() != assembler::instruction::id::label){
		map_[next_] = instruction;
		next_ += instruction->instruction_bytes();
	}
	else//Label
		label_map_[next_] = instruction;
}

void oosl::assembler::instructions_section::bundle(){
	auto start_address = allocate_memory_();
	if (start_address == 0u)
		return;//Empty section

	vm::instructions.bundle(start_address, map_, label_map_);
	if (id_ != section_id::text){//Data sections -- allocate memory
		vm::register_.find("rip")->write_qword(start_address);
		for (auto &item : map_)//Execute memory instructions
			item.second->execute_and_update_instruction_pointer();
	}
}

oosl::assembler::instructions_section::uint64_type oosl::assembler::instructions_section::allocate_memory_(){
	return ((next_ == 0u) ? 0u : vm::memory.reserve(next_));
}
