#include "typeUJinst.h"

TypeUJinst::TypeUJinst()
{
}

TypeUJinst::TypeUJinst(const string &_command, const string &_rd, const string &_imm)
	: Instruction("1101111")
{
	temp_command = new string();
	temp_command->assign(_command);

	temp_rd = new string();
	temp_rd->assign(_rd.begin() + 1, _rd.end());

	temp_imm = new string();
	temp_imm->assign(_imm);
}

TypeUJinst::~TypeUJinst() 
{
}

void TypeUJinst::set_rs1(const string &_rs1)
{
	copy(_rs1.begin(), _rs1.end(), get_rs1());
}

void TypeUJinst::set_rs2(const string &_rs2) 
{
	char *temp_rs2 = get_rs2();
	for (const auto &bit : _rs2) {
		*temp_rs2 = bit;
		++temp_rs2;
	}
}

void TypeUJinst::set_func5(const string &_func5)
{
	//copy(_func5.begin(), _func5.end(), get_func5() + 1);
	char *temp_func5 = get_func5() + 1;
	for (const auto &bit : _func5) {
		*temp_func5 = bit;
		++temp_func5;
	}
}

void TypeUJinst::transfer()
{
	Instruction::set_rd(*temp_rd);

	string decimal_to_binary = to_binary_string(21, *temp_imm);
	//[20]bit is discarded
	get_func5()[0] = decimal_to_binary[0];

	set_func5(decimal_to_binary.substr(10, 4));
	set_func2(decimal_to_binary.substr(14, 2));
	set_rs2(decimal_to_binary.substr(16, 4));
	
	get_rs2()[4] = decimal_to_binary[9]; // 11

	set_rs1(decimal_to_binary.substr(1, 5));
	Instruction::set_func3(decimal_to_binary.substr(6, 3));
}

void TypeUJinst::print() const
{
	cout << " |" << setw(19) << " simm[20|10:1|11|19:12]" << setw(3) << "|" << " rd  |" << " opcode |" << '\n';
	cout << setw(9) << get_func5() << get_func2() << get_rs2()
		<< get_rs1() << get_func3() << setw(9) << get_rd()
		<< setw(9) << get_opcode() << "\n\n";
}