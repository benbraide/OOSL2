#include "memory_instruction_operand.h"

oosl::assembler::memory_instruction_operand::memory_instruction_operand(code_type code, ptr_type value)
	: code_(code), value_(value){}

oosl::assembler::instruction_operand_type oosl::assembler::memory_instruction_operand::type() const{
	return instruction_operand_type::memory;
}

oosl::assembler::instruction_operand_base::code_type oosl::assembler::memory_instruction_operand::code() const{
	return code_;
}

void oosl::assembler::memory_instruction_operand::print(writer_type &writer) const{
	writer.write("[");
	value_->print(writer);
	writer.write("]");
}

bool oosl::assembler::memory_instruction_operand::operator==(const instruction_operand_base &rhs) const{
	return comp_(false, rhs);
}

bool oosl::assembler::memory_instruction_operand::operator<(const instruction_operand_base &rhs) const{
	return comp_(true, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator>>=(const instruction_operand_base &rhs){
	return eval_(operator_type::rshift, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator<<=(const instruction_operand_base &rhs){
	return eval_(operator_type::lshift, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator^=(const instruction_operand_base &rhs){
	return eval_(operator_type::bit_xor, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator|=(const instruction_operand_base &rhs){
	return eval_(operator_type::bit_or, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator&=(const instruction_operand_base &rhs){
	return eval_(operator_type::bit_and, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator%=(const instruction_operand_base &rhs){
	return eval_(operator_type::mod, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator/=(const instruction_operand_base &rhs){
	return eval_(operator_type::div, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator*=(const instruction_operand_base &rhs){
	return eval_(operator_type::mult, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator-=(const instruction_operand_base &rhs){
	return eval_(operator_type::sub, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator+=(const instruction_operand_base &rhs){
	return eval_(operator_type::add, rhs);
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::operator=(const instruction_operand_base &rhs){
	switch ((code_ == code_type::unknown) ? rhs.code() : code_){
	case code_type::byte:
		return assign_(rhs.read_byte());
	case code_type::word:
		return assign_(rhs.read_word());
	case code_type::dword:
		return assign_(rhs.read_dword());
	case code_type::qword:
		return assign_(rhs.read_qword());
	case code_type::float_:
		return assign_(rhs.read_float());
	case code_type::double_:
		return assign_(rhs.read_double());
	case code_type::ldouble:
		return assign_(rhs.read_ldouble());
	default:
		break;
	}

	throw instruction_error::bad_operation;
}

oosl::assembler::instruction_operand_base::byte_type oosl::assembler::memory_instruction_operand::read_byte() const{
	return read_<byte_type>();
}

oosl::assembler::instruction_operand_base::word_type oosl::assembler::memory_instruction_operand::read_word() const{
	return read_<word_type>();
}

oosl::assembler::instruction_operand_base::dword_type oosl::assembler::memory_instruction_operand::read_dword() const{
	return read_<dword_type>();
}

oosl::assembler::instruction_operand_base::qword_type oosl::assembler::memory_instruction_operand::read_qword() const{
	return read_<qword_type>();
}

float oosl::assembler::memory_instruction_operand::read_float() const{
	return read_<float>();
}

double oosl::assembler::memory_instruction_operand::read_double() const{
	return read_<double>();
}

long double oosl::assembler::memory_instruction_operand::read_ldouble() const{
	return read_<long double>();
}

oosl::assembler::instruction_operand_base &oosl::assembler::memory_instruction_operand::eval_(operator_type op, const instruction_operand_base &rhs){
	switch ((code_ == code_type::unknown) ? rhs.code() : code_){
	case code_type::byte:
		return eval_integral_(op, read_<byte_type>(), rhs.read_byte());
	case code_type::word:
		return eval_integral_(op, read_<word_type>(), rhs.read_word());
	case code_type::dword:
		return eval_integral_(op, read_<dword_type>(), rhs.read_dword());
	case code_type::qword:
		return eval_integral_(op, read_<qword_type>(), rhs.read_qword());
	case code_type::float_:
		return eval_(op, read_<float>(), rhs.read_float());
	case code_type::double_:
		return eval_(op, read_<double>(), rhs.read_double());
	case code_type::ldouble:
		return eval_(op, read_<long double>(), rhs.read_ldouble());
	default:
		break;
	}

	throw instruction_error::bad_operation;
}

bool oosl::assembler::memory_instruction_operand::comp_(bool less, const instruction_operand_base &rhs) const{
	switch ((code_ == code_type::unknown) ? rhs.code() : code_){
	case code_type::byte:
		return comp_(less, read_<byte_type>(), rhs.read_byte());
	case code_type::word:
		return comp_(less, read_<word_type>(), rhs.read_word());
	case code_type::dword:
		return comp_(less, read_<dword_type>(), rhs.read_dword());
	case code_type::qword:
		return comp_(less, read_<qword_type>(), rhs.read_qword());
	case code_type::float_:
		return comp_(less, read_<float>(), rhs.read_float());
	case code_type::double_:
		return comp_(less, read_<double>(), rhs.read_double());
	case code_type::ldouble:
		return comp_(less, read_<long double>(), rhs.read_ldouble());
	default:
		break;
	}

	throw instruction_error::bad_operation;
}
