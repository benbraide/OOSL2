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

#include "ast.h"

OOSL_AST_BEGIN

OOSL_AST_DECLARE_SINGLE_WPOS(asm_integral_value, __int64)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_float_value, double)

OOSL_AST_DECLARE_SINGLE_WPOS(asm_decl_integral_value, __int64)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_decl_float_value, double)

OOSL_AST_DECLARE_SINGLE_WPOS(asm_string, std::string)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_identifier, std::string)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_register, std::string)

OOSL_AST_DECLARE_SINGLE_WPOS(asm_mnemonic, oosl::assembler::instruction::id)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_section, oosl::assembler::section_id)
OOSL_AST_DECLARE_SINGLE(asm_label, asm_identifier)

OOSL_AST_DECLARE_SINGLE_WPOS(asm_type, oosl::memory::register_value_type)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_expr, oosl::assembler::instruction_operand_base::ptr_type)
OOSL_AST_DECLARE_SINGLE_WPOS(asm_grouped_expr, asm_expr)

OOSL_AST_DECLARE_SINGLE_WPOS(asm_memory, asm_expr)

struct asm_typed_memory{
	oosl::memory::register_value_type type;
	asm_memory memory;
};

OOSL_AST_DECLARE_SINGLE_VARIANT(asm_operand, asm_integral_value, asm_float_value, asm_identifier, asm_register, asm_memory, asm_typed_memory)
OOSL_AST_DECLARE_SINGLE_VARIANT(asm_non_memory_operand, asm_integral_value, asm_float_value, asm_identifier, asm_register)

struct asm_no_operand{
	asm_mnemonic mnemonic;
};

struct asm_unary{
	asm_mnemonic mnemonic;
	asm_operand operand;
};

struct asm_binary{
	asm_mnemonic mnemonic;
	asm_operand left;
	asm_operand right;
};

struct asm_ternary{
	asm_mnemonic mnemonic;
	asm_operand left;
	asm_operand right;
	asm_operand last;
};

struct asm_variadic{
	asm_mnemonic mnemonic;
	std::vector<asm_operand> operands;
};

struct asm_traverser{
	typedef oosl::assembler::instruction_operand_base::ptr_type operand_type;
	typedef oosl::assembler::instruction::decl_operand::ptr_type decl_operand_type;

	operand_type operator()(const asm_integral_value &ast) const{
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<long long>>(ast.value);
	}

	operand_type operator()(const asm_float_value &ast) const{
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<double>>(ast.value);
	}

	operand_type operator()(const asm_identifier &ast) const{
		return std::make_shared<oosl::assembler::identifier_instruction_operand>(ast.value);
	}

	operand_type operator()(const asm_register &ast) const{
		return std::make_shared<oosl::assembler::register_value_instruction_operand>(*oosl::assembler::vm::register_.find(ast.value));
	}

	operand_type operator()(const asm_memory &ast) const{
		return std::make_shared<oosl::assembler::memory_instruction_operand>(oosl::memory::register_value_type::unknown, ast.value.value);
	}

	operand_type operator()(const asm_typed_memory &ast) const{
		return std::make_shared<oosl::assembler::memory_instruction_operand>(ast.type, ast.memory.value.value);
	}

	decl_operand_type operator()(const asm_string &ast) const{
		return std::make_shared<oosl::assembler::instruction::string_decl_operand>(ast.value);
	}

	decl_operand_type operator()(const asm_decl_integral_value &ast) const{
		return std::make_shared<oosl::assembler::instruction::integral_decl_operand<long long>>(ast.value);
	}

	decl_operand_type operator()(const asm_decl_float_value &ast) const{
		return std::make_shared<oosl::assembler::instruction::float_decl_operand<double>>(ast.value);
	}
};

OOSL_AST_END

OOSL_AST_ADAPT_SINGLE(asm_integral_value)
OOSL_AST_ADAPT_SINGLE(asm_float_value)

OOSL_AST_ADAPT_SINGLE(asm_decl_integral_value)
OOSL_AST_ADAPT_SINGLE(asm_decl_float_value)

OOSL_AST_ADAPT_SINGLE(asm_string)
OOSL_AST_ADAPT_SINGLE(asm_identifier)
OOSL_AST_ADAPT_SINGLE(asm_register)

OOSL_AST_ADAPT_SINGLE(asm_mnemonic)
OOSL_AST_ADAPT_SINGLE(asm_section)
OOSL_AST_ADAPT_SINGLE(asm_label)

OOSL_AST_ADAPT_SINGLE(asm_type)
OOSL_AST_ADAPT_SINGLE(asm_expr)
OOSL_AST_ADAPT_SINGLE(asm_grouped_expr)

OOSL_AST_ADAPT_SINGLE(asm_memory)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_typed_memory,
	(oosl::memory::register_value_type, type)
	(oosl::parser::ast::asm_memory, memory)
)

OOSL_AST_ADAPT_SINGLE(asm_operand)
OOSL_AST_ADAPT_SINGLE(asm_non_memory_operand)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_no_operand,
	(oosl::parser::ast::asm_mnemonic, mnemonic)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_unary,
	(oosl::parser::ast::asm_mnemonic, mnemonic)
	(oosl::parser::ast::asm_operand, operand)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_binary,
	(oosl::parser::ast::asm_mnemonic, mnemonic)
	(oosl::parser::ast::asm_operand, left)
	(oosl::parser::ast::asm_operand, right)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_ternary,
	(oosl::parser::ast::asm_mnemonic, mnemonic)
	(oosl::parser::ast::asm_operand, left)
	(oosl::parser::ast::asm_operand, right)
	(oosl::parser::ast::asm_operand, last)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::asm_variadic,
	(oosl::parser::ast::asm_mnemonic, mnemonic)
	(std::vector<oosl::parser::ast::asm_operand>, operands)
)

#endif /* !OOSL_ASSEMBLER_AST_H */
