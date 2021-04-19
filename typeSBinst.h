#ifndef _TYPESBINST_
#define _TYPESBINST_

#include "Instruction.h"
#include <string>
#include <iomanip>
using namespace std;

class TypeSBinst :
	public Instruction
{
public:
	TypeSBinst();
	TypeSBinst(const string &, const string &, const string &, const string &);
	~TypeSBinst();

	virtual void transfer() override;
	virtual void print() const override;
private:

	virtual void set_rd(const string &) override;
	virtual void set_func2(const string &) override;
	virtual void set_func5(const string &) override;

	string temp_command;
	string temp_rs1;
	string temp_rs2;
	string temp_offset;
};

#endif // !_TYPESBINST_