#pragma once

#ifndef OOSL_ASSEMBLER_AST_H
#define OOSL_ASSEMBLER_AST_H

#include "../../memory/memory_register.h"
#include "../../assembler/instruction/instruction_id.h"
#include "../../assembler/instructions_section.h"

#include "../../assembler/vm.h"
#include "../../assembler/constant_value_instruction_operand.h"
#include "../../assembler/instruction_operand_base.h"
#include "../../assembler/register_value_instruction_operand.h"
#include "../../assembler/identifier_instruction_operand.h"
#include "../../assembler/expression_instruction_operand.h"
#include "../../assembler/memory_instruction_operand.h"
#include "../../assembler/instruction/decl_instruction.h"

#include "../../assembler/instruction/nop_instruction.h"
#include "../../assembler/instruction/arithmetic_instruction.h"
#include "../../assembler/instruction/cmp_instruction.h"
#include "../../assembler/instruction/call_instruction.h"
#include "../../assembler/instruction/ret_instruction.h"
#include "../../assembler/instruction/jmp_instruction.h"
#include "../../assembler/instruction/int_instruction.h"
#include "../../assembler/instruction/label_instruction.h"
#include "../../assembler/instruction/loop_instruction.h"
#include "../../assembler/instruction/mov_instruction.h"
#include "../../assembler/instruction/stack_instruction.h"
#include "../../assembler/instruction/test_instruction.h"
#include "../../assembler/instruction/times_instruction.h"
#include "../../assembler/instruction/decl_instruction.h"
#include "../../assembler/instruction/section_instruction.h"

#include "../parser_utils.h"

#include "ast.h"

#define OOSL_AST_CREATE_UNARY(name)\
return std::make_shared<oosl::assembler::instruction::name>(asm_traverser::get(ast.operand));

#define OOSL_AST_CREATE_BINARY(name)\
return std::make_shared<oosl::assembler::instruction::name>(asm_traverser::get(ast.left), asm_traverser::get(ast.right));

#define OOSL_AST_CREATE_TERNARY(name)\
return std::make_shared<oosl::assembler::instruction::name>(asm_traverser::get(ast.left), asm_traverser::get(ast.right), asm_traverser::get(ast.last));

#define OOSL_AST_CREATE_VARIADIC(name)\
return std::make_shared<oosl::assembler::instruction::name>(std::move(operands));

OOSL_AST_BEGIN

using operand_type = oosl::assembler::instruction_operand_base::ptr_type;
using decl_operand_type = oosl::assembler::instruction::decl_operand::ptr_type;
using instruction_type = oosl::assembler::instruction::base::ptr_type;

OOSL_AST_DECLARE_SINGLE_WPOS(asm_integral_value, __int64)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_float_value, double)

OOSL_AST_DECLARE_SINGLE_WPOS(asm_integral_decl_value, __int64)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_float_decl_value, double)

OOSL_AST_DECLARE_SINGLE_WPOS(asm_string, std::vector<char>)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_register, std::string)

using asm_identifier = identifier_ast;

OOSL_AST_DECLARE_SINGLE_WPOS(asm_mnemonic, oosl::assembler::instruction::id)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_section, oosl::assembler::section_id)
OOSL_AST_DECLARE_SINGLE(asm_label, asm_identifier)

OOSL_AST_DECLARE_SINGLE_VARIANT(asm_non_memory_operand, asm_integral_value, asm_float_value, asm_identifier, asm_register)

OOSL_AST_DECLARE_SINGLE_WPOS(asm_memory, operand_type)

struct asm_typed_memory{
	oosl::memory::register_value_type type;
	asm_memory memory;
};

OOSL_AST_DECLARE_SINGLE_VARIANT(asm_operand, asm_integral_value, asm_float_value, asm_identifier, asm_register, asm_memory, asm_typed_memory)
OOSL_AST_DECLARE_SINGLE_VARIANT(asm_numeric_operand_decl, asm_integral_decl_value, asm_float_decl_value)

struct asm_no_operand{
	oosl::assembler::instruction::id mnemonic;
};

struct asm_unary{
	oosl::assembler::instruction::id mnemonic;
	asm_operand operand;
};

struct asm_binary{
	oosl::assembler::instruction::id mnemonic;
	asm_operand left;
	asm_operand right;
};

struct asm_ternary{
	oosl::assembler::instruction::id mnemonic;
	asm_operand left;
	asm_operand right;
	asm_operand last;
};

struct asm_variadic{
	oosl::assembler::instruction::id mnemonic;
	std::vector<asm_operand> operands;
};

struct asm_variadic_decl{
	typedef boost::variant<asm_string, decl_operand_type> operands_type;
	oosl::assembler::instruction::id mnemonic;
	std::vector<operands_type> operands;
};

OOSL_AST_DECLARE_SINGLE_VARIANT(asm_instruction, asm_section, asm_label, asm_no_operand, asm_unary, asm_binary, asm_ternary, asm_variadic_decl)
OOSL_AST_DECLARE_SINGLE(asm_instruction_set, std::vector<asm_instruction>)

struct asm_traverser{
	static void identifier_to_string(const asm_identifier &ast, std::string &value){
		value.reserve(ast.rest.size() + 2);

		value.append(1, ast.first);
		value.append(ast.rest.data(), ast.rest.size());
	}

	template <typename value_type>
	static value_type get(const value_type &ast){
		return ast;
	}

	static decl_operand_type get(const asm_numeric_operand_decl &ast){
		return boost::apply_visitor(asm_traverser(), ast.value);
	}

	static operand_type get(const asm_operand &ast){
		return boost::apply_visitor(asm_traverser(), ast.value);
	}

	static operand_type get(const asm_non_memory_operand &ast){
		return boost::apply_visitor(asm_traverser(), ast.value);
	}

	static instruction_type get(const asm_instruction &ast){
		return boost::apply_visitor(asm_traverser(), ast.value);
	}

	template <typename value_type>
	value_type operator()(const value_type &ast) const{
		return ast;
	}

	operand_type operator()(const asm_integral_value &ast) const{
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<long long>>(ast.value);
	}

	operand_type operator()(const asm_float_value &ast) const{
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<double>>(ast.value);
	}

	decl_operand_type operator()(const asm_integral_decl_value &ast) const{
		return std::make_shared<oosl::assembler::instruction::integral_decl_operand<long long>>(ast.value);
	}

	decl_operand_type operator()(const asm_float_decl_value &ast) const{
		return std::make_shared<oosl::assembler::instruction::float_decl_operand<double>>(ast.value);
	}

	decl_operand_type operator()(const asm_string &ast) const{
		return std::make_shared<oosl::assembler::instruction::string_decl_operand>(std::string(ast.value.data(), ast.value.size()));
	}

	operand_type operator()(const asm_identifier &ast) const{
		std::string value;
		identifier_to_string(ast, value);
		return std::make_shared<oosl::assembler::identifier_instruction_operand>(value);
	}

	operand_type operator()(const std::string &ast) const{
		return std::make_shared<oosl::assembler::identifier_instruction_operand>(ast);
	}

	operand_type operator()(const asm_register &ast) const{
		return std::make_shared<oosl::assembler::register_value_instruction_operand>(*oosl::assembler::vm::register_.find(ast.value));
	}

	operand_type operator()(const asm_memory &ast) const{
		return std::make_shared<oosl::assembler::memory_instruction_operand>(oosl::memory::register_value_type::unknown, ast.value);
	}

	operand_type operator()(const asm_typed_memory &ast) const{
		return std::make_shared<oosl::assembler::memory_instruction_operand>(ast.type, ast.memory.value);
	}

	operand_type operator()(const asm_operand &ast) const{
		return boost::apply_visitor(asm_traverser(), ast.value);
	}

	operand_type operator()(const asm_non_memory_operand &ast) const{
		return boost::apply_visitor(asm_traverser(), ast.value);
	}

	instruction_type operator()(const asm_section &ast) const{
		return std::make_shared<oosl::assembler::instruction::section>(ast.value);
	}

	instruction_type operator()(const asm_label &ast) const{
		std::string value;
		identifier_to_string(ast.value, value);
		return std::make_shared<oosl::assembler::instruction::label>(value);
	}

	instruction_type operator()(const asm_no_operand &ast) const{
		switch (ast.mnemonic){
		case oosl::assembler::instruction::id::nop:
			return std::make_shared<oosl::assembler::instruction::nop>();
		case oosl::assembler::instruction::id::ret:
			return std::make_shared<oosl::assembler::instruction::ret>();
		default:
			break;
		}

		return nullptr;
	}

	instruction_type operator()(const asm_unary &ast) const{
		switch (ast.mnemonic){
		case oosl::assembler::instruction::id::push:
			OOSL_AST_CREATE_UNARY(push);
		case oosl::assembler::instruction::id::pop:
			OOSL_AST_CREATE_UNARY(pop);
		case oosl::assembler::instruction::id::int_:
			OOSL_AST_CREATE_UNARY(int_);
		case oosl::assembler::instruction::id::call:
			OOSL_AST_CREATE_UNARY(call);
		case oosl::assembler::instruction::id::jmp:
			OOSL_AST_CREATE_UNARY(jmp);
		case oosl::assembler::instruction::id::jz:
			OOSL_AST_CREATE_UNARY(jz);
		case oosl::assembler::instruction::id::jnz:
			OOSL_AST_CREATE_UNARY(jnz);
		case oosl::assembler::instruction::id::je:
			OOSL_AST_CREATE_UNARY(je);
		case oosl::assembler::instruction::id::jne:
			OOSL_AST_CREATE_UNARY(jne);
		case oosl::assembler::instruction::id::jl:
			OOSL_AST_CREATE_UNARY(jl);
		case oosl::assembler::instruction::id::jnl:
			OOSL_AST_CREATE_UNARY(jnl);
		case oosl::assembler::instruction::id::jle:
			OOSL_AST_CREATE_UNARY(jle);
		case oosl::assembler::instruction::id::jnle:
			OOSL_AST_CREATE_UNARY(jnle);
		case oosl::assembler::instruction::id::jg:
			OOSL_AST_CREATE_UNARY(jg);
		case oosl::assembler::instruction::id::jng:
			OOSL_AST_CREATE_UNARY(jng);
		case oosl::assembler::instruction::id::jge:
			OOSL_AST_CREATE_UNARY(jge);
		case oosl::assembler::instruction::id::jnge:
			OOSL_AST_CREATE_UNARY(jnge);
		case oosl::assembler::instruction::id::loop:
			OOSL_AST_CREATE_UNARY(loop);
		case oosl::assembler::instruction::id::inc:
			OOSL_AST_CREATE_UNARY(inc);
		case oosl::assembler::instruction::id::dec:
			OOSL_AST_CREATE_UNARY(dec);
		case oosl::assembler::instruction::id::not:
			OOSL_AST_CREATE_UNARY(not);
		default:
			break;
		}

		return nullptr;
	}

	instruction_type operator()(const asm_binary &ast) const{
		switch (ast.mnemonic){
		case oosl::assembler::instruction::id::mov:
			OOSL_AST_CREATE_BINARY(mov);
		case oosl::assembler::instruction::id::add:
			OOSL_AST_CREATE_BINARY(add);
		case oosl::assembler::instruction::id::sub:
			OOSL_AST_CREATE_BINARY(sub);
		case oosl::assembler::instruction::id::mult:
			OOSL_AST_CREATE_BINARY(mult);
		case oosl::assembler::instruction::id::div:
			OOSL_AST_CREATE_BINARY(div);
		case oosl::assembler::instruction::id::mod:
			OOSL_AST_CREATE_BINARY(mod);
		case oosl::assembler::instruction::id::and_:
			OOSL_AST_CREATE_BINARY(and_);
		case oosl::assembler::instruction::id::xor_:
			OOSL_AST_CREATE_BINARY(xor_);
		case oosl::assembler::instruction::id::or_:
			OOSL_AST_CREATE_BINARY(or_);
		case oosl::assembler::instruction::id::lshift:
			OOSL_AST_CREATE_BINARY(lshift);
		case oosl::assembler::instruction::id::rshift:
			OOSL_AST_CREATE_BINARY(rshift);
		case oosl::assembler::instruction::id::test:
			OOSL_AST_CREATE_BINARY(test);
		case oosl::assembler::instruction::id::cmp:
			OOSL_AST_CREATE_BINARY(cmp);
		default:
			break;
		}

		return nullptr;
	}

	instruction_type operator()(const asm_ternary &ast) const{
		return nullptr;
	}

	instruction_type operator()(const asm_variadic &ast) const{
		return nullptr;
	}

	instruction_type operator()(const asm_variadic_decl &ast) const{
		std::vector<decl_operand_type> operands;

		operands.reserve(ast.operands.size());
		for (auto &item : ast.operands)
			operands.push_back(boost::apply_visitor(asm_traverser(), item));

		switch (ast.mnemonic){
		case oosl::assembler::instruction::id::db:
			OOSL_AST_CREATE_VARIADIC(byte_decl);
		case oosl::assembler::instruction::id::dw:
			OOSL_AST_CREATE_VARIADIC(word_decl);
		case oosl::assembler::instruction::id::dd:
			OOSL_AST_CREATE_VARIADIC(dword_decl);
		case oosl::assembler::instruction::id::dq:
			OOSL_AST_CREATE_VARIADIC(qword_decl);
		default:
			break;
		}

		return nullptr;
	}
};

OOSL_AST_END

OOSL_AST_ADAPT_SINGLE(asm_integral_value)
OOSL_AST_ADAPT_SINGLE(asm_float_value)

OOSL_AST_ADAPT_SINGLE(asm_integral_decl_value)
OOSL_AST_ADAPT_SINGLE(asm_float_decl_value)

OOSL_AST_ADAPT_SINGLE(asm_string)
OOSL_AST_ADAPT_SINGLE(asm_register)

OOSL_AST_ADAPT_SINGLE(asm_mnemonic)
OOSL_AST_ADAPT_SINGLE(asm_section)
OOSL_AST_ADAPT_SINGLE(asm_label)

OOSL_AST_ADAPT_SINGLE(asm_memory)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_typed_memory,
	(oosl::memory::register_value_type, type)
	(oosl::parser::ast::asm_memory, memory)
)

OOSL_AST_ADAPT_SINGLE(asm_operand)
OOSL_AST_ADAPT_SINGLE(asm_non_memory_operand)
OOSL_AST_ADAPT_SINGLE(asm_numeric_operand_decl)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_no_operand,
	(oosl::assembler::instruction::id, mnemonic)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_unary,
	(oosl::assembler::instruction::id, mnemonic)
	(oosl::parser::ast::asm_operand, operand)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_binary,
	(oosl::assembler::instruction::id, mnemonic)
	(oosl::parser::ast::asm_operand, left)
	(oosl::parser::ast::asm_operand, right)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_ternary,
	(oosl::assembler::instruction::id, mnemonic)
	(oosl::parser::ast::asm_operand, left)
	(oosl::parser::ast::asm_operand, right)
	(oosl::parser::ast::asm_operand, last)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_variadic,
	(oosl::assembler::instruction::id, mnemonic)
	(std::vector<oosl::parser::ast::asm_operand>, operands)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_variadic_decl,
	(oosl::assembler::instruction::id, mnemonic)
	(std::vector<oosl::parser::ast::asm_variadic_decl::operands_type>, operands)
)

OOSL_AST_ADAPT_SINGLE(asm_instruction)
OOSL_AST_ADAPT_SINGLE(asm_instruction_set)

#endif /* !OOSL_ASSEMBLER_AST_H */
