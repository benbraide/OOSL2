#include "grouped_expression_instruction_operand.h"

oosl::assembler::grouped_expression_instruction_operand::grouped_expression_instruction_operand(ptr_type value)
	: value_(value){}

oosl::assembler::instruction_operand_type oosl::assembler::grouped_expression_instruction_operand::type() const{
	return value_->type();
}

oosl::assembler::instruction_operand_base::code_type oosl::assembler::grouped_expression_instruction_operand::code() const{
	return value_->code();
}

oosl::assembler::instruction_operand_base::size_type oosl::assembler::grouped_expression_instruction_operand::instruction_bytes() const{
	return value_->instruction_bytes();
}

void oosl::assembler::grouped_expression_instruction_operand::resolve_constant(){
	value_->resolve_constant();
}

void oosl::assembler::grouped_expression_instruction_operand::print(writer_type &writer) const{
	writer.write("(");
	value_->print(writer);
	writer.write(")");
}

oosl::assembler::instruction_operand_base::ptr_type oosl::assembler::grouped_expression_instruction_operand::eval(){
	return value_->eval();
}

oosl::assembler::instruction_operand_base::ptr_type oosl::assembler::grouped_expression_instruction_operand::apply_operator(operator_type op, instruction_operand_base &rhs){
	return value_->apply_operator(op, rhs);
}

oosl::assembler::instruction_operand_base::byte_type oosl::assembler::grouped_expression_instruction_operand::read_byte() const{
	return value_->read_byte();
}

oosl::assembler::instruction_operand_base::word_type oosl::assembler::grouped_expression_instruction_operand::read_word() const{
	return value_->read_word();
}

oosl::assembler::instruction_operand_base::dword_type oosl::assembler::grouped_expression_instruction_operand::read_dword() const{
	return value_->read_dword();
}

oosl::assembler::instruction_operand_base::qword_type oosl::assembler::grouped_expression_instruction_operand::read_qword() const{
	return value_->read_qword();
}

float oosl::assembler::grouped_expression_instruction_operand::read_float() const{
	return value_->read_float();
}

double oosl::assembler::grouped_expression_instruction_operand::read_double() const{
	return value_->read_double();
}

long double oosl::assembler::grouped_expression_instruction_operand::read_ldouble() const{
	return value_->read_ldouble();
}
