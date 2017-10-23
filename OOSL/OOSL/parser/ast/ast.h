#pragma once

#ifndef OOSL_AST_H
#define OOSL_AST_H

#include <string>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#define OOSL_AST_JOIN_(x, y) x ## y
#define OOSL_AST_JOIN(x, y) OOSL_AST_JOIN_(x, y)

#define OOSL_AST_PREFIX										\
namespace x3 = boost::spirit::x3;

#define OOSL_AST_BEGIN namespace oosl::parser::ast{

OOSL_AST_PREFIX

#define OOSL_AST_END }

#define OOSL_AST_DECLARE_SINGLE(name, type)					\
struct name{												\
	typedef type value_type;								\
	type value;												\
};

#define OOSL_AST_DECLARE_SINGLE_WPOS(name, type)			\
struct name : x3::position_tagged{							\
	typedef type value_type;								\
	value_type value;										\
};

#define OOSL_AST_DECLARE_SINGLE_VARIANT(name, ...)			\
struct name{												\
	typedef boost::variant<__VA_ARGS__> value_type;			\
	value_type value;										\
};

#define OOSL_AST_ADAPT_SINGLE(name)							\
BOOST_FUSION_ADAPT_STRUCT(									\
	oosl::parser::ast::name,								\
	(oosl::parser::ast::name::value_type, value)			\
)

#endif /* !OOSL_AST_H */
