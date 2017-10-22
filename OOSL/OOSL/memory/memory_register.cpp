#include "memory_register.h"

oosl::memory::register_::register_()
	: flags_(register_flag::nil){
	add_("rax", "eax", "ax", "al", "ah");
	add_("rbx", "ebx", "bx", "bl", "bh");
	add_("rcx", "ecx", "cx", "cl", "ch");
	add_("rdx", "edx", "dx", "dl", "dh");

	add_<qword_type, dword_type>("eip", "ip", "");
	add_<qword_type, dword_type>("esp", "sp", "");
	add_<qword_type, dword_type>("ebp", "bp", "");

	add_<qword_type, dword_type>("esi", "si", "");
	add_<qword_type, dword_type>("edi", "di", "");

	add_range_<qword_type>(0, 7);
	add_range_<dword_type>(8, 16);
	add_range_<word_type>(17, 25);
	add_range_<byte_type>(26, 34);

	add_range_<float>(35, 43);
	add_range_<double>(44, 52);
	add_range_<long double>(53, 61);
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

void oosl::memory::register_::add_(const std::string &name, const std::string &_32, const std::string &_16, const std::string &low, const std::string &high){
	auto value = std::make_shared<register_value<qword_type>>(name);

	auto _32_value = std::make_shared<register_ref_value<dword_type>>(_32, value->low<dword_type>());
	auto _16_value = std::make_shared<register_ref_value<word_type>>(_16, _32_value->low<word_type>());

	map_[low] = std::make_shared<register_ref_value<byte_type>>(low, _16_value->low<byte_type>());
	map_[high] = std::make_shared<register_ref_value<byte_type>>(high, _16_value->high<byte_type>());

	map_[_16] = _16_value;
	map_[_32] = _32_value;

	map_[name] = value;
}
