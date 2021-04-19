#ifndef __TYPEUINST_H__
#define __TYPEUINST_H__

#include "Instruction.h"
#include <string>
#include <iomanip>
using namespace std;

class TypeUinst :
	public Instruction
{
public:
	TypeUinst();
	TypeUinst(const string &, const string &, const string &);
	~TypeUinst();

	virtual void transfer() override;
	virtual void print() const override;
private:
	virtual void set_rs2(const string &) override;
	
	string *temp_command;
	string *temp_rd;
	string *temp_imm;
};

#endif
