#include "Instruction.h"

Instruction::Instruction()
{
}

Instruction::Instruction(const string &_opcode)
{
	set_opcode(_opcode);
	
	opcode[7] = '\0';
	rd[5] = '\0';
	func3[3] = '\0';
	rs1[5] = '\0';
	rs2[5] = '\0';
	func2[2] = '\0';
	func5[5] = '\0';
}

Instruction::~Instruction()
{
}

string Instruction::to_binary_string(const int num_bits, const string &num_decimal) 
{
	char _binary[33];
	int _num = stoi(num_decimal);
	_itoa_s(_num, _binary, 2);

	bitset<32> bits(_binary);
	
	return bits.to_string().substr(32 - num_bits, string::npos);
}


void Instruction::set_opcode(const string &_opcode)
{
	copy(_opcode.begin(), _opcode.end(), opcode);
}

const char *Instruction::get_opcode() const 
{
	return opcode;
}

void Instruction::set_rd(const string &_rd)
{
	string rd_binary = to_binary_string(5, _rd);

	copy(rd_binary.begin(), rd_binary.end(), rd);
}

const char *Instruction::get_rd() const
{
	return rd;
}

char * const Instruction::get_rd()
{
	return rd;
}

void Instruction::set_func3(const string &_func3)
{
	copy(_func3.begin(), _func3.end(), func3);
}

void Instruction::set_rs1(const string &_rs1)
{
	string rd_binary = to_binary_string(5, _rs1);

	copy(rd_binary.begin(), rd_binary.end(), rs1);
}

char * const Instruction::get_rs1()
{
	return rs1;
}

const char *Instruction::get_rs1() const
{
	return rs1;
}

char * const Instruction::get_func3()
{
	return func3;
}

const char *Instruction::get_func3() const
{
	return func3;
}

void Instruction::set_rs2(const string &_rs2)
{
	string rd_binary = to_binary_string(5, _rs2);

	copy(rd_binary.begin(), rd_binary.end(), rs2);
}

char * const Instruction::get_rs2()
{
	return rs2;
}

const char *Instruction::get_rs2() const
{
	return rs2;
}

void Instruction::set_func2(const string &_func2)
{
	copy(_func2.begin(), _func2.end(), func2);
}

char * const Instruction::get_func2()
{
	return func2;
}

const char *Instruction::get_func2() const
{
	return func2;
}

void Instruction::set_func5(const string &_func5)
{
	copy(_func5.begin(), _func5.end(), func5);
}

char * const Instruction::get_func5()
{
	return func5;
}

const char *Instruction::get_func5() const
{
	return func5;
}

void Instruction::print() const
{
	cout << get_func5()  << get_func2() << get_rs2()
		 << get_rs1()    << get_func3() << get_rd()
		 << get_opcode() << '\n';
}