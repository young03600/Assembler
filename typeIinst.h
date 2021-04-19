#ifndef TYPEIINST_H
#define TYPEIINST_H

#include "Instruction.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class TypeIinst :
	public Instruction
{
public:
	TypeIinst();

	// for lui and load inst
	TypeIinst(const string &, const string &, const string &); 

	TypeIinst(const string &, const string &, const string &, const string &);
	~TypeIinst();

	virtual void transfer() override;
	virtual void print() const override;
private:	
	virtual void set_rs2(const string &) override;
	virtual void set_func2(const string &) override;
	virtual void set_func5(const string &) override;
	
	string *temp_command;
	string *temp_rd;
	string *temp_rs;
	string *temp_imm;	
};

#endif  // !TYPEIINST_H
