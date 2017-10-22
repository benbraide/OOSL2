#pragma once

#ifndef OOSL_INSTRUCTION_BASE_H
#define OOSL_INSTRUCTION_BASE_H

#include "../instruction_operand_base.h"

#include "instruction_id.h"

#define OOSL_INS_CTORS(name)						\
template <class... args_type>						\
explicit name(args_type &&... args)					\
	: base_type(std::forward<args_type>(args)...){}	\
													\
virtual ~name() = default;

namespace oosl{
	namespace assembler{
		namespace instruction{
			class base{
			public:
				typedef oosl::common::writer_base writer_type;

				typedef id id_type;
				typedef instruction_operand_base::ptr_type operand_type;

				virtual ~base() = default;

				virtual id_type id() const = 0;

				virtual void execute() const = 0;

				virtual void print(writer_type &writer) const = 0;

				static std::string id_to_string(id_type id){
					switch (id){
					case id_type::nop:
						return "nop";
					case id_type::push:
						return "push";
					case id_type::pop:
						return "pop";
					case id_type::mov:
						return "mov";
					case id_type::int_:
						return "int_";
					case id_type::call:
						return "call";
					case id_type::ret:
						return "ret";
					case id_type::jmp:
						return "jmp";
					case id_type::jz:
						return "jz";
					case id_type::jnz:
						return "jnz";
					case id_type::je:
						return "je";
					case id_type::jne:
						return "jne";
					case id_type::jl:
						return "jl";
					case id_type::jnl:
						return "jnl";
					case id_type::jle:
						return "jle";
					case id_type::jnle:
						return "jnle";
					case id_type::jg:
						return "jg";
					case id_type::jng:
						return "jng";
					case id_type::jge:
						return "jge";
					case id_type::jnge:
						return "jnge";
					case id_type::loop:
						return "loop";
					case id_type::inc:
						return "inc";
					case id_type::dec:
						return "dec";
					case id_type::add:
						return "add";
					case id_type::sub:
						return "sub";
					case id_type::mult:
						return "mult";
					case id_type::div:
						return "div";
					case id_type::mod:
						return "mod";
					case id_type::and_:
						return "and";
					case id_type::xor_:
						return "xor";
					case id_type::or_:
						return "or";
					case id_type::lshift:
						return "sll";
					case id_type::rshift:
						return "srl";
					case id_type::test:
						return "test";
					case id_type::not:
						return "not";
					case id_type::cmp:
						return "cmp";
					default:
						break;
					}

					return "";
				}
			};
		}
	}
}

#endif /* !OOSL_INSTRUCTION_BASE_H */
