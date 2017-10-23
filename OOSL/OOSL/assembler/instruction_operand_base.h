#pragma once

#ifndef OOSL_INSTRUCTION_OPERAND_BASE_H
#define OOSL_INSTRUCTION_OPERAND_BASE_H

#include <memory>

#include "../common/writer_base.h"
#include "../memory/memory_register.h"

namespace oosl{
	namespace assembler{
		enum class instruction_error{
			nil,
			bad_operation,
			ambiguous_operation,
			bad_conversion,
			bad_identifier,
		};

		enum class instruction_operand_type{
			nil,
			constant_value,
			register_value,
			memory,
			expression,
			identifier,
		};

		class instruction_operand_base : public std::enable_shared_from_this<instruction_operand_base>{
		public:
			typedef unsigned __int8 byte_type;
			typedef unsigned __int16 word_type;
			typedef unsigned __int32 dword_type;
			typedef unsigned __int64 qword_type;

			typedef std::size_t size_type;
			typedef oosl::common::writer_base writer_type;

			typedef oosl::memory::stack stack_type;
			typedef oosl::memory::register_value_type code_type;

			typedef std::shared_ptr<instruction_operand_base> ptr_type;

			enum class operator_type{
				add,
				sub,
				mult,
				div,
				mod,
				bit_and,
				bit_or,
				bit_xor,
				lshift,
				rshift,
				not,
				inc,
				dec,
			};

			virtual ptr_type reflect(){
				return shared_from_this();
			}

			virtual instruction_operand_type type() const = 0;

			virtual code_type code() const{
				throw instruction_error::ambiguous_operation;
			}

			virtual void print(writer_type &writer) const = 0;

			virtual ptr_type eval(){
				return reflect();
			}

			virtual ptr_type apply_operator(operator_type op, instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator ~(){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator ++(){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator --(){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator =(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator +=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator -=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator *=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator /=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator %=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator &=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator |=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator ^=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator <<=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual instruction_operand_base &operator >>=(const instruction_operand_base &rhs){
				throw instruction_error::bad_operation;
			}

			virtual bool operator <(const instruction_operand_base &rhs) const{
				throw instruction_error::bad_operation;
			}

			virtual inline bool operator <=(const instruction_operand_base &rhs) const{
				return (*this < rhs || *this == rhs);
			}

			virtual bool operator ==(const instruction_operand_base &rhs) const{
				throw instruction_error::bad_operation;
			}

			virtual inline bool operator !=(const instruction_operand_base &rhs) const{
				return !(*this == rhs);
			}

			virtual inline bool operator >=(const instruction_operand_base &rhs) const{
				return !(*this < rhs);
			}

			virtual inline bool operator >(const instruction_operand_base &rhs) const{
				return !(*this < rhs || *this == rhs);
			}

			virtual byte_type read_byte() const{
				throw instruction_error::bad_conversion;
			}

			virtual word_type read_word() const{
				throw instruction_error::bad_conversion;
			}

			virtual dword_type read_dword() const{
				throw instruction_error::bad_conversion;
			}

			virtual qword_type read_qword() const{
				throw instruction_error::bad_conversion;
			}

			virtual float read_float() const{
				throw instruction_error::bad_conversion;
			}

			virtual double read_double() const{
				throw instruction_error::bad_conversion;
			}

			virtual long double read_ldouble() const{
				throw instruction_error::bad_conversion;
			}

			virtual void push_onto_stack(stack_type &stack){
				throw instruction_error::bad_operation;
			}

			virtual void pop_from_stack(stack_type &stack){
				throw instruction_error::bad_operation;
			}
		};
	}
}

#endif /* !OOSL_INSTRUCTION_OPERAND_BASE_H */
