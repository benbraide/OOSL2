#pragma once

#ifndef OOSL_ASSEMBLER_PARSER_H
#define OOSL_ASSEMBLER_PARSER_H

#include "ast/assembler_ast.h"

namespace oosl{
	namespace parser{
		namespace assembler{
			namespace ast = parser::ast;
			namespace x3 = boost::spirit::x3;

			using operand_type = oosl::assembler::instruction_operand_base::ptr_type;
			using decl_operand_type = oosl::assembler::instruction::decl_operand::ptr_type;
			using instruction_type = oosl::assembler::instruction::base::ptr_type;

			struct asm_escaped_symbols : x3::symbols<char>{
				asm_escaped_symbols(){
					add
						("\\0", '\0')
						("\\a", '\a')
						("\\b", '\b')
						("\\f", '\f')
						("\\n", '\n')
						("\\r", '\r')
						("\\t", '\t')
						("\\v", '\v')
						("\\?", '\?')
						("\\\"", '\"')
						("\\\'", '\'')
						("\\\\", '\\')
						;
				}
			} asm_escaped_symbols_;

			struct asm_register_symbols : x3::symbols<std::string>{
				asm_register_symbols(){
					add
						("rax", "rax")
						("r0", "r0")
						("eax", "eax")
						("ax", "ax")
						("al", "al")
						("ah", "ah")
						("rbx", "rbx")
						("r1", "r1")
						("ebx", "ebx")
						("bx", "bx")
						("bl", "bl")
						("bh", "bh")
						("rcx", "rcx")
						("r2", "r2")
						("ecx", "ecx")
						("cx", "cx")
						("cl", "cl")
						("ch", "ch")
						("rdx", "rdx")
						("r3", "r3")
						("edx", "edx")
						("dx", "dx")
						("dl", "dl")
						("dh", "dh")
						("rsp", "rsp")
						("r4", "r4")
						("esp", "esp")
						("sp", "sp")
						("rbp", "rbp")
						("r5", "r5")
						("ebp", "ebp")
						("bp", "bp")
						("rsi", "rsi")
						("r6", "r6")
						("esi", "esi")
						("si", "si")
						("rdi", "rdi")
						("r7", "r7")
						("edi", "edi")
						("di", "di")
						("rip", "rip")
						("r8", "r8")
						("eip", "eip")
						("ip", "ip")
						("r15", "r15")
						("r14", "r14")
						("r13", "r13")
						("r12", "r12")
						("r11", "r11")
						("r10", "r10")
						("r9", "r9")
						("f0", "f0")
						("f1", "f1")
						("f2", "f2")
						("f3", "f3")
						("fd0", "fd0")
						("fd1", "fd1")
						("fd2", "fd2")
						("fd3", "fd3")
						("fld0", "fld0")
						("fld1", "fld1")
						("fld2", "fld2")
						("fld3", "fld3")
						;
				}
			} asm_register_symbols_;

			struct asm_section_symbols : x3::symbols<oosl::assembler::section_id>{
				asm_section_symbols(){
					add
						(".rodata", oosl::assembler::section_id::rodata)
						(".data", oosl::assembler::section_id::data)
						(".text", oosl::assembler::section_id::text)
						;
				}
			} asm_section_symbols_;

			struct asm_type_symbols : x3::symbols<oosl::memory::register_value_type>{
				asm_type_symbols(){
					add
						("byte", oosl::memory::register_value_type::byte)
						("dword", oosl::memory::register_value_type::dword)
						("qword", oosl::memory::register_value_type::qword)
						("word", oosl::memory::register_value_type::word)
						("float", oosl::memory::register_value_type::float_)
						("double", oosl::memory::register_value_type::double_)
						;
				}
			} asm_type_symbols_;

			struct asm_no_operand_mnemonic_symbols : x3::symbols<oosl::assembler::instruction::id>{
				asm_no_operand_mnemonic_symbols(){
					add
						("nop", oosl::assembler::instruction::id::nop)
						("ret", oosl::assembler::instruction::id::ret)
						;
				}
			} asm_no_operand_mnemonic_symbols_;

			struct asm_unary_mnemonic_symbols : x3::symbols<oosl::assembler::instruction::id>{
				asm_unary_mnemonic_symbols(){
					add
						("push", oosl::assembler::instruction::id::push)
						("pop", oosl::assembler::instruction::id::pop)
						("int", oosl::assembler::instruction::id::int_)
						("call", oosl::assembler::instruction::id::call)
						("jmp", oosl::assembler::instruction::id::jmp)
						("jz", oosl::assembler::instruction::id::jz)
						("jnz", oosl::assembler::instruction::id::jnz)
						("je", oosl::assembler::instruction::id::je)
						("jne", oosl::assembler::instruction::id::jne)
						("jle", oosl::assembler::instruction::id::jle)
						("jl", oosl::assembler::instruction::id::jl)
						("jnle", oosl::assembler::instruction::id::jnle)
						("jnl", oosl::assembler::instruction::id::jnl)
						("jge", oosl::assembler::instruction::id::jge)
						("jg", oosl::assembler::instruction::id::jg)
						("jnge", oosl::assembler::instruction::id::jnge)
						("jng", oosl::assembler::instruction::id::jng)
						("loop", oosl::assembler::instruction::id::loop)
						("inc", oosl::assembler::instruction::id::inc)
						("dec", oosl::assembler::instruction::id::dec)
						("not", oosl::assembler::instruction::id::not)
						;
				}
			} asm_unary_mnemonic_symbols_;

			struct asm_binary_mnemonic_symbols : x3::symbols<oosl::assembler::instruction::id>{
				asm_binary_mnemonic_symbols(){
					add
						("mov", oosl::assembler::instruction::id::mov)
						("add", oosl::assembler::instruction::id::add)
						("sub", oosl::assembler::instruction::id::sub)
						("mult", oosl::assembler::instruction::id::mult)
						("div", oosl::assembler::instruction::id::div)
						("mod", oosl::assembler::instruction::id::mod)
						("and", oosl::assembler::instruction::id::and_)
						("xor", oosl::assembler::instruction::id::xor_)
						("or", oosl::assembler::instruction::id::or_)
						("sll", oosl::assembler::instruction::id::lshift)
						("srl", oosl::assembler::instruction::id::rshift)
						("test", oosl::assembler::instruction::id::test)
						("cmp", oosl::assembler::instruction::id::cmp)
						;
				}
			} asm_binary_mnemonic_symbols_;

			struct asm_variadic_mnemonic_symbols : x3::symbols<oosl::assembler::instruction::id>{
				asm_variadic_mnemonic_symbols(){
					add
						("db", oosl::assembler::instruction::id::db)
						("dw", oosl::assembler::instruction::id::dw)
						("dd", oosl::assembler::instruction::id::dd)
						("dq", oosl::assembler::instruction::id::dq)
						;
				}
			} asm_variadic_mnemonic_symbols_;

			struct asm_operator_symbols : x3::symbols<oosl::assembler::expression_instruction_operand::operator_type>{
				asm_operator_symbols(){
					add
						("+", oosl::assembler::expression_instruction_operand::operator_type::add)
						("-", oosl::assembler::expression_instruction_operand::operator_type::sub)
						("*", oosl::assembler::expression_instruction_operand::operator_type::mult)
						("/", oosl::assembler::expression_instruction_operand::operator_type::div)
						("%", oosl::assembler::expression_instruction_operand::operator_type::mod)
						("&", oosl::assembler::expression_instruction_operand::operator_type::bit_and)
						("|", oosl::assembler::expression_instruction_operand::operator_type::bit_xor)
						("^", oosl::assembler::expression_instruction_operand::operator_type::bit_or)
						("<<", oosl::assembler::expression_instruction_operand::operator_type::lshift)
						(">>", oosl::assembler::expression_instruction_operand::operator_type::rshift)
						;
				}
			} asm_operator_symbols_;

			x3::rule<class asm_integral_value, ast::asm_integral_value> const asm_integral_value = "asm_integral_value";
			x3::rule<class asm_float_value, ast::asm_float_value> const asm_float_value = "asm_float_value";

			x3::rule<class asm_integral_decl_value, ast::asm_integral_decl_value> const asm_integral_decl_value = "asm_integral_decl_value";
			x3::rule<class asm_float_decl_value, ast::asm_float_decl_value> const asm_float_decl_value = "asm_float_decl_value";

			x3::rule<class asm_string, ast::asm_string> const asm_string = "asm_string";
			x3::rule<class asm_identifier, ast::asm_identifier> const asm_identifier = "asm_identifier";
			x3::rule<class asm_register, ast::asm_register> const asm_register = "asm_register";

			x3::rule<class asm_section, ast::asm_section> const asm_section = "asm_section";
			x3::rule<class asm_label, ast::asm_label> const asm_label = "asm_label";

			x3::rule<class asm_expr, operand_type> const asm_expr = "asm_expr";
			x3::rule<class asm_grouped_expr, operand_type> const asm_grouped_expr = "asm_grouped_expr";

			x3::rule<class asm_expr_decl, decl_operand_type> const asm_expr_decl = "asm_expr_decl";
			x3::rule<class asm_grouped_expr_decl, decl_operand_type> const asm_grouped_expr_decl = "asm_grouped_expr_decl";

			x3::rule<class asm_memory, ast::asm_memory> const asm_memory = "asm_memory";
			x3::rule<class asm_typed_memory, ast::asm_typed_memory> const asm_typed_memory = "asm_typed_memory";

			x3::rule<class asm_operand, ast::asm_operand> const asm_operand = "asm_operand";
			x3::rule<class asm_non_memory_operand, ast::asm_non_memory_operand> const asm_non_memory_operand = "asm_non_memory_operand";

			x3::rule<class asm_no_operand, ast::asm_no_operand> const asm_no_operand = "asm_no_operand";
			x3::rule<class asm_unary, ast::asm_unary> const asm_unary = "asm_unary";
			x3::rule<class asm_binary, ast::asm_binary> const asm_binary = "asm_binary";
			x3::rule<class asm_ternary, ast::asm_ternary> const asm_ternary = "asm_ternary";
			x3::rule<class asm_variadic, ast::asm_variadic> const asm_variadic = "asm_variadic";

			x3::rule<class asm_numeric_operand_decl, ast::asm_numeric_operand_decl> const asm_numeric_operand_decl = "asm_numeric_operand_decl";
			x3::rule<class asm_variadic_decl, ast::asm_variadic_decl> const asm_variadic_decl = "asm_variadic_decl";

			x3::rule<class asm_instruction, ast::asm_instruction> const asm_instruction = "asm_instruction";
			x3::rule<class asm_instruction_set, ast::asm_instruction_set> const asm_instruction_set = "asm_instruction_set";

			x3::rule<class asm_skip> const asm_skip = "asm_skip";

			auto asm_parsed_string = [](auto &ctx){
				x3::_val(ctx) = std::make_shared<oosl::assembler::instruction::string_decl_operand>(std::string(boost::begin(x3::_attr(ctx)), boost::end(x3::_attr(ctx))));
			};

			auto asm_parsed_identifier = [](auto &ctx){
				x3::_val(ctx) = std::make_shared<oosl::assembler::identifier_instruction_operand>(std::string(boost::begin(x3::_attr(ctx)), boost::end(x3::_attr(ctx))));
			};

			auto asm_parsed_register = [](auto &ctx){
				auto register_ = oosl::assembler::vm::register_.find(std::string(boost::begin(x3::_attr(ctx)), boost::end(x3::_attr(ctx))));
				x3::_val(ctx) = std::make_shared<oosl::assembler::register_value_instruction_operand>(*register_);
			};

			auto asm_parsed_single = [](auto &ctx){
				x3::_val(ctx) = ast::asm_traverser::get(x3::_attr(ctx));
			};

			auto asm_parsed_expr = [](auto &ctx){
				x3::_val(ctx) = std::make_shared<oosl::assembler::expression_instruction_operand>(
					boost::fusion::at<boost::mpl::int_<0>>(x3::_attr(ctx)),
					x3::_val(ctx),
					ast::asm_traverser::get(boost::fusion::at<boost::mpl::int_<1>>(x3::_attr(ctx)))
					);
			};

			auto asm_parsed_grouped_expr = [](auto &ctx){
				x3::_val(ctx) = std::make_shared<oosl::assembler::grouped_expression_instruction_operand>(x3::_attr(ctx));
			};

			auto asm_parsed_expr_decl = [](auto &ctx){
				x3::_val(ctx) = std::make_shared<oosl::assembler::instruction::expr_decl_operand>(
					boost::fusion::at<boost::mpl::int_<0>>(x3::_attr(ctx)),
					x3::_val(ctx),
					ast::asm_traverser::get(boost::fusion::at<boost::mpl::int_<1>>(x3::_attr(ctx)))
					);
			};

			auto asm_parsed_grouped_decl_expr = [](auto &ctx){
				x3::_val(ctx) = std::make_shared<oosl::assembler::instruction::grouped_expr_decl_operand>(x3::_attr(ctx));
			};

			auto const asm_integral_value_def = x3::long_long;
			auto const asm_float_value_def = double_;

			auto const asm_integral_decl_value_def = x3::long_long;
			auto const asm_float_decl_value_def = double_;

			auto const asm_string_def = ("'" >> x3::lexeme[*(asm_escaped_symbols_ | ~x3::char_("'"))] >> "'");
			auto const asm_identifier_def = (!utils::keyword("section") >> !asm_register >> utils_identifier);
			auto const asm_register_def = utils::keyword(asm_register_symbols_);

			auto const asm_section_def = (utils::keyword("section") > asm_section_symbols_);
			auto const asm_label_def = (asm_identifier >> utils::keyword(":"));

			auto const asm_expr_def = (asm_non_memory_operand)[asm_parsed_single] >> *(asm_operator_symbols_ >> asm_non_memory_operand)[asm_parsed_expr];
			auto const asm_grouped_expr_def = ('(' >> asm_expr >> ')')[asm_parsed_grouped_expr];

			auto const asm_expr_decl_def = (asm_numeric_operand_decl)[asm_parsed_single] >> *(asm_operator_symbols_ >> asm_numeric_operand_decl)[asm_parsed_expr_decl];
			auto const asm_grouped_expr_decl_def = ('(' >> asm_expr_decl >> ')')[asm_parsed_grouped_decl_expr];
			auto const asm_numeric_operand_decl_def = (asm_float_decl_value | asm_integral_decl_value);

			auto const asm_memory_def = ('[' >> asm_expr >> ']');
			auto const asm_typed_memory_def = (asm_type_symbols_ >> asm_memory);

			auto const asm_operand_def = (asm_float_value | asm_integral_value | asm_register | asm_identifier | asm_memory | asm_typed_memory);
			auto const asm_non_memory_operand_def = (asm_integral_value | asm_float_value | asm_register | asm_identifier);

			auto const asm_no_operand_def = utils::keyword(asm_no_operand_mnemonic_symbols_);
			auto const asm_unary_def = (utils::keyword(asm_unary_mnemonic_symbols_) >> asm_operand);
			auto const asm_binary_def = (utils::keyword(asm_binary_mnemonic_symbols_) >> asm_operand >> ',' >> asm_operand);
			auto const asm_ternary_def = (utils::keyword(asm_binary_mnemonic_symbols_) >> asm_operand >> ',' >> asm_operand >> ',' >> asm_operand);

			auto const asm_variadic_decl_def = (utils::keyword(asm_variadic_mnemonic_symbols_) >> (asm_string | asm_grouped_expr_decl | asm_expr_decl) % ",");

			auto const asm_instruction_def = (asm_section | asm_no_operand | asm_unary | asm_binary | asm_ternary | asm_variadic_decl | asm_label);
			auto const asm_instruction_set_def = (*asm_instruction);

			auto const asm_skip_def = (x3::space | (';' >> *x3::omit[(x3::char_ - x3::eol)] >> x3::eol));

			BOOST_SPIRIT_DEFINE(
				asm_integral_value,
				asm_float_value,
				asm_integral_decl_value,
				asm_float_decl_value,
				asm_string,
				asm_identifier,
				asm_register,
				asm_section,
				asm_label,
				asm_expr,
				asm_grouped_expr,
				asm_numeric_operand_decl,
				asm_expr_decl,
				asm_grouped_expr_decl,
				asm_memory,
				asm_typed_memory,
				asm_operand,
				asm_non_memory_operand,
				asm_no_operand,
				asm_unary,
				asm_binary,
				asm_ternary,
				asm_variadic_decl,
				asm_instruction,
				asm_instruction_set,
				asm_skip
			)
		}
	}
}

#endif /* !OOSL_ASSEMBLER_PARSER_H */
