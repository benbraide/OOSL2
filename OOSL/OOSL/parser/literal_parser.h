#pragma once

#ifndef OOSL_LITERAL_PARSER_H
#define OOSL_LITERAL_PARSER_H

#include "ast/literal_ast.h"

#define OOSL_INT_LIT_PARSER_DEF(name, suf)										\
																				\
struct OOSL_AST_JOIN(name, _literal_symbols) : x3::symbols<oosl::common::numeric_literal_suffix>{\
	OOSL_AST_JOIN(name, _literal_symbols)(){									\
		add																		\
			(suf, oosl::common::numeric_literal_suffix::name)					\
			("u" suf, oosl::common::numeric_literal_suffix::OOSL_AST_JOIN(u, name))\
			;																	\
	}																			\
} OOSL_AST_JOIN(name, _literal_symbols_);										\
																				\
x3::rule<class OOSL_AST_JOIN(name, _literal), ast::OOSL_AST_JOIN(name, _literal)> const OOSL_AST_JOIN(name, _literal) = #name "_literal";\
																				\
signed_hex_parser<OOSL_AST_JOIN(__, name)> const OOSL_AST_JOIN(name, _hex)= {};	\
signed_oct_parser<OOSL_AST_JOIN(__, name)> const OOSL_AST_JOIN(name, _oct)= {};	\
signed_bin_parser<OOSL_AST_JOIN(__, name)> const OOSL_AST_JOIN(name, _bin)= {};	\
																				\
auto const OOSL_AST_JOIN(name, _literal_def) =									\
x3::lexeme[(("0x" >> OOSL_AST_JOIN(name, _hex)) | OOSL_AST_JOIN(name, _oct) | ("0b" >> OOSL_AST_JOIN(name, _bin)) | x3::name) >> utils::keyword(OOSL_AST_JOIN(name, _literal_symbols_))];\
																				\
BOOST_SPIRIT_DEFINE(OOSL_AST_JOIN(name, _literal));

#define OOSL_INT_LIT_0_PARSER_DEF(name)											\
																				\
x3::rule<class OOSL_AST_JOIN(name, _0_literal), ast::OOSL_AST_JOIN(name, _literal)> const OOSL_AST_JOIN(name, _0_literal) = #name "_0_literal";\
																				\
signed_hex_parser<OOSL_AST_JOIN(__, name)> const OOSL_AST_JOIN(name, _0_hex)= {};\
signed_oct_parser<OOSL_AST_JOIN(__, name)> const OOSL_AST_JOIN(name, _0_oct)= {};\
signed_bin_parser<OOSL_AST_JOIN(__, name)> const OOSL_AST_JOIN(name, _0_bin)= {};\
																				\
auto const OOSL_AST_JOIN(name, _0_literal_def) =								\
((x3::lexeme["0x" >> OOSL_AST_JOIN(name, _0_hex)] | OOSL_AST_JOIN(name, _0_oct) | x3::lexeme["0b" >> OOSL_AST_JOIN(name, _0_bin)] | x3::name));\
																				\
BOOST_SPIRIT_DEFINE(OOSL_AST_JOIN(name, _0_literal));

#define OOSL_REAL_LIT_PARSER_DEF(name, suf)										\
																				\
struct OOSL_AST_JOIN(name, literal_symbols) : x3::symbols<oosl::common::numeric_literal_suffix>{\
	OOSL_AST_JOIN(name, literal_symbols)(){										\
		add																		\
			(suf, oosl::common::numeric_literal_suffix::name)					\
			;																	\
	}																			\
} OOSL_AST_JOIN(name, literal_symbols_);										\
																				\
x3::rule<class OOSL_AST_JOIN(name, literal), ast::OOSL_AST_JOIN(name, literal)> const OOSL_AST_JOIN(name, literal) = #name "literal";\
																				\
auto const OOSL_AST_JOIN(name, literal_def) = x3::lexeme[name >> utils::keyword(OOSL_AST_JOIN(name, literal_symbols_))];\
																				\
BOOST_SPIRIT_DEFINE(OOSL_AST_JOIN(name, literal));

#define OOSL_REAL_LIT_0_PARSER_DEF(name)										\
																				\
x3::rule<class OOSL_AST_JOIN(name, _0_literal), ast::OOSL_AST_JOIN(name, literal)> const OOSL_AST_JOIN(name, _0_literal) = #name "_0_literal";\
																				\
auto const OOSL_AST_JOIN(name, _0_literal_def) = name;							\
																				\
BOOST_SPIRIT_DEFINE(OOSL_AST_JOIN(name, _0_literal));

namespace oosl{
	namespace parser{
		namespace x3 = boost::spirit::x3;

		OOSL_INT_LIT_PARSER_DEF(int8, "i8");
		OOSL_INT_LIT_PARSER_DEF(int16, "i16");
		OOSL_INT_LIT_PARSER_DEF(int32, "i32");
		OOSL_INT_LIT_PARSER_DEF(int64, "i64");
		
		OOSL_REAL_LIT_PARSER_DEF(float_, "f32");
		OOSL_REAL_LIT_PARSER_DEF(double_, "f64");
		OOSL_REAL_LIT_PARSER_DEF(long_double_, "f128");

		OOSL_INT_LIT_0_PARSER_DEF(int32);
		OOSL_REAL_LIT_0_PARSER_DEF(double_);

		x3::rule<class integral_literal, ast::integral_literal> const integral_literal = "integral_literal";
		x3::rule<class real_literal, ast::real_literal> const real_literal = "real_literal";
		x3::rule<class numeric_literal, ast::numeric_literal> const numeric_literal = "numeric_literal";

		auto const integral_literal_def = (int8_literal | int16_literal | int32_literal | int64_literal | int32_0_literal);
		auto const real_literal_def = (float_literal | double_literal | long_double_literal | double__0_literal);
		auto const numeric_literal_def = (real_literal_def | integral_literal_def);

		BOOST_SPIRIT_DEFINE(
			integral_literal,
			real_literal,
			numeric_literal
		)
	}
}

#endif /* !OOSL_LITERAL_PARSER_H */
