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
			typedef std::size_t size_type;
			typedef std::unique_ptr<char[]> data_type;

			explicit stack(size_type data_size = (1024 * 1024));//Default size is 1MB

			char *begin() const;

			template <typename value_type>
			char *push(char *current, value_type value){
				current += sizeof(value_type);
				if (current > max_)//Overflow
					throw stack_error::overflow;

				memcpy(current, &value, sizeof(value_type));
				return current;
			}

			template <typename value_type>
			value_type pop(char *&current){
				auto value = value_type();
				memcpy(&value, current, sizeof(value_type));

				current -= sizeof(value_type);
				if (current < data_.get())//Underflow
					throw stack_error::underflow;

				return value;
			}

		private:
			data_type data_;
			char *max_;
		};
	}
}

#endif /* !OOSL_MEMORY_STACK_H */
