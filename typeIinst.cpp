#include "typeIinst.h"

TypeIinst::TypeIinst()
{
}

TypeIinst::TypeIinst(const string &_command, const string &_rd, const string &_imm)
	: Instruction("0010011")
{
	temp_command = new string();
	temp_command->assign(_command);

	temp_rd = new string();
	temp_rd->assign(_rd.begin() + 1, _rd.end());

	temp_imm = new string();
	size_t pos_of_left_para = _imm.find('(');
	temp_imm->assign(_imm.begin(), _imm.begin() + pos_of_left_para);
	temp_rs = new string();
	temp_rs->assign(_imm.begin() + pos_of_left_para + 2, _imm.end() - 1);
}

TypeIinst::TypeIinst(const string &_command, const string &_rd, const string &_rs, const string &_imm)
	: Instruction("0010011")
{
	temp_command = new string();
	temp_command->assign(_command);

	temp_rd = new string();
	temp_rd->assign(_rd.begin() + 1, _rd.end());

	temp_rs = new string();
	temp_rs->assign(_rs.begin() + 1, _rs.end());

	temp_imm = new string();
	temp_imm->assign(_imm);
}

TypeIinst::~TypeIinst() 
{
	delete temp_command;
	temp_command = nullptr;

	delete temp_rd;
	temp_rd = nullptr;

	delete temp_rs;
	temp_rs = nullptr;

	delete temp_imm;
	temp_imm = nullptr;
}

void TypeIinst::set_rs2(const string &_rs2)
{
	copy(_rs2.begin(), _rs2.end(), get_rs2());
}

void TypeIinst::set_func2(const string &_func2) 
{
	copy(_func2.begin(), _func2.end(), get_func2());
}

void TypeIinst::set_func5(const string &_func5)
{
	copy(_func5.begin(), _func5.end(), get_func5());
}

void TypeIinst::transfer() 
{
	if (*temp_command == "jalr")
		Instruction::set_opcode("1100111");
	else if (*temp_command == "lb" || *temp_command == "lh" || *temp_command == "lw" || *temp_command == "lbu" || *temp_command == "lhu")
		Instruction::set_opcode("0000011");


	Instruction::set_rd(*temp_rd);
	Instruction::set_rs1(*temp_rs);

	if (*temp_command == "slli" || *temp_command == "srli" || *temp_command == "srai") {

		Instruction::set_func2("00");

		if (*temp_command == "slli" || *temp_command == "srai")
			Instruction::set_func5("00000");
		else
			Instruction::set_func5("01000");

		Instruction::set_rs2(*temp_imm);

		if (*temp_command == "slli")
			Instruction::set_func3("001");
		else if (*temp_command == "srli" || *temp_command == "srai")
			Instruction::set_func3("101");

		return;
	}


	if (*temp_command == "addi" || *temp_command == "jalr")
		Instruction::set_func3("000");
	else if (*temp_command == "slti")
		Instruction::set_func3("010");
	else if(*temp_command == "sltiu")
		Instruction::set_func3("011");
	else if(*temp_command == "xori")
		Instruction::set_func3("100");
	else if(*temp_command == "ori")
		Instruction::set_func3("110");
	else if(*temp_command == "andi")
		Instruction::set_func3("111");
	else if(*temp_command == "lb")
		Instruction::set_func3("000");	
	else if (*temp_command == "lh")
		Instruction::set_func3("001");
	else if(*temp_command == "lw")
		Instruction::set_func3("010");
	else if (*temp_command == "lbu")
		Instruction::set_func3("100");
	else if (*temp_command == "lhu")
		Instruction::set_func3("101");

	string decimal_to_binary = to_binary_string(12, *temp_imm);
	
	set_func5(decimal_to_binary.substr(0, 5));       // 5bits

	set_func2(decimal_to_binary.substr(5, 2));       // 2bits

	set_rs2(decimal_to_binary.substr(7, 5));         // 5bits
}

void TypeIinst::print() const 
{
	if (*temp_command == "slli" || *temp_command == "srli" || *temp_command == "srai") {
		cout << " |" << " f5 " << " | f2 " << "| shamt[4:0] |" << " rs1 |" << "f3 |" << " rd  |" << " opcode |" << '\n';
		cout << setw(7) << get_func5() << setw(4) << get_func2() << setw(11) << get_rs2()
			 << setw(9) << get_rs1()   << setw(4) << get_func3() << setw(6)  << get_rd()
			 << setw(9) << get_opcode() << "\n\n";

		return;
	}
	
	cout << " |" << setw(12) << " simm[11:0] " << "| rs1 |" << "f3 |" << " rd  |" << " opcode |" << '\n';
	cout << setw(7) << get_func5()  << get_func2() << get_rs2()
	     << setw(6) << get_rs1()    << setw(4)     << get_func3() << setw(6) << get_rd()
	     << setw(9) << get_opcode() << "\n\n";
}