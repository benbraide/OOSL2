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
	oosl::assembler::vm::rsp->write_qword(address_ = block->address);

	data_ = block->data.get();
	max_ = (data_ + data_size);
}

char *oosl::memory::stack::begin() const{
	return data_;
}

void oosl::memory::stack::push_(const char *value, size_type size){
	auto current_address = oosl::assembler::vm::rsp->read_qword();
	auto next_address = (current_address + size);//Address after write

	if ((data_ + (next_address - address_)) > max_)
		throw stack_error::overflow;//Overflow

	memcpy(data_ + current_address, value, size);//Copy bytes
	oosl::assembler::vm::rsp->write_qword(next_address);//Update register value
}

void oosl::memory::stack::pop_(char *value, size_type size){
	auto current_address = oosl::assembler::vm::rsp->read_qword();
	if ((current_address - address_) < size)
		throw stack_error::underflow;//Error

	memcpy(value, data_ + (current_address - size), size);//Copy bytes
	oosl::assembler::vm::rsp->write_qword(current_address - size);//Update register value
}
