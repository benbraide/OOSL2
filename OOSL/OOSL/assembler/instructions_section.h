#pragma once

#ifndef OOSL_INSTRUCTIONS_SECTION_H
#define OOSL_INSTRUCTIONS_SECTION_H

#include <unordered_map>

namespace oosl{
	namespace assembler{
		namespace instruction{
			class base;
		}

		enum class section_id{
			nil,
			rodata,
			data,
			text,
		};

		class instructions_section{
		public:
			typedef unsigned __int64 uint64_type;

			typedef std::shared_ptr<instruction::base> instruction_ptr_type;
			typedef std::unordered_map<uint64_type, instruction_ptr_type> map_type;

			explicit instructions_section(section_id id);

			virtual ~instructions_section() = default;

			virtual void add(instruction_ptr_type instruction);

			virtual void bundle();

		protected:
			virtual uint64_type allocate_memory_();

			section_id id_;
			uint64_type next_;
			map_type map_;
			map_type label_map_;
		};
	}
}

#endif /* !OOSL_INSTRUCTIONS_SECTION_H */
