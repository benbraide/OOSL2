#include "register_value_instruction_operand.h"

oosl::assembler::register_value_instruction_operand::register_value_instruction_operand(register_value_type &value)
	: value_(&value){}

bool oosl::assembler::register_value_instruction_operand::operator==(const instruction_operand_base &rhs) const{
	return comp_(false, rhs);
}

bool oosl::assembler::register_value_instruction_operand::operator<(const instruction_operand_base &rhs) const{
	return comp_(true, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator>>=(const instruction_operand_base &rhs){
	return eval_(operator_type::rshift, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator<<=(const instruction_operand_base &rhs){
	return eval_(operator_type::lshift, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator^=(const instruction_operand_base &rhs){
	return eval_(operator_type::bit_xor, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator|=(const instruction_operand_base &rhs){
	return eval_(operator_type::bit_or, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator&=(const instruction_operand_base &rhs){
	return eval_(operator_type::bit_and, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator%=(const instruction_operand_base &rhs){
	return eval_(operator_type::mod, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator/=(const instruction_operand_base &rhs){
	return eval_(operator_type::div, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator*=(const instruction_operand_base &rhs){
	return eval_(operator_type::mult, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator-=(const instruction_operand_base &rhs){
	return eval_(operator_type::sub, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator+=(const instruction_operand_base &rhs){
	return eval_(operator_type::add, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::operator=(const instruction_operand_base &rhs){
	switch (value_->type()){
	case oosl::memory::register_value_type::byte:
		return assign_(rhs.read_byte());
	case oosl::memory::register_value_type::word:
		return assign_(rhs.read_word());
	case oosl::memory::register_value_type::dword:
		return assign_(rhs.read_dword());
	case oosl::memory::register_value_type::qword:
		return assign_(rhs.read_qword());
	case oosl::memory::register_value_type::float_:
		return assign_(rhs.read_float());
	case oosl::memory::register_value_type::double_:
		return assign_(rhs.read_double());
	case oosl::memory::register_value_type::ldouble:
		return assign_(rhs.read_ldouble());
	default:
		break;
	}

	throw instruction_error::bad_operation;
}

oosl::assembler::instruction_operand_base::byte_type oosl::assembler::register_value_instruction_operand::read_byte() const{
	return value_->read_byte();
}

oosl::assembler::instruction_operand_base::word_type oosl::assembler::register_value_instruction_operand::read_word() const{
	return value_->read_word();
}

oosl::assembler::instruction_operand_base::dword_type oosl::assembler::register_value_instruction_operand::read_dword() const{
	return value_->read_dword();
}

oosl::assembler::instruction_operand_base::qword_type oosl::assembler::register_value_instruction_operand::read_qword() const{
	return value_->read_qword();
}

float oosl::assembler::register_value_instruction_operand::read_float() const{
	return value_->read_float();
}

double oosl::assembler::register_value_instruction_operand::read_double() const{
	return value_->read_double();
}

long double oosl::assembler::register_value_instruction_operand::read_ldouble() const{
	return value_->read_ldouble();
}

oosl::assembler::instruction_operand_base &oosl::assembler::register_value_instruction_operand::eval_(operator_type op, const instruction_operand_base &rhs){
	switch (value_->type()){
	case oosl::memory::register_value_type::byte:
		return eval_integral_(op, value_->read<byte_type>(), rhs.read_byte());
	case oosl::memory::register_value_type::word:
		return eval_integral_(op, value_->read<word_type>(), rhs.read_word());
	case oosl::memory::register_value_type::dword:
		return eval_integral_(op, value_->read<dword_type>(), rhs.read_dword());
	case oosl::memory::register_value_type::qword:
		return eval_integral_(op, value_->read<qword_type>(), rhs.read_qword());
	case oosl::memory::register_value_type::float_:
		return eval_(op, value_->read<float>(), rhs.read_float());
	case oosl::memory::register_value_type::double_:
		return eval_(op, value_->read<double>(), rhs.read_double());
	case oosl::memory::register_value_type::ldouble:
		return eval_(op, value_->read<long double>(), rhs.read_ldouble());
	default:
		break;
	}

	throw instruction_error::bad_operation;
}

bool oosl::assembler::register_value_instruction_operand::comp_(bool less, const instruction_operand_base &rhs) const{
	switch (value_->type()){
	case oosl::memory::register_value_type::byte:
		return comp_(less, value_->read<byte_type>(), rhs.read_byte());
	case oosl::memory::register_value_type::word:
		return comp_(less, value_->read<word_type>(), rhs.read_word());
	case oosl::memory::register_value_type::dword:
		return comp_(less, value_->read<dword_type>(), rhs.read_dword());
	case oosl::memory::register_value_type::qword:
		return comp_(less, value_->read<qword_type>(), rhs.read_qword());
	case oosl::memory::register_value_type::float_:
		return comp_(less, value_->read<float>(), rhs.read_float());
	case oosl::memory::register_value_type::double_:
		return comp_(less, value_->read<double>(), rhs.read_double());
	case oosl::memory::register_value_type::ldouble:
		return comp_(less, value_->read<long double>(), rhs.read_ldouble());
	default:
		break;
	}

	throw instruction_error::bad_operation;
}
