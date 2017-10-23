#pragma once

#ifndef OOSL_MEMORY_STACK_H
#define OOSL_MEMORY_STACK_H

#include <memory>

namespace oosl{
	namespace memory{
		enum class stack_error{
			nil,
			overflow,
			underflow,
		};

		class stack{
		public:
			typedef unsigned __int64 uint64_type;
			typedef std::size_t size_type;

			explicit stack(size_type data_size = 0u);

			void create(size_type data_size = 0u);

			char *begin() const;

			template <typename value_type>
			void push(value_type value){
				push_(reinterpret_cast<char *>(&value), sizeof(value_type));
			}

			template <typename value_type>
			value_type pop(){
				auto value = value_type();
				pop_(reinterpret_cast<char *>(&value), sizeof(value_type));
				return value;
			}

		private:
			void push_(const char *value, size_type size);

			void pop_(char *value, size_type size);

			uint64_type address_;
			char *data_;
			char *max_;
		};
	}
}

#endif /* !OOSL_MEMORY_STACK_H */
