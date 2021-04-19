#include "Assembler.h"
#include "Instruction.h"
#include "typeRinst.h"
#include "typeIinst.h"
#include "typeSinst.h"
#include "typeUinst.h"
#include "typeSBinst.h"
#include "typeUJinst.h"

char instRtype[][6] = { "add", "sub", "sll", "stl", "sltu", "xor", "srl", "sra", "or", "and" };
char instItype[][6] = { "jalr", "lb", "lh", "lw", "lbu", "lhu", "addi", "slti", "sltiu", "xori", "andi", "slli", "srli", "srai" }; //slli srli srai
char instStype[][3] = { "sb", "sh", "sw" };
char instSBtype[][5] = { "beq", "bne", "blt", "bge", "bltu", "begu" };
char instUtype[][6] = { "lui", "auipc" };
char instUJtype[][4] = { "jal" };

Assembler::Assembler(const string _fileName) 
	: count(0)
{
	fileName = new string();
	fileName->assign(_fileName);
}

Assembler::~Assembler()
{
	delete fileName;
	fileName = nullptr;
}

void Assembler::run() 
{
	read();
	interpret();
}

void Assembler::read() {
	
	
	ifstream ifs(*fileName);
	if (!ifs) {
		cerr << "File not found\n";
		exit(1);
	}
	
	string line;
	while (getline(ifs, line)) {

		for (size_t i = line.find(',', 1); i != line.npos; i = line.find(',', 1))
			line.replace(i, 1, " ");

		track.push_back(line);

		istringstream iss(line);
		string word;
		while (iss >> word) {
			if (word[0] == ' ')
				word.erase(remove(word.begin(), word.end(), ' '), word.end());

			if (word.back() == ':') continue;
			//if(word.find('('))

			inst.push_back(word);
		}
	}
#ifdef _DEBUG
	for (const auto &word : inst)
		cout << word << '\n';
	cout << '\n';
#else
    for (const auto &word : track) cout << word << '\n';
    cout << '\n';
#endif // DEBUG
}

char Assembler::find_type(const string &type)
{
	auto iter_char_6 = find_if(begin(instRtype), end(instRtype), [&](const char *word) { return word == type; });
	if (iter_char_6 != end(instRtype)) return 'R';

	iter_char_6 = find_if(begin(instItype), end(instItype), [&](const char *word) { return word == type; });
	if (iter_char_6 != end(instItype)) return 'I';

	iter_char_6 = find_if(begin(instUtype), end(instUtype), [&](const char *word) { return word == type; });
	if (iter_char_6 != end(instUtype)) return 'U';

	auto iter_char_5 = find_if(begin(instSBtype), end(instSBtype), [&](const char *word) { return word == type; });
	if (iter_char_5 != end(instSBtype)) return 'B';

	auto iter_char_4 = find_if(begin(instUJtype), end(instUJtype), [&](const char *word) { return word == type; });
	if (iter_char_4 != end(instUJtype)) return 'J';

	auto iter_char_3 = find_if(begin(instStype), end(instStype), [&](const char *word) { return word == type; });
	if (iter_char_3 != end(instStype)) return 'S';

	return 'E';   // error
}

int Assembler::lable_offset(const vector<string>::iterator &_first, const vector<string>::iterator &_last, const string &_lable_find)
{
	auto iter = find_if(_first, _last, [&](const auto &_inst) {
		return _inst.find(_lable_find) != string::npos;
	});
	
	if (iter == _last)
		return -4097;

	return _last == track.end() ? int(iter - track.begin() - count) : int((iter - track.begin()) - count);
}

void Assembler::interpret() 
{
	Instruction *instruction = nullptr;
	
	// return J for Type-UJ
	// return B for Type-SB
	while (!inst.empty()) {
		
		int _offset;
		try {
			switch (find_type(inst[0])) {
				case 'R':
					instruction = new TypeRinst(inst[0], inst[1], inst[2], inst[3]);
					inst.erase(inst.begin(), inst.begin() + 4);
					break;
				case 'I':
					if (inst[0] == "jalr" || inst[0] == "lb" || inst[0] == "lh" || inst[0] == "lw" || inst[0] == "lbu" || inst[0] == "lhu") {
						instruction = new TypeIinst(inst[0], inst[1], inst[2]);
						inst.erase(inst.begin(), inst.begin() + 3);
					}
					else {
						instruction = new TypeIinst(inst[0], inst[1], inst[2], inst[3]);
						inst.erase(inst.begin(), inst.begin() + 4);
					}
					break;
				case 'S':
					instruction = new TypeSinst(inst[0], inst[1], inst[2]);
					inst.erase(inst.begin(), inst.begin() + 3);
					break;
				case 'U':
					instruction = new TypeUinst(inst[0], inst[1], inst[2]);
					inst.erase(inst.begin(), inst.begin() + 3);
					break;
				case 'J':
					_offset = lable_offset(track.begin(), track.begin() + count - 1, inst[2] + ":");
					if (_offset == -4097)
						_offset = lable_offset(track.begin() + count + 1, track.end(), inst[2] + ":");
					
					instruction = new TypeUJinst(inst[0], inst[1], to_string(_offset << 2));
					inst.erase(inst.begin(), inst.begin() + 3);
					break;
				case 'B':
					_offset = lable_offset(track.begin(), track.begin() + count - 1, inst[3] + ":");
					if (_offset == -4097)
						_offset = lable_offset(track.begin() + count + 1, track.end(), inst[3] + ":");
					
					instruction = new TypeSBinst(inst[0], inst[1], inst[2], to_string(_offset << 2));
					inst.erase(inst.begin(), inst.begin() + 4);
					break;
				default:
                  throw runtime_error("\n[Error]: Error type was detected. The process is exiting\n");
                  break;
			}
		}	
		catch (exception &e) {
			cerr << e.what();
			exit(1);
		}
		
		instruction->transfer();
		instruction->print();

		delete instruction;

		++count;
	}
	
	instruction = nullptr;
}