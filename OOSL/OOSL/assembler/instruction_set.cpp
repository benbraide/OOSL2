#include "instruction/instruction_base.h"
#include "instruction_set.h"

void oosl::assembler::instructions_set::bundle(uint64_type start_address, map_type &map, alt_map_type &label_map){
	for (auto &item : map)//Add items with absolute addresses
		map_[item.first + start_address] = item.second;

	for (auto &item : label_map)//Add labels to absolute addresses
		label_map_[item.first->absolute_label_value()] = (item.second + start_address);
}

void oosl::assembler::instructions_set::resolve_constant(){
	for (auto &item : map_)//Resolve instructions
		item.second->resolve_constant();
}

oosl::assembler::instructions_set::instruction_type *oosl::assembler::instructions_set::find_instruction(uint64_type address){
	auto entry = map_.find(address);
	return ((entry == map_.end()) ? nullptr : entry->second.get());
}

oosl::assembler::instructions_set::uint64_type oosl::assembler::instructions_set::find_label(const std::string &key){
	auto entry = label_map_.find(key);
	return ((entry == label_map_.end()) ? 0u : entry->second);
}
