#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <array>
#include <bitset>
#include <cmath>
#include <iostream>
using namespace std;

class Instruction
{
	//friend virtual ostream &operator<<(ostream &out, const Instruction &instruction) = 0;
public:
	Instruction();
	Instruction(const string &);
	virtual ~Instruction();
	
	void set_opcode(const string &);
	virtual void set_rd(const string &);
	virtual void set_func3(const string &);
	virtual void set_rs1(const string &);
	virtual void set_rs2(const string &);
	virtual void set_func2(const string &);
	virtual void set_func5(const string &);
	
	virtual void transfer() = 0;
	virtual void print() const = 0;
private:

	// numBits + 1 for '\0'
	char opcode[8];
	char rd[6];
	char func3[4];
	char rs1[6];
	char rs2[6];
	char func2[3];
	char func5[6];

protected:
	string to_binary_string(const int, const string &);
	//void split_bits(const string &, int, int);
	
    //char * const get_opcode();
	const char *get_opcode() const;
	
	char * const get_rd();
	const char *get_rd() const;

	char * const get_rs1();
	const char *get_rs1() const;

	
	char * const get_func3();
	const char *get_func3() const;

	char * const get_rs2();
	const char *get_rs2() const;

	char * const get_func2();
	const char *get_func2() const;

	char * const get_func5();
	const char *get_func5() const;
};

#endif  // !INSTRUCTION_H