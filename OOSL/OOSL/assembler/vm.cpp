#include "vm.h"

oosl::assembler::vm::size_type oosl::assembler::vm::stack_size = (1024 * 1024);//Default size is 1MB

oosl::assembler::vm::memory_type oosl::assembler::vm::memory;

thread_local oosl::assembler::vm::stack_type oosl::assembler::vm::stack;

thread_local oosl::assembler::vm::register_type oosl::assembler::vm::register_;
