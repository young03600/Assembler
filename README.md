# RISC-V Assembler for R32I
course practice

## How does your file pass: 
### using Command line argument to pass path of your input file 
    Assembler to be run like this
    Assembler *assembler = new Assembler("path of your input file");
## How the Assembler works?
*   A base class Instruction pointer initialize when the Assembler is running
*   After the instruction type was determined, the Instruction pointer points the type it should be\
    *   *Any error or not supported type would be detected at the point when the program is running on that type*

Example Input:
    
        add x2,x2,x23       
        addi x24,x24,2
        bne x24,x23,L2
        sw x27,0(x10)
        beq x0,x0,L1
    L2: sw x1,0(x2)
    L1: addi x24,x24,1

Example Output: (followd the instruction order above)

      | f5  |f2| rs2 | rs1 |f3 | rd  | opcode |
  
         00000 00 10111 00010 000 00010  0110011

      | simm[11:0] | rs1 |f3 | rd  | opcode |
 
       000000000010 11000 000 11000  0010011

      | imm[12|10:5] | rs2 | rs1 |f3 | simm[4:1|11] | opcode |

            0000000   10111 11000 001      01100     1100011

      | simm[11:5] | rs2 | rs1 |f3 | simm[4:0] | opcode |

         0000000   11011 01010 010    00000     0100011

      | imm[12|10:5] | rs2 | rs1 |f3 | simm[4:1|11] | opcode |

         0000000   00000 00000 000      01000     1100011

      | simm[11:5] | rs2 | rs1 |f3 | simm[4:0] | opcode |

          0000000   00001 00010 010    00000     0100011

      | simm[11:0] | rs1 |f3 | rd  | opcode |

      000000000001 11000 000 11000  0010011
  
  
