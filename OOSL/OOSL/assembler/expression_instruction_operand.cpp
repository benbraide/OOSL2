#include "expression_instruction_operand.h"

oosl::assembler::expression_instruction_operand::expression_instruction_operand(operator_type op, ptr_type left, ptr_type right)
	: op_(op), left_(left), right_(right){}

oosl::assembler::instruction_operand_type oosl::assembler::expression_instruction_operand::type() const{
	return instruction_operand_type::expression;
}

oosl::assembler::instruction_operand_base::code_type oosl::assembler::expression_instruction_operand::code() const{
	return eval_()->code();
}

void oosl::assembler::expression_instruction_operand::print(writer_type &writer) const{
	left_->print(writer);
	switch (op_){
	case operator_type::add:
		writer.write(" + ");
		break;
	case operator_type::sub:
		writer.write(" - ");
		break;
	case operator_type::mult:
		writer.write(" * ");
		break;
	case operator_type::div:
		writer.write(" / ");
		break;
	case operator_type::mod:
		writer.write(" % ");
		break;
	case operator_type::bit_and:
		writer.write(" & ");
		break;
	case operator_type::bit_or:
		writer.write(" | ");
		break;
	case operator_type::bit_xor:
		writer.write(" ^ ");
		break;
	case operator_type::lshift:
		writer.write(" << ");
		break;
	case operator_type::rshift:
		writer.write(" >> ");
		break;
	default:
		break;
	}
	right_->print(writer);
}

oosl::assembler::instruction_operand_base::ptr_type oosl::assembler::expression_instruction_operand::eval(){
	return eval_();
}

oosl::assembler::instruction_operand_base::ptr_type oosl::assembler::expression_instruction_operand::apply_operator(operator_type op, instruction_operand_base &rhs){
	return eval_()->apply_operator(op, rhs);
}

oosl::assembler::instruction_operand_base::byte_type oosl::assembler::expression_instruction_operand::read_byte() const{
	return eval_()->read_byte();
}

oosl::assembler::instruction_operand_base::word_type oosl::assembler::expression_instruction_operand::read_word() const{
	return eval_()->read_word();
}

oosl::assembler::instruction_operand_base::dword_type oosl::assembler::expression_instruction_operand::read_dword() const{
	return eval_()->read_dword();
}

oosl::assembler::instruction_operand_base::qword_type oosl::assembler::expression_instruction_operand::read_qword() const{
	return eval_()->read_qword();
}

float oosl::assembler::expression_instruction_operand::read_float() const{
	return eval_()->read_float();
}

double oosl::assembler::expression_instruction_operand::read_double() const{
	return eval_()->read_ldouble();
}

long double oosl::assembler::expression_instruction_operand::read_ldouble() const{
	return eval_()->read_ldouble();
}

oosl::assembler::instruction_operand_base::ptr_type oosl::assembler::expression_instruction_operand::eval_() const{
	return left_->apply_operator(op_, *right_);
}
