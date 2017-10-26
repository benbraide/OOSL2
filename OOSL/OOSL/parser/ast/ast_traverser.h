#pragma once

#ifndef OOSL_AST_TRAVERSER_H
#define OOSL_AST_TRAVERSER_H

#include "assembler_ast.h"

#include "constant_value_ast.h"
#include "literal_ast.h"

OOSL_AST_BEGIN

struct ast_to_instruction_operand{
	static void get_string(const string_literal &ast, std::string &out){
		switch (ast.type){
		case common::quoted_string_type::escaped_narrow:
			utils::escape_string(ast.value.data(), ast.value.data() + ast.value.size(), out);
			break;
		default:
			out.assign(ast.value.data(), ast.value.size());
			break;
		}
	}

	static void get_string(const string_literal &ast, std::wstring &out){
		switch (ast.type){
		case common::quoted_string_type::escaped_wide:
			utils::escape_string(ast.value.data(), ast.value.data() + ast.value.size(), out);
			break;
		default:
			out.reserve(ast.value.size() + 1);
			for (auto &c : ast.value)
				out.append(1u, static_cast<wchar_t>(c));
			break;
		}
	}
	
	static operand_type get(const constant_value &ast){
		auto address = std::make_shared<oosl::assembler::absolute_identifier_instruction_operand>("@c." + std::to_string(static_cast<int>(ast.value)));
		return std::make_shared<oosl::assembler::memory_instruction_operand>(oosl::memory::register_value_type::unknown, address);
	}

	static operand_type get(const int8_literal &ast){
		if (ast.suffix.value_or(oosl::common::numeric_literal_suffix::int8) == oosl::common::numeric_literal_suffix::uint8)
			return std::make_shared<oosl::assembler::constant_value_instruction_operand<unsigned __int8>>(static_cast<unsigned __int8>(ast.value));
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<__int8>>(ast.value);//Signed value
	}

	static operand_type get(const int16_literal &ast){
		if (ast.suffix.value_or(oosl::common::numeric_literal_suffix::int16) == oosl::common::numeric_literal_suffix::uint16)
			return std::make_shared<oosl::assembler::constant_value_instruction_operand<unsigned __int16>>(static_cast<unsigned __int16>(ast.value));
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<__int16>>(ast.value);//Signed value
	}

	static operand_type get(const int32_literal &ast){
		if (ast.suffix.value_or(oosl::common::numeric_literal_suffix::int32) == oosl::common::numeric_literal_suffix::uint32)
			return std::make_shared<oosl::assembler::constant_value_instruction_operand<unsigned __int32>>(static_cast<unsigned __int32>(ast.value));
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<__int32>>(ast.value);//Signed value
	}

	static operand_type get(const int64_literal &ast){
		if (ast.suffix.value_or(oosl::common::numeric_literal_suffix::int64) == oosl::common::numeric_literal_suffix::uint64)
			return std::make_shared<oosl::assembler::constant_value_instruction_operand<unsigned __int64>>(static_cast<unsigned __int64>(ast.value));
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<__int64>>(ast.value);//Signed value
	}

	static operand_type get(const float_literal &ast){
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<float>>(ast.value);
	}

	static operand_type get(const double_literal &ast){
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<double>>(ast.value);
	}

	static operand_type get(const long_double_literal &ast){
		return std::make_shared<oosl::assembler::constant_value_instruction_operand<long double>>(ast.value);
	}

	static operand_type get(const integral_literal &ast){
		return boost::apply_visitor(ast_to_instruction_operand(), ast.value);
	}

	static operand_type get(const real_literal &ast){
		return boost::apply_visitor(ast_to_instruction_operand(), ast.value);
	}

	static operand_type get(const numeric_literal &ast){
		return boost::apply_visitor(ast_to_instruction_operand(), ast.value);
	}

	static operand_type get(const string_literal &ast){
		if (ast.type == common::quoted_string_type::narrow || ast.type == common::quoted_string_type::escaped_narrow){
			std::string buffer;
			get_string(ast, buffer);

			auto decl_op = std::make_shared<oosl::assembler::instruction::string_decl_operand>(buffer);
			return std::make_shared<oosl::assembler::absolute_identifier_instruction_operand>("@c." + std::to_string(0));
		}

		return nullptr;
	}

	template <typename ast_type>
	operand_type operator()(const ast_type &ast) const{
		return get(ast);
	}
};

struct ast_traverser{
	instruction_type operator()(const constant_value &ast) const{
		return nullptr;
	}
};

OOSL_AST_END

#endif /* !OOSL_AST_TRAVERSER_H */
