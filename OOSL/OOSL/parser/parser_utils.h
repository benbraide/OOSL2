#pragma once

#ifndef OOSL_PARSER_UTILS_H
#define OOSL_PARSER_UTILS_H

#include "ast/ast.h"

namespace oosl{
	namespace parser{
		namespace x3 = boost::spirit::x3;

		template <typename value_type>
		struct real_policies : x3::real_policies<value_type>{
			static bool const expect_dot = true;
			static bool const allow_leading_dot = true;
			static bool const allow_trailing_dot = true;
		};

		using float_parser = x3::real_parser<float, real_policies<float>>;
		using double_parser = x3::real_parser<double, real_policies<double>>;
		using long_double_parser = x3::real_parser<long double, real_policies<long double>>;

		float_parser const float_ = {};
		double_parser const double_ = {};
		long_double_parser const long_double_ = {};

		struct identifier_ast{
			char first;
			std::vector<char> rest;
		};

		class utils{
		public:
			template <typename parser_type>
			static auto keyword(parser_type &&parser){
				return x3::lexeme[parser >> !x3::char_("$_A-Za-z0-9")];
			};

			static auto keyword(const char *value){
				return keyword(x3::lit(value));
			}

			static void identifier_to_string(const identifier_ast &ast, std::string &value){
				value.reserve(ast.rest.size() + 2);
				value.append(1, ast.first);
				value.append(ast.rest.data(), ast.rest.size());
			}
		};

		x3::rule<class utils_identifier, identifier_ast> const utils_identifier = "utils_identifier";
		auto const utils_identifier_def = x3::lexeme[x3::char_("$_A-Za-z") >> *x3::char_("$_A-Za-z0-9")];

		BOOST_SPIRIT_DEFINE(utils_identifier);
	}
}

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::identifier_ast,
	(char, first)
	(std::vector<char>, rest)
)

#endif /* !OOSL_PARSER_UTILS_H */
