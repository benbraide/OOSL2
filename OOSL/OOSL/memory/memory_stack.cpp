#include "../assembler/vm.h"

#include "memory_stack.h"

oosl::memory::stack::stack(size_type data_size)
	: address_(0), data_(nullptr), max_(nullptr){
	if (data_size != 0u)//Allocate memory
		create(data_size);
}

void oosl::memory::stack::create(size_type data_size){
	if (data_ != nullptr)
		return;//Already allocated

	if (data_size == 0u)//Use size in VM
		data_size = assembler::vm::stack_size;

	auto block = assembler::vm::memory.allocate(data_size);
	assembler::vm::register_.find("esp")->write_qword(address_ = block->address);

	data_ = block->data.get();
	max_ = (data_ + data_size);
}

char *oosl::memory::stack::begin() const{
	return data_;
}
