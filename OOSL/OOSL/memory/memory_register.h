#pragma once

#ifndef OOSL_MEMORY_REGISTER_H
#define OOSL_MEMORY_REGISTER_H

#include <string>
#include <memory>
#include <unordered_map>

#include "../common/macro.h"

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

		enum class register_flag : unsigned int{
			nil				= (0 << 0x0000),
			zero			= (1 << 0x0000),
			less			= (1 << 0x0001),
		};

		class register_value_base{
		public:
			typedef std::size_t size_type;

			typedef unsigned __int8 byte_type;
			typedef unsigned __int16 word_type;
			typedef unsigned __int32 dword_type;
			typedef unsigned __int64 qword_type;

			typedef stack stack_type;

			virtual const std::string &name() const = 0;

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

			virtual void push_onto_stack(stack_type &stack) = 0;

			virtual void pop_from_stack(stack_type &stack) = 0;
		};

		template <class value_type>
		class basic_register_value : public register_value_base{
		public:
			typedef value_type value_type;

			basic_register_value(const std::string &name, value_type *value_ref)
				: name_(name), value_ref_(value_ref){}

			virtual const std::string &name() const override{
				return name_;
			}

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
				return static_cast<byte_type>(*value_ref_);
			}

			virtual word_type read_word() const override{
				return static_cast<word_type>(*value_ref_);
			}

			virtual dword_type read_dword() const override{
				return static_cast<dword_type>(*value_ref_);
			}

			virtual qword_type read_qword() const override{
				return static_cast<qword_type>(*value_ref_);
			}

			virtual float read_float() const override{
				return static_cast<float>(*value_ref_);
			}

			virtual double read_double() const override{
				return static_cast<double>(*value_ref_);
			}

			virtual long double read_ldouble() const override{
				return static_cast<long double>(*value_ref_);
			}

			virtual char *read_address() const override{
				return reinterpret_cast<char *>(read_qword());
			}

			virtual void read(void *buffer, size_type size) const override{
				memcpy(buffer, value_ref_, size);
			}

			virtual void write_byte(byte_type value) override{
				*value_ref_ = static_cast<value_type>(value);
			}

			virtual void write_word(word_type value) override{
				*value_ref_ = static_cast<value_type>(value);
			}

			virtual void write_dword(dword_type value) override{
				*value_ref_ = static_cast<value_type>(value);
			}

			virtual void write_qword(qword_type value) override{
				*value_ref_ = static_cast<value_type>(value);
			}

			virtual void write_float(float value) override{
				*value_ref_ = static_cast<value_type>(value);
			}

			virtual void write_double(double value) override{
				*value_ref_ = static_cast<value_type>(value);
			}

			virtual void write_ldouble(long double value) override{
				*value_ref_ = static_cast<value_type>(value);
			}

			virtual void write_address(const char *value) override{
				write_qword(reinterpret_cast<qword_type>(value));
			}

			virtual void write(const void *buffer, size_type size) override{
				memcpy(value_ref_, buffer, size);
			}

			virtual void push_onto_stack(stack_type &stack) override{
				stack.push(*value_ref_);
			}

			virtual void pop_from_stack(stack_type &stack) override{
				*value_ref_ = stack.pop<value_type>();
			}

			template <typename target_type>
			target_type *low() const{
				return reinterpret_cast<target_type *>(value_ref_);
			}

			template <typename target_type>
			target_type *high() const{
				return (reinterpret_cast<target_type *>(value_ref_) + 1);
			}

		private:
			std::string name_;
			value_type *value_ref_;
		};

		template <class value_type>
		class register_value : public basic_register_value<value_type>{
		public:
			typedef basic_register_value<value_type> base_type;

			explicit register_value(const std::string &name, value_type value = value_type())
				: base_type(name, &value_), value_(value){}

		private:
			value_type value_;
		};

		template <class value_type>
		using register_ref_value = basic_register_value<value_type>;

		class register_{
		public:
			typedef unsigned __int8 byte_type;
			typedef unsigned __int16 word_type;
			typedef unsigned __int32 dword_type;
			typedef unsigned __int64 qword_type;

			typedef std::shared_ptr<register_value_base> register_value_ptr_type;
			typedef std::unordered_map<std::string, register_value_ptr_type> map_type;

			register_();

			register_value_base *find(std::string key) const;

			void update_flag(register_flag flag, bool clear);

			void update_zero_flag(bool clear);

			void update_less_flag(bool clear);

			bool has_flag(register_flag flag) const;

			bool has_zero_flag() const;

			bool has_less_flag() const;

			static void to_lower(std::string &value);

		private:
			template <typename value_type, typename smaller_type>
			void add_(const std::string &name, const std::string &low, const std::string &high){
				auto value = std::make_shared<register_value<value_type>>(name);
				if (!low.empty())
					map_[low] = std::make_shared<register_ref_value<smaller_type>>(name, value->low<smaller_type>());

				if (!high.empty())
					map_[high] = std::make_shared<register_ref_value<smaller_type>>(name, value->high<smaller_type>());

				map_[name] = value;
			}

			void add_(const std::string &name, const std::string &alias, const std::string &_32, const std::string &_16, const std::string &low, const std::string &high);

			void add_qword_(int from, int to);

			template <typename value_type>
			void add_float_(const std::string &prefix, int from, int to){
				std::string name;
				for (; from <= to; ++from){//Add entries
					name = (prefix + std::to_string(from));
					map_[name] = std::make_shared<register_value<value_type>>(name);
				}
			}

			register_flag flags_;
			map_type map_;
		};

		OOSL_MAKE_OPERATORS(register_flag);
	}
}

#endif /* !OOSL_MEMORY_REGISTER_H */
