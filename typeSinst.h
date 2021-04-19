#ifndef TYPESINST_H
#define TYPESINST_H

#include "Instruction.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class TypeSinst :
	public Instruction
{
public:
	TypeSinst();
	TypeSinst(const string &, const string &, const string &);
	~TypeSinst();
	
	virtual void transfer() override;
	virtual void print() const override;
private:
	virtual void set_rd(const string &) override;
	virtual void set_func2(const string &) override;
	virtual void set_func5(const string &) override;

	string *temp_command;
	string *temp_rs2;
	string *temp_rs1;
	string *temp_imm;
};

#endif  // !TYPESINST_H

