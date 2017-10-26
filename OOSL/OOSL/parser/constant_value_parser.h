#pragma once

#ifndef OOSL_CONSTANT_VALUE_PARSER_H
#define OOSL_CONSTANT_VALUE_PARSER_H

#include "ast/constant_value_ast.h"

namespace oosl{
	namespace parser{
		namespace x3 = boost::spirit::x3;

		struct constant_value_symbols : x3::symbols<oosl::common::constant_value>{
			constant_value_symbols(){
				add
					("true", oosl::common::constant_value::true_)
					("false", oosl::common::constant_value::false_)
					("indeterminate", oosl::common::constant_value::indeterminate)
					("word", oosl::common::constant_value::nullptr_)
					("NaN", oosl::common::constant_value::nan_)
					("undefined", oosl::common::constant_value::undefined)
					;
			}
		} constant_value_symbols_;

		x3::rule<class constant_value, ast::constant_value> const constant_value = "constant_value";

		auto const constant_value_def = utils::keyword(constant_value_symbols_);

		BOOST_SPIRIT_DEFINE(constant_value);
	}
}

#endif /* !OOSL_CONSTANT_VALUE_PARSER_H */
