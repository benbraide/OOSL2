#include "../vm.h"

#include "sys_call_interrupt.h"

void oosl::assembler::interrupt::sys_call::handle(){
	switch (static_cast<id>(assembler::vm::register_.find("eax")->read_dword())){
	case id::exit:
		assembler::vm::exit(static_cast<int>(assembler::vm::register_.find("ebx")->read_dword()));
		break;
	case id::write:
		break;
	case id::read:
		break;
	default:
		throw error::sys_call_not_found;
		break;
	}
}
