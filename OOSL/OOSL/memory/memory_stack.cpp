#include "memory_stack.h"

oosl::memory::stack::stack(size_type data_size)
	: data_(std::make_unique<char[]>(data_size)){}

char *oosl::memory::stack::begin() const{
	return data_.get();
}
