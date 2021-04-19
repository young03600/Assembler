#include "typeSBinst.h"

TypeSBinst::TypeSBinst()
{
}

TypeSBinst::~TypeSBinst() 
{
}

TypeSBinst::TypeSBinst(const string &_command, const string &_rs1, const string &_rs2, const string &_offset)
	: Instruction("1100011"), temp_command(_command), temp_offset(_offset)
{
	temp_rs1.assign(_rs1.begin() + 1, _rs1.end());
	temp_rs2.assign(_rs2.begin() + 1, _rs2.end());
}

void TypeSBinst::set_rd(const string &_rd)
{
	//copy(_rd.begin(), _rd.end(), get_rd());
	char *temp_rd = get_rd();
	for (const auto &bit : _rd) {
		*temp_rd = bit;
		++temp_rd;
	}
}
void TypeSBinst::set_func2(const string &_func2) 
{
	copy(_func2.begin(), _func2.end(), get_func2());
}

void TypeSBinst::set_func5(const string &_func5) 
{
	//copy(_func5.begin(), _func5.end(), get_func5() + 1);
	char *temp_func5 = get_func5() + 1;
	for (const auto &bit : _func5) {
		*temp_func5 = bit;
		++temp_func5;
	}
}

void TypeSBinst::transfer() 
{
	string decimal_to_binary = to_binary_string(13, temp_offset);
	//discard bit-0
	get_func5()[0] = decimal_to_binary[0];
	get_rd()[4] = decimal_to_binary[1];

	set_func5(decimal_to_binary.substr(2, 4));
	set_func2(decimal_to_binary.substr(6, 2));
	set_rd(decimal_to_binary.substr(8, 4));

	set_rs2(temp_rs2);
	set_rs1(temp_rs1);

	if (temp_command == "beq")
		set_func3("000");
	else if(temp_command == "bne")
		set_func3("001");
	else if(temp_command == "blt")
		set_func3("100");
	else if (temp_command == "bge")
		set_func3("101");
	else if (temp_command == "bltu")
		set_func3("110");
	else if (temp_command == "bgeu")
		set_func3("111");
}


void TypeSBinst::print() const 
{
	cout << " |" << " imm[12|10:5] " << "| rs2 |" << " rs1 |" << "f3 |" << " simm[4:1|11] |" << " opcode |" << '\n';

	cout << setw(12) << get_func5() << get_func2() << "   " << get_rs2()
		<< ' ' << get_rs1() << ' ' << get_func3() << setw(11) << get_rd()
		<< setw(12) << get_opcode() << "\n\n";
}

