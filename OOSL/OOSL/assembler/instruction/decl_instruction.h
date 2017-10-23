#pragma once

#ifndef OOSL_DECL_INSTRUCTION_H
#define OOSL_DECL_INSTRUCTION_H

#include <vector>
#include <memory>

#include "instruction_base.h"

namespace oosl{
	namespace assembler{
		namespace instruction{
			class decl_operand{
			public:
				typedef std::size_t size_type;

				virtual ~decl_operand() = default;

				virtual size_type count(size_type byte_size) const = 0;

				virtual void write(char *buffer, size_type byte_size) const = 0;
			};

			template <std::size_t byte_size>
			class decl : public base{
			public:
				typedef std::shared_ptr<decl_operand> decl_operand_ptr_type;
				typedef std::vector<decl_operand_ptr_type> operand_list_type;

				explicit decl(const operand_list_type &operands)
					: operands_(operands){
					compute_instruction_bytes_();
				}

				explicit decl(operand_list_type &&operands)
					: operands_(std::move(operands)){
					compute_instruction_bytes_();
				}

				virtual ~decl() = default;

				virtual id_type id() const override{
					return id_type::decl;
				}

				virtual size_type instruction_bytes() const override{
					return instruction_bytes_;
				}

				virtual void execute() const override{
					auto memory_buffer = assembler::vm::memory.allocate(instruction_bytes_, assembler::vm::register_.find("rip")->read_qword())->data;
					for (auto item : operands_){//Write operand values
						item->write(memory_buffer, byte_size);
						memory_buffer += (item->count() * byte_size);//Advance buffer
					}
				}

			protected:
				void compute_instruction_bytes_(){
					size_type count = 0u;
					for (auto item : operands_)
						count += item->count(byte_size);

					instruction_bytes_ = (count * byte_size);
				}

				size_type instruction_bytes_;
				operand_list_type operands_;
			};

			using byte_decl = decl<sizeof(unsigned __int8)>;
			using word_decl = decl<sizeof(unsigned __int16)>;
			using dword_decl = decl<sizeof(unsigned __int32)>;
			using qword_decl = decl<sizeof(unsigned __int64)>;

			class string_decl_operand : public decl_operand{
			public:
				explicit string_decl_operand(const std::string &value)
					: value_(value){}

				explicit string_decl_operand(std::string &&value)
					: value_(std::move(value)){}

				virtual ~string_decl_operand() = default;

				virtual size_type count(size_type byte_size) const override{
					auto char_count = value_.size();
					if ((char_count % byte_size) != 0u)//Error
						throw instruction_error::bad_conversion;
					return (char_count / byte_size);
				}

				virtual void write(char *buffer, size_type byte_size) const override{
					memcpy(buffer, value_.data(), value_.size());
				}

			private:
				std::string value_;
			};

			template <class value_type>
			class integral_decl_operand : public decl_operand{
			public:
				typedef value_type value_type;

				explicit integral_decl_operand(value_type value)
					: value_(value){}

				virtual ~integral_decl_operand() = default;

				virtual size_type count(size_type byte_size) const override{
					return 1u;
				}

				virtual void write(char *buffer, size_type byte_size) const override{
					switch (byte_size){
					case 1u:
						write_(static_cast<unsigned __int8>(value_), buffer, byte_size);
						break;
					case 2u:
						write_(static_cast<unsigned __int16>(value_), buffer, byte_size);
						break;
					case 4u:
						write_(static_cast<unsigned __int32>(value_), buffer, byte_size);
						break;
					case 8u:
						write_(static_cast<unsigned __int64>(value_), buffer, byte_size);
						break;
					default:
						throw instruction_error::bad_operation;
						break;
					}
				}

			private:
				template <typename value_type>
				void write_(value_type value, char *buffer, size_type byte_size){
					memcpy(buffer, &value_, byte_size);
				}

				value_type value_;
			};

			template <class value_type>
			class float_decl_operand : public decl_operand{
			public:
				typedef value_type value_type;

				explicit float_decl_operand(value_type value)
					: value_(value){}

				virtual ~float_decl_operand() = default;

				virtual size_type count(size_type byte_size) const override{
					return 1u;
				}

				virtual void write(char *buffer, size_type byte_size) const override{
					if (sizeof(value_type) < byte_size)//Promote value
						write_(static_cast<long double>(value_), buffer, byte_size);
					else//Copy sufficient bytes
						write_(value_, buffer, byte_size);
				}

			private:
				template <typename value_type>
				void write_(value_type value, char *buffer, size_type byte_size){
					memcpy(buffer, &value_, byte_size);
				}

				value_type value_;
			};
		}
	}
}

#endif /* !OOSL_DECL_INSTRUCTION_H */
