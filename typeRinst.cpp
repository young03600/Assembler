#include "typeRinst.h"

TypeRinst::TypeRinst()
{
}

TypeRinst::TypeRinst(const string &_command, const string &_rd, const string &_rs1, const string &_rs2)
	: Instruction("0110011")
{
	temp_command = new string();
	temp_command->assign(_command);

	temp_rd = new string();
	temp_rd->assign(_rd.begin() + 1, _rd.end());

	temp_rs1 = new string();
	temp_rs1->assign(_rs1.begin() + 1, _rs1.end());

	temp_rs2 = new string();
	temp_rs2->assign(_rs2.begin() + 1, _rs2.end());
}

TypeRinst::~TypeRinst() 
{
	delete temp_rd;
	temp_rd = nullptr;
	
	delete temp_rs1;
	temp_rs1 = nullptr;

	delete temp_rs2;
	temp_rs2 = nullptr;
}

void TypeRinst::transfer() 
{
	Instruction::set_rd(*temp_rd);
	Instruction::set_rs1(*temp_rs1);
	Instruction::set_rs2(*temp_rs2);
	Instruction::set_func2("00");
	if (*temp_command == "sub" || *temp_command == "sra")
		Instruction::set_func5("01000");
	else
		Instruction::set_func5("00000");

	if(*temp_command == "add" || *temp_command == "sub")
		Instruction::set_func3("000");
	else if(*temp_command == "sll")
		Instruction::set_func3("001");
	else if(*temp_command == "slt")
		Instruction::set_func3("010");
	else if(*temp_command == "sltu")
		Instruction::set_func3("011");
	else if(*temp_command == "xor")
		Instruction::set_func3("100");
	else if(*temp_command == "srl" || *temp_command == "sra")
		Instruction::set_func3("101");
	else if(*temp_command == "or")
		Instruction::set_func3("110");
	else
		Instruction::set_func3("111"); // and

}

void TypeRinst::print() const 
{
	cout << " |" << " f5" << "  |" << "f2" << "| rs2 |" << " rs1 |" << "f3 |" << " rd  |" << " opcode |" << '\n';

	cout << "  " << get_func5() << ' ' << get_func2() << ' ' << get_rs2()
		 << ' ' << get_rs1()    << ' '  << get_func3() << ' ' << get_rd()
		 << "  " << get_opcode() << "\n\n";
}