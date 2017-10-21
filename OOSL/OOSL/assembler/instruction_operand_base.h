#pragma once

#ifndef OOSL_INSTRUCTION_OPERAND_BASE_H
#define OOSL_INSTRUCTION_OPERAND_BASE_H

#include "../memory/memory_register.h"

namespace oosl{
	namespace assembler{
		enum class instruction_error{
			nil,
			bad_operation,
			bad_conversion,
		};

		class instruction_operand_base{
		public:
			typedef unsigned __int8 byte_type;
			typedef unsigned __int16 word_type;
			typedef unsigned __int32 dword_type;
			typedef unsigned __int64 qword_type;

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
		};
	}
}

#endif /* !OOSL_INSTRUCTION_OPERAND_BASE_H */
