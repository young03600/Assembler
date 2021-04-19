#include "typeUinst.h"

TypeUinst::TypeUinst() 
{
}

TypeUinst::TypeUinst(const string &_command, const string &_rd, const string &_imm)
	: Instruction("0110111")
{
	temp_command = new string();
	temp_command->assign(_command);

	temp_rd = new string();
	temp_rd->assign(_rd.begin() + 1, _rd.end());

	temp_imm = new string();
	temp_imm->assign(_imm);
}

TypeUinst::~TypeUinst() 
{
}

void TypeUinst::set_rs2(const string &_rs2)
{
	copy(_rs2.begin(), _rs2.end(), get_rs2());
}

void TypeUinst::transfer() 
{
	if(*temp_command == "auipc")
		Instruction::set_opcode("0010111");

	Instruction::set_rd(*temp_rd);

	string decimal_to_binary = to_binary_string(20, *temp_imm);

	Instruction::set_func5(decimal_to_binary.substr(0, 5));

	Instruction::set_func2(decimal_to_binary.substr(5, 2));

	set_rs2(decimal_to_binary.substr(7, 5));

	Instruction::set_rs1(decimal_to_binary.substr(12, 5));

	Instruction::set_func3(decimal_to_binary.substr(17, 3));
}

void TypeUinst::print() const
{
	cout << " |" << setw(17) << " simm[31:12] " << setw(4) << "|" << " rd  |" << " opcode |" << '\n';
	cout << setw(7) << get_func5() << get_func2() << get_rs2()
		<< get_rs1() << get_func3() << setw(6) << get_rd()
		<< setw(9) << get_opcode() << "\n\n";
}