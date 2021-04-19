#include "typeSinst.h"

TypeSinst::TypeSinst()
{
}

TypeSinst::TypeSinst(const string &_command, const string &_rs2, const string &_imm)
	: Instruction("0100011")
{
	temp_command = new string();
	temp_command->assign(_command);

	temp_rs2 = new string();
	temp_rs2->assign(_rs2.begin() + 1, _rs2.end());


	temp_imm = new string();
	size_t pos_of_left_para = _imm.find('(');
	temp_imm->assign(_imm.begin(), _imm.begin() + pos_of_left_para);

	temp_rs1 = new string();
	temp_rs1->assign(_imm.begin() + pos_of_left_para + 2, _imm.end() - 1); // for delimeter (x // +2
}

TypeSinst::~TypeSinst() 
{
	delete temp_command;
	temp_command = nullptr;

	delete temp_rs2;
	temp_rs2 = nullptr;

	delete temp_imm;
	temp_imm = nullptr;

	delete temp_rs1;
	temp_rs1 = nullptr;
}

void TypeSinst::set_rd(const string &_rd)
{
	copy(_rd.begin(), _rd.end(), get_rd());
}
void TypeSinst::set_func2(const string &_func2)
{
	copy(_func2.begin(), _func2.end(), get_func2());
}

void TypeSinst::set_func5(const string &_func5)
{
	copy(_func5.begin(), _func5.end(), get_func5());
}

void TypeSinst::transfer()
{
	Instruction::set_rs1(*temp_rs1);
	Instruction::set_rs2(*temp_rs2);

	if (*temp_command == "sb")
		Instruction::set_func3("000");
	else if (*temp_command == "sh")
		Instruction::set_func3("001");
	else
		Instruction::set_func3("010");            // sw

	string decimal_to_binary = to_binary_string(12, *temp_imm);

	set_func5(decimal_to_binary.substr(0, 5));    
	set_func2(decimal_to_binary.substr(5, 2));   										  
		     									  // total  7 bits

	set_rd(decimal_to_binary.substr(7, 5));       // last 5 bits
}

void TypeSinst::print() const 
{
	cout << " |" << " simm[11:5] " << "| rs2 |" << " rs1 |" << "f3 |" << " simm[4:0] |" << " opcode |" << '\n';

	cout << setw(10) << get_func5()  << get_func2() << "   "       << get_rs2()
		 << ' '      << get_rs1()    << ' '         << get_func3() << setw(9)   << get_rd()
		 << setw(12) << get_opcode() << "\n\n";
}