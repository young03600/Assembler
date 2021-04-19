#ifndef TYPERINST_H
#define TYPEINST_H

#include "Instruction.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class TypeRinst :
	public Instruction
{
	//friend virtual ostream &operator<<(ostream &out, const TypeRinst &);
public:
	TypeRinst();
	TypeRinst(const string &, const string &, const string &, const string &);
	~TypeRinst();

	virtual void transfer() override;
	virtual void print() const override;
private:
	string *temp_command;
	string *temp_rd;
	string *temp_rs1;
	string *temp_rs2;
};

#endif // !TYPERINST_H