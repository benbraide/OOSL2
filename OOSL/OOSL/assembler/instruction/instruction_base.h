#pragma once

#ifndef OOSL_INSTRUCTION_BASE_H
#define OOSL_INSTRUCTION_BASE_H

#include "../vm.h"
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
			class base : public std::enable_shared_from_this<base>{
			public:
				typedef std::size_t size_type;
				typedef oosl::common::writer_base writer_type;

				typedef id id_type;
				typedef instruction_operand_base::ptr_type operand_type;

				typedef std::shared_ptr<base> ptr_type;

				virtual ~base() = default;

				virtual id_type id() const = 0;

				virtual size_type instruction_bytes() const = 0;

				virtual const std::string &label_value() const{
					throw instruction_error::bad_operation;
				}

				virtual const std::string &absolute_label_value() const{
					throw instruction_error::bad_operation;
				}

				virtual void create_or_add_to_section(){
					assembler::vm::add_instruction(shared_from_this());
				}

				virtual void resolve_constant(){}

				virtual void execute_and_update_instruction_pointer() const{
					execute();
					assembler::vm::rip->write_qword(assembler::vm::rip->read_qword() + instruction_bytes());//Advance Instruction Pointer
				}

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
					case id_type::times:
						return "times";
					case id_type::not:
						return "not";
					case id_type::cmp:
						return "cmp";
					case id_type::db:
						return "db";
					case id_type::dw:
						return "dw";
					case id_type::dd:
						return "dd";
					case id_type::dq:
						return "dq";
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
