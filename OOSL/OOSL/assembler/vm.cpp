#include "vm.h"

oosl::assembler::vm::uint64_type oosl::assembler::vm::find_identifier(const std::string &key){
	auto entry = map.find(key);
	return ((entry == map.end()) ? 0u : entry->second);
}

oosl::assembler::vm::size_type oosl::assembler::vm::stack_size = (1024 * 1024);//Default size is 1MB

oosl::assembler::vm::memory_type oosl::assembler::vm::memory;

thread_local oosl::assembler::vm::stack_type oosl::assembler::vm::stack;

thread_local oosl::assembler::vm::register_type oosl::assembler::vm::register_;

thread_local oosl::assembler::vm::map_type oosl::assembler::vm::map;
