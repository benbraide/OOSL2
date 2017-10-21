#include "memory_register.h"

oosl::memory::register_::register_(){
	for (auto index = 0; index < 33; ++index)//Add 64 bit entries
		map_["$r" + std::to_string(index)] = std::make_shared<register_value<qword_type>>();

	for (auto index = 33; index < 41; ++index)//Add 32 bit entries
		map_["$r" + std::to_string(index)] = std::make_shared<register_value<dword_type>>();

	for (auto index = 41; index < 47; ++index)//Add 16 bit entries
		map_["$r" + std::to_string(index)] = std::make_shared<register_value<word_type>>();

	for (auto index = 47; index < 53; ++index)//Add 8 bit entries
		map_["$r" + std::to_string(index)] = std::make_shared<register_value<byte_type>>();

	map_["$sp"] = map_["$r29"];//Stack Pointer
	map_["$sf"] = map_["$r30"];//Stack Frame
	map_["$ip"] = map_["$r31"];//Instruction Pointer
}

oosl::memory::register_value_base *oosl::memory::register_::find(const std::string &key) const{
	auto entry = map_.find(key);
	if (entry == map_.end())//Error
		throw register_error::not_found;
	return entry->second.get();
}
