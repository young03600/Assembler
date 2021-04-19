#ifndef __TYPEUJINST_H__
#define __TYPEUJINST_H__

#include "Instruction.h"
#include <string>
#include <iomanip>
using namespace std;

class TypeUJinst :
	public Instruction
{
public:
	TypeUJinst();
	TypeUJinst(const string &, const string &, const string &);
	~TypeUJinst();

	virtual void transfer() override;
	virtual void print() const override;
private:
	virtual void set_rs1(const string &) override;
	virtual void set_rs2(const string &) override;
	virtual void set_func5(const string &) override;

	string *temp_command;
	string *temp_rd;
	string *temp_imm;
};

#endif