#include "../assembler/vm.h"
#include "memory_register.h"

oosl::memory::register_::register_()
	: flags_(register_flag::nil){
	add_("rax", "r0", "eax", "ax", "al", "ah");
	add_("rbx", "r1", "ebx", "bx", "bl", "bh");
	add_("rcx", "r2", "ecx", "cx", "cl", "ch");
	add_("rdx", "r3", "edx", "dx", "dl", "dh");

	add_("rsp", "r4", "esp", "sp", "", "");
	add_("rbp", "r5", "ebp", "bp", "", "");
	add_("rsi", "r6", "esi", "si", "", "");
	add_("rdi", "r7", "edi", "di", "", "");
	add_("rip", "r8", "eip", "ip", "", "");

	add_qword_(9, 15);
	add_float_<long double>("xmm", 0, 7);

	oosl::assembler::vm::rip = find("rip");
	oosl::assembler::vm::rsp = find("rsp");
	oosl::assembler::vm::rbp = find("rbp");
}

oosl::memory::register_value_base *oosl::memory::register_::find(std::string key) const{
	to_lower(key);

	auto entry = map_.find(key);
	if (entry == map_.end())//Error
		throw register_error::not_found;

	return entry->second.get();
}

void oosl::memory::register_::update_flag(register_flag flag, bool clear){
	if (clear)
		OOSL_REMOVE(flags_, flag);
	else//Set
		OOSL_SET(flags_, flag);
}

void oosl::memory::register_::update_zero_flag(bool clear){
	update_flag(register_flag::less, true);
	update_flag(register_flag::zero, clear);
}

void oosl::memory::register_::update_less_flag(bool clear){
	update_flag(register_flag::zero, true);
	update_flag(register_flag::less, clear);
}

bool oosl::memory::register_::has_flag(register_flag flag) const{
	return OOSL_IS(flags_, flag);
}

bool oosl::memory::register_::has_zero_flag() const{
	return has_flag(register_flag::zero);
}

bool oosl::memory::register_::has_less_flag() const{
	return has_flag(register_flag::less);
}

void oosl::memory::register_::to_lower(std::string &value){
	for (auto &c : value)
		c = tolower(c);
}

void oosl::memory::register_::add_(const std::string &name, const std::string &alias, const std::string &_32, const std::string &_16, const std::string &low, const std::string &high){
	typedef register_value<qword_type> qword_register_value_type;
	typedef register_ref_value<dword_type> dword_register_value_type;
	typedef register_ref_value<word_type> word_register_value_type;
	typedef register_ref_value<byte_type> byte_register_value_type;

	auto value = std::make_shared<qword_register_value_type>(name);
	auto _32_value = std::make_shared<dword_register_value_type>(_32, value->low<dword_type>());
	auto _16_value = std::make_shared<word_register_value_type>(_16, value->low<word_type>());
	auto _8_value = std::make_shared<byte_register_value_type>(low, value->low<byte_type>());

	if (!low.empty())
		map_[low] = _8_value;

	if (!high.empty())
		map_[high] = std::make_shared<byte_register_value_type>(high, _16_value->high<byte_type>());

	map_[_16] = _16_value;
	map_[_32] = _32_value;

	map_[name] = value;
	if (!alias.empty()){
		map_[alias + "b"] = _8_value;
		map_[alias + "w"] = _16_value;
		map_[alias + "d"] = _32_value;
		map_[alias] = value;
	}
}

void oosl::memory::register_::add_qword_(int from, int to){
	typedef register_value<qword_type> qword_register_value_type;
	typedef register_ref_value<dword_type> dword_register_value_type;
	typedef register_ref_value<word_type> word_register_value_type;
	typedef register_ref_value<byte_type> byte_register_value_type;

	std::string name;
	std::shared_ptr<qword_register_value_type> value;
	std::shared_ptr<dword_register_value_type> dword_value;
	std::shared_ptr<word_register_value_type> word_value;
	std::shared_ptr<byte_register_value_type> byte_value;

	for (; from <= to; ++from){//Add entries
		name = ("r" + std::to_string(from));
		value = std::make_shared<qword_register_value_type>(name);

		dword_value = std::make_shared<dword_register_value_type>(name + "d", value->low<dword_type>());
		word_value = std::make_shared<word_register_value_type>(name + "w", value->low<word_type>());
		byte_value = std::make_shared<byte_register_value_type>(name + "b", value->low<byte_type>());

		map_[name + "b"] = byte_value;
		map_[name + "w"] = word_value;
		map_[name + "d"] = dword_value;
		map_[name] = value;
	}
}
