#pragma once

#ifndef OOSL_MEMORY_REGISTER_H
#define OOSL_MEMORY_REGISTER_H

#include <string>
#include <memory>
#include <unordered_map>

#include "memory_stack.h"

namespace oosl{
	namespace memory{
		enum class register_error{
			nil,
			not_found,
		};

		enum class register_value_type{
			byte,
			word,
			dword,
			qword,
			float_,
			double_,
			ldouble,
			unknown,
		};

		class register_value_base{
		public:
			typedef std::size_t size_type;

			typedef unsigned __int8 byte_type;
			typedef unsigned __int16 word_type;
			typedef unsigned __int32 dword_type;
			typedef unsigned __int64 qword_type;

			typedef stack stack_type;

			virtual register_value_type type() const = 0;

			virtual size_type size() const = 0;

			virtual byte_type read_byte() const = 0;

			virtual word_type read_word() const = 0;

			virtual dword_type read_dword() const = 0;

			virtual qword_type read_qword() const = 0;

			virtual float read_float() const = 0;

			virtual double read_double() const = 0;

			virtual long double read_ldouble() const = 0;

			virtual char *read_address() const = 0;

			virtual void read(void *buffer, size_type size) const = 0;

			template <typename value_type>
			value_type read() const{
				auto value = value_type();
				read(&value, sizeof(value_type));
				return value;
			}

			virtual void write_byte(byte_type value) = 0;

			virtual void write_word(word_type value) = 0;

			virtual void write_dword(dword_type value) = 0;

			virtual void write_qword(qword_type value) = 0;

			virtual void write_float(float value) = 0;

			virtual void write_double(double value) = 0;

			virtual void write_ldouble(long double value) = 0;

			virtual void write_address(const char *value) = 0;

			virtual void write(const void *buffer, size_type size) = 0;

			template <typename value_type>
			void write(value_type value){
				write(&value, sizeof(value_type));
			}

			virtual char *push_onto_stack(char *stack_pointer, stack_type &stack) = 0;

			virtual char *pop_from_stack(char *stack_pointer, stack_type &stack) = 0;
		};

		template <class value_type>
		class register_value : public register_value_base{
		public:
			typedef value_type value_type;

			register_value()
				: value_(){}

			virtual register_value_type type() const override{
				if (std::is_same_v<value_type, byte_type>)
					return register_value_type::byte;

				if (std::is_same_v<value_type, word_type>)
					return register_value_type::word;

				if (std::is_same_v<value_type, dword_type>)
					return register_value_type::dword;

				if (std::is_same_v<value_type, qword_type>)
					return register_value_type::qword;

				if (std::is_same_v<value_type, float>)
					return register_value_type::float_;

				if (std::is_same_v<value_type, double>)
					return register_value_type::double_;

				if (std::is_same_v<value_type, long double>)
					return register_value_type::ldouble;

				return register_value_type::unknown;
			}

			virtual size_type size() const override{
				return static_cast<size_type>(sizeof(value_type));
			}

			virtual byte_type read_byte() const override{
				return static_cast<byte_type>(value_);
			}

			virtual word_type read_word() const override{
				return static_cast<word_type>(value_);
			}

			virtual dword_type read_dword() const override{
				return static_cast<dword_type>(value_);
			}

			virtual qword_type read_qword() const override{
				return static_cast<qword_type>(value_);
			}

			virtual float read_float() const override{
				return static_cast<float>(value_);
			}

			virtual double read_double() const override{
				return static_cast<double>(value_);
			}

			virtual long double read_ldouble() const override{
				return static_cast<long double>(value_);
			}

			virtual char *read_address() const override{
				return reinterpret_cast<char *>(read_qword());
			}

			virtual void read(void *buffer, size_type size) const override{
				memcpy(buffer, &value_, size);
			}

			virtual void write_byte(byte_type value) override{
				value_ = static_cast<value_type>(value);
			}

			virtual void write_word(word_type value) override{
				value_ = static_cast<value_type>(value);
			}

			virtual void write_dword(dword_type value) override{
				value_ = static_cast<value_type>(value);
			}

			virtual void write_qword(qword_type value) override{
				value_ = static_cast<value_type>(value);
			}

			virtual void write_float(float value) override{
				value_ = static_cast<value_type>(value);
			}

			virtual void write_double(double value) override{
				value_ = static_cast<value_type>(value);
			}

			virtual void write_ldouble(long double value) override{
				value_ = static_cast<value_type>(value);
			}

			virtual void write_address(const char *value) override{
				write_qword(reinterpret_cast<qword_type>(value));
			}

			virtual void write(const void *buffer, size_type size) override{
				memcpy(&value_, buffer, size);
			}

			virtual char *push_onto_stack(char *stack_pointer, stack_type &stack) override{
				return stack.push(stack_pointer, value_);
			}

			virtual char *pop_from_stack(char *stack_pointer, stack_type &stack) override{
				value_ = stack.pop<value_type>(stack_pointer);
				return stack_pointer;
			}

		private:
			value_type value_;
		};

		class register_{
		public:
			typedef unsigned __int8 byte_type;
			typedef unsigned __int16 word_type;
			typedef unsigned __int32 dword_type;
			typedef unsigned __int64 qword_type;

			typedef std::shared_ptr<register_value_base> register_value_ptr_type;
			typedef std::unordered_map<std::string, register_value_ptr_type> map_type;

			register_();

			register_value_base *find(const std::string &key) const;

		private:
			map_type map_;
		};
	}
}

#endif /* !OOSL_MEMORY_REGISTER_H */
