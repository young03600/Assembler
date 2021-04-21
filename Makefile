# Makefile for windows
all:main clean

main: ALCO_project1.o Assembler.o Instruction.o typeRinst.o typeIinst.o typeSBinst.o typeSinst.o typeUinst.o typeUJinst.o
	@g++ -o Assembler ALCO_project1.o Assembler.o Instruction.o typeRinst.o typeIinst.o typeSBinst.o typeSinst.o typeUinst.o typeUJinst.o

ALCO_project1.o: ALCO_project1.cpp
	@g++ -c ALCO_project1.cpp

Assembler.o: Assembler.cpp
	@g++ -c Assembler.cpp

Instruction.o: Instruction.cpp
	@g++ -c Instruction.cpp

typeRinst.o: typeRinst.cpp
	@g++ -c typeRinst.cpp

typeIinst.o: typeIinst.cpp
	@g++ -c typeIinst.cpp

typeSBinst.o: typeSBinst.cpp
	@g++ -c typeSBinst.cpp

typeSinst.o: typeSinst.cpp
	@g++ -c typeSinst.cpp

typeUinst.o: typeUinst.cpp
	@g++ -c typeUinst.cpp

typeUJinst.o: typeUJinst.cpp
	@g++ -c typeUJinst.cpp

clean:
	@del *.o