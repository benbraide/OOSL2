#pragma once

#ifndef OOSL_INSTRUCTION_SET_H
#define OOSL_INSTRUCTION_SET_H

#include <string>
#include <unordered_map>

namespace oosl{
	namespace assembler{
		namespace instruction{
			class base;
		}

		class instructions_set{
		public:
			typedef unsigned __int64 uint64_type;
			typedef assembler::instruction::base instruction_type;

			typedef std::shared_ptr<instruction_type> instruction_ptr_type;
			typedef std::unordered_map<std::string, uint64_type> string_map_type;

			typedef std::unordered_map<uint64_type, instruction_ptr_type> map_type;
			typedef std::unordered_map<instruction_ptr_type, uint64_type> alt_map_type;

			virtual ~instructions_set() = default;

			virtual void bundle(uint64_type start_address, map_type &map, alt_map_type &label_map);

			virtual void resolve_constant();

			virtual instruction_type *find_instruction(uint64_type address);

			virtual uint64_type find_label(const std::string &key);

		protected:
			map_type map_;
			string_map_type label_map_;
		};
	}
}

#endif /* !OOSL_INSTRUCTION_SET_H */
