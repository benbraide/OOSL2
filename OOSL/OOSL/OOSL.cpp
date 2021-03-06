#include <iostream>

#include "parser/assembler_parser.h"
#include "parser/constant_value_parser.h"
#include "parser/literal_parser.h"

int main(){
	oosl::parser::ast::asm_instruction_set op;
	std::string gram = "section .text prefix: mov rax, 9 .inner: ret main: mov eax, ebp mov eax, rax call prefix xor eax, eax db 'benbraide', 0, 18, 27 mov eax, 1 mov ebx, 9 int 0x80";

	class mini_writer : public oosl::common::writer_base{
	public:
		virtual writer_base &begin() override{
			throw std::logic_error("The method or operation is not implemented.");
		}

		virtual writer_base &end() override{
			throw std::logic_error("The method or operation is not implemented.");
		}

		virtual writer_base &write(const char *value) override{
			std::cout << value;
			return *this;
		}

		virtual writer_base &write(const wchar_t *value) override{
			std::wcout << value;
			return *this;
		}
	} mini_writer_;

	auto r = boost::spirit::x3::phrase_parse(gram.data(), gram.data() + gram.size(), oosl::parser::assembler::asm_instruction_set, oosl::parser::assembler::asm_skip, op);
	if (r){
		for (auto &ins : op.value){
			auto ins_v = oosl::parser::ast::asm_traverser::get(ins);
			ins_v->create_or_add_to_section();
			ins_v->print(mini_writer_);
			mini_writer_.write("\n");
		}

		oosl::assembler::vm::bundle();
		oosl::assembler::vm::execute();
	}

	return 0;
}
