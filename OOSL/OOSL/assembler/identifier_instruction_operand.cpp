#include "instruction/instruction_base.h"
#include "identifier_instruction_operand.h"

oosl::assembler::identifier_instruction_operand::identifier_instruction_operand(const std::string &value)
	: value_(value), target_(0){}

oosl::assembler::instruction_operand_type oosl::assembler::identifier_instruction_operand::type() const{
	return instruction_operand_type::identifier;
}

oosl::assembler::instruction_operand_base::code_type oosl::assembler::identifier_instruction_operand::code() const{
	return code_type::qword;
}

oosl::assembler::instruction_operand_base::size_type oosl::assembler::identifier_instruction_operand::instruction_bytes() const{
	return sizeof(qword_type);
}

void oosl::assembler::identifier_instruction_operand::resolve_label(){
	if (vm::active_relative_label != nullptr && vm::active_relative_label->label_value() == value_)
		resolved_ = vm::active_relative_label->absolute_label_value();//Use absolute label
	else//Absolute
		resolved_ = value_;
}

void oosl::assembler::identifier_instruction_operand::resolve_constant(){
	try{
		target_ = read_();
	}
	catch (...){//Intercept exception
		target_ = 0u;
	}
}

void oosl::assembler::identifier_instruction_operand::print(writer_type &writer) const{
	writer.write(value_);
}

oosl::assembler::instruction_operand_base::ptr_type oosl::assembler::identifier_instruction_operand::apply_operator(operator_type op, instruction_operand_base &rhs){
	auto resolved_rhs = rhs.eval();
	if (resolved_rhs->type() != instruction_operand_type::constant_value)
		throw instruction_error::bad_operation;

	return eval_integral_(op, read_(), resolved_rhs->read_qword());
}

oosl::assembler::instruction_operand_base::byte_type oosl::assembler::identifier_instruction_operand::read_byte() const{
	return static_cast<byte_type>(read_());
}

oosl::assembler::instruction_operand_base::word_type oosl::assembler::identifier_instruction_operand::read_word() const{
	return static_cast<word_type>(read_());
}

oosl::assembler::instruction_operand_base::dword_type oosl::assembler::identifier_instruction_operand::read_dword() const{
	return static_cast<dword_type>(read_());
}

oosl::assembler::instruction_operand_base::qword_type oosl::assembler::identifier_instruction_operand::read_qword() const{
	return static_cast<qword_type>(read_());
}

float oosl::assembler::identifier_instruction_operand::read_float() const{
	return static_cast<float>(read_());
}

double oosl::assembler::identifier_instruction_operand::read_double() const{
	return static_cast<double>(read_());
}

long double oosl::assembler::identifier_instruction_operand::read_ldouble() const{
	return static_cast<long double>(read_());
}

oosl::assembler::instruction_operand_base::qword_type oosl::assembler::identifier_instruction_operand::read_() const{
	if (target_ != 0u)//Use cached value
		return target_;

	auto value = vm::instructions.find_label(resolved_);
	if (value == 0u)//Identifier not found
		throw instruction_error::bad_identifier;

	return value;
}

oosl::assembler::absolute_identifier_instruction_operand::absolute_identifier_instruction_operand(const std::string &value)
	: identifier_instruction_operand(value){}

void oosl::assembler::absolute_identifier_instruction_operand::resolve_label(){
	resolved_ = value_;
}
