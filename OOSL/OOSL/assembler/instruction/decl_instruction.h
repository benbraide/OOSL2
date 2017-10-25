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
				typedef std::shared_ptr<decl_operand> ptr_type;

				typedef oosl::common::writer_base writer_type;

				virtual ~decl_operand() = default;

				virtual size_type count(size_type byte_size) const = 0;

				virtual void write(char *buffer, size_type byte_size) const = 0;

				virtual long long read_int() const{
					throw instruction_error::bad_conversion;
				}

				virtual double read_float() const{
					throw instruction_error::bad_conversion;
				}

				virtual bool is_float() const{
					return false;
				}

				virtual void print(writer_type &writer) const = 0;
			};

			template <id id_value, std::size_t byte_size>
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
					return id_value;
				}

				virtual size_type instruction_bytes() const override{
					return instruction_bytes_;
				}

				virtual void execute() const override{
					auto memory_buffer = assembler::vm::memory.allocate(instruction_bytes_, assembler::vm::rip->read_qword())->data.get();
					for (auto item : operands_){//Write operand values
						item->write(memory_buffer, byte_size);
						memory_buffer += (item->count(byte_size) * byte_size);//Advance buffer
					}
				}

				virtual void print(writer_type &writer) const override{
					writer.write(id_to_string(id()));
					writer.write(" ");

					auto is_first = true;
					for (auto item : operands_){
						if (is_first)
							is_first = false;
						else//Print delimiter
							writer.write(", ");

						item->print(writer);
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

			using byte_decl = decl<id::db, sizeof(unsigned __int8)>;
			using word_decl = decl<id::dw, sizeof(unsigned __int16)>;
			using dword_decl = decl<id::dd, sizeof(unsigned __int32)>;
			using qword_decl = decl<id::dq, sizeof(unsigned __int64)>;

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

				virtual void print(writer_type &writer) const override{
					writer.write("'");
					writer.write(value_);
					writer.write("'");
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

				virtual long long read_int() const override{
					return static_cast<long long>(value_);
				}

				virtual double read_float() const override{
					return static_cast<double>(value_);
				}

				virtual void print(writer_type &writer) const override{
					writer.write(std::to_string(value_));
				}

			private:
				template <typename value_type>
				void write_(value_type value, char *buffer, size_type byte_size) const{
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

				virtual long long read_int() const override{
					return static_cast<long long>(value_);
				}

				virtual double read_float() const override{
					return static_cast<double>(value_);
				}

				virtual bool is_float() const override{
					return true;
				}

				virtual void print(writer_type &writer) const override{
					writer.write(std::to_string(value_));
				}

			private:
				template <typename value_type>
				void write_(value_type value, char *buffer, size_type byte_size) const{
					memcpy(buffer, &value_, byte_size);
				}

				value_type value_;
			};

			class expr_decl_operand : public decl_operand{
			public:
				typedef assembler::instruction_operand_base::operator_type operator_type;

				explicit expr_decl_operand(operator_type op, ptr_type left, ptr_type right)
					: op_(op), left_(left), right_(right){}

				virtual ~expr_decl_operand() = default;

				virtual size_type count(size_type byte_size) const override{
					if (value_ == nullptr)
						eval_();//Evaluate expression
					return value_->count(byte_size);
				}

				virtual void write(char *buffer, size_type byte_size) const override{
					if (value_ == nullptr)
						eval_();//Evaluate expression
					value_->write(buffer, byte_size);
				}

				virtual long long read_int() const override{
					if (value_ == nullptr)
						eval_();//Evaluate expression
					return value_->read_int();
				}

				virtual double read_float() const override{
					if (value_ == nullptr)
						eval_();//Evaluate expression
					return value_->read_float();
				}

				virtual bool is_float() const override{
					return (left_->is_float() || right_->is_float());
				}

				virtual void print(writer_type &writer) const override{
					left_->print(writer);
					switch (op_){
					case operator_type::add:
						writer.write(" + ");
						break;
					case operator_type::sub:
						writer.write(" - ");
						break;
					case operator_type::mult:
						writer.write(" * ");
						break;
					case operator_type::div:
						writer.write(" / ");
						break;
					case operator_type::mod:
						writer.write(" % ");
						break;
					case operator_type::bit_and:
						writer.write(" & ");
						break;
					case operator_type::bit_or:
						writer.write(" | ");
						break;
					case operator_type::bit_xor:
						writer.write(" ^ ");
						break;
					case operator_type::lshift:
						writer.write(" << ");
						break;
					case operator_type::rshift:
						writer.write(" >> ");
						break;
					default:
						break;
					}
					right_->print(writer);
				}

			private:
				void eval_() const{
					if (is_float())
						value_ = eval_<integral_decl_operand<double>>(left_->read_float(), right_->read_float());
					else//Integral
						value_ = eval_integral_(left_->read_int(), right_->read_int());
				}

				template <typename target_type, typename value_type>
				ptr_type eval_(value_type left, value_type right) const{
					switch (op_){
					case operator_type::add:
						return std::make_shared<target_type>(left + right);
					case operator_type::sub:
						return std::make_shared<target_type>(left - right);
					case operator_type::mult:
						return std::make_shared<target_type>(left * right);
					case operator_type::div:
						return std::make_shared<target_type>(left / right);
					default:
						break;
					}

					throw instruction_error::bad_operation;
				}

				ptr_type eval_integral_(long long left, long long right) const{
					switch (op_){
					case operator_type::mod:
						return std::make_shared<integral_decl_operand<long long>>(left % right);
					case operator_type::bit_and:
						return std::make_shared<integral_decl_operand<long long>>(left & right);
					case operator_type::bit_xor:
						return std::make_shared<integral_decl_operand<long long>>(left ^ right);
					case operator_type::bit_or:
						return std::make_shared<integral_decl_operand<long long>>(left | right);
					case operator_type::lshift:
						return std::make_shared<integral_decl_operand<long long>>(left << right);
					case operator_type::rshift:
						return std::make_shared<integral_decl_operand<long long>>(left >> right);
					default:
						break;
					}

					return eval_<integral_decl_operand<long long>>(left, right);
				}

				operator_type op_;
				ptr_type left_;
				ptr_type right_;
				mutable ptr_type value_;
			};

			class grouped_expr_decl_operand : public decl_operand{
			public:
				explicit grouped_expr_decl_operand(ptr_type value)
					: value_(value){}

				virtual ~grouped_expr_decl_operand() = default;

				virtual size_type count(size_type byte_size) const override{
					return value_->count(byte_size);
				}

				virtual void write(char *buffer, size_type byte_size) const override{
					value_->write(buffer, byte_size);
				}

				virtual long long read_int() const override{
					return value_->read_int();
				}

				virtual double read_float() const override{
					return value_->read_float();
				}

				virtual bool is_float() const override{
					return value_->is_float();
				}

				virtual void print(writer_type &writer) const override{
					writer.write("(");
					value_->print(writer);
					writer.write(")");
				}

			private:
				ptr_type value_;
			};
		}
	}
}

#endif /* !OOSL_DECL_INSTRUCTION_H */
