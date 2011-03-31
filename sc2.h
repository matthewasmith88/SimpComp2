/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
 H
 H  scsim.h
 H  
 H
 H  Created by Tyler Crocker, Michael Palmer,
 H  Stanislava Auchynnikava on 1/20/11.
 H  Date completed: 1/25/11
 H
 H  Description: A header file for the test-driver.
 H
 HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/

#include <stdio.h>
#include <string.h>

/*-----------------------------------------------------------------------------
 -  Prototypes for test driver helper methods.
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/
int get_input(int min, int max, char * string, char * errorMessage);
void printErrMsg(int error_code);

/*#############################################################################
 #  Define (General Purpose)
 ############################################################################*/

#define uchar unsigned char
#define ushort unsigned short
#define byte unsigned char
#define word unsigned short
#define LO_BYTE_BIT_MASK  0x00FF
#define HI_BYTE_BIT_MASK  0xFF00
#define WORD_BIT_MASK     0xFFFF
#define BYTE_SIZE         0x8
#define WORD_SIZE         0x10
#define SIGN_BIT_MASK     0x8000
#define HIGHEST_BYTE_VAL  0x7F
#define LOWEST_BYTE_VAL   0xFFFFFF80
#define LOWEST_WORD_VAL   0xFFFF8000
#define NULL_BYTE         0x00
#define NULL_WORD         0x0000
#define HEX_30            0x30
#define BUFFER_SIZE       80
#define HEXADECIMAL       16


/*#############################################################################
 #  Define for Operations
 ############################################################################*/

/* Memory Operations */
#define LDI       0x01
#define LADR      0x17

#define LDB_MOVB	0x02
#define LDW_MOVW	0x03

#define LDB_BR    0x04
#define LDW_BR    0x05

#define STB       0x06
#define STW       0x07

#define STB_BR    0x1A
#define STW_BR    0x1B

/* ALU Imm Operations */
#define ADDI      0x08
#define SUBI      0x09

/* ALU 2-opnd Operations */
#define ADD       0x0A
#define SUB       0x0B
#define MUL       0x0C
#define DIV       0x0D
#define AND       0x0E
#define OR        0x0F
#define XOR       0x10

/* ALU 1-opnd Operations */
#define NEG       0x11
#define NOT       0x12
#define SH        0x1E /* SHARED BETWEEN SHR AND SHL */
#define SHL_ALU   0xF0 /* ALU USE ONLY */
#define SHR_ALU   0xF1 /* ALU USE ONLY */

/* Control Operations */
#define BR        0x13
#define BRcc      0x14

/* IO Operations */
#define IN        0x18
#define OUT       0x19

/* HALT Operation */
#define HALT      0x1F

/* AMOD Values */
#define LDB_AMOD	0x0
#define LDW_AMOD  0x0
#define MOVB_AMOD 0x4
#define MOVW_AMOD 0x5


/*#############################################################################
 #  Define Error Codes
 ############################################################################*/

#define ERR_NO_ERROR                      0
#define ERR_UNDEFINED_ERROR               1
#define ERR_NULL_POINTER_EXCEPTION        2
#define ERR_INVALID_BYTE_DESCRIPTOR       3
#define ERR_INVALID_REGISTER              4
#define ERR_DATA_TYPE_MISMATCH            5
#define ERR_MEMORY_ADDRESS_OUT_OF_BOUNDS  6
#define ERR_INVALID_OPERATION             7
#define ERR_ILLEGAL_ARGUMENT_EXCEPTION    8
#define ERR_INVALID_IO_PORT			9


/******************************************************************************
 *
 *  16 bit Register ADT
 *
 *****************************************************************************/

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the 16 bit Register ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef unsigned short Register;
typedef Register *RegisterPtr;

/*-----------------------------------------------------------------------------
 -  Prototypes for the 16 bit Register ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

RegisterPtr register_initialize(void); /* allocates space and returns pointer */

byte register_getLoByte(RegisterPtr the_reg, int * error);
byte register_getHiByte(RegisterPtr the_reg, int * error);
word register_getRegVal(RegisterPtr the_reg, int * error);

int register_putLoByte(RegisterPtr the_reg, byte data); /* returns error code */
int register_putHiByte(RegisterPtr the_reg, byte data); /* returns error code */
int register_putRegVal(RegisterPtr the_reg, word data); /* returns error code */

/* returns 0 for positive, 1 for negative, 2 and up are error codes */
uchar register_signOf(RegisterPtr the_reg);


/******************************************************************************
 *
 *  Register File ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for Register File ADT
 ############################################################################*/

#define REGISTER_COUNT 16
#define $R0 0x0
#define $R1 0x1
#define $R2 0x2
#define $R3 0x3
#define $R4 0x4
#define $R5 0x5
#define $R6 0x6
#define $R7 0x7
#define $R8 0x8
#define $R9 0x9
#define $RA 0xA
#define $RB 0xB
#define $RC 0xC
#define $RD 0xD
#define $RE 0xE
#define $RF 0xF

#define LO_BYTE   0x0
#define HI_BYTE   0x1
#define FULL_WORD 0x2

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the Register File ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef RegisterPtr RegisterFilePtr; /* pointer to an unsigned short */

/*-----------------------------------------------------------------------------
 -  Prototypes for the Register File ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

RegisterFilePtr registerFile_initialize();

byte registerFile_getByteFrom(RegisterFilePtr reg_file, uchar reg_num,
                              uchar which_byte, int * error);
word registerFile_getRegVal(RegisterFilePtr reg_file, uchar reg_num,
                            int * error);

int registerFile_putByteTo(RegisterFilePtr reg_file, uchar reg_num,
                           uchar which_byte, byte data);
int registerFile_putRegVal(RegisterFilePtr reg_file, uchar reg_num, word data);


/****************************************************************************** 
 *
 *  Memory Module ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for the Memory Module ADT
 ############################################################################*/

#define END_OF_MEMORY   0xFFFF
#define START_OF_MEMORY 0x3000

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the Memory Module ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef uchar *MemoryModulePtr; /* pointer to an unsigned char */

/*-----------------------------------------------------------------------------
 -  Prototypes for the Memory Module ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

MemoryModulePtr memory_initialize();

byte memory_fetchByteFrom(MemoryModulePtr mem_module, ushort address,
                          int * error);
word memory_fetchWordFrom(MemoryModulePtr mem_module, ushort address,
                          int * error);

int memory_storeByteTo(MemoryModulePtr mem_module, ushort address, byte data);
int memory_storeWordTo(MemoryModulePtr mem_module, ushort address, word data);


/****************************************************************************** 
 *
 *  I/O ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for the I/O ADT
 ############################################################################*/

/* Port Addresses of I/O Devices */
#define IO_PORT_KBD 0x1
#define IO_PORT_VID 0x2


/*-----------------------------------------------------------------------------
 -  Prototypes for the Status Word ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/


uchar io_in(uchar port, int *error_code);	/* passes back data */
int io_out(uchar port, uchar data);	/* passes back error code */


/****************************************************************************** 
 *
 *  Status Word ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for the Status Word ADT
 ############################################################################*/

#define SW_BIT_SHIFT    0xC

/* AND TO CLEAR ALL SW FLAGS */
#define FLAG_CLEAR_MASK 0x0FFF

/* OR TO SET A SPECIFIC FLAG */
#define NEG_MASK    0x8000
#define ZERO_MASK   0x4000
#define CARRY_MASK  0x2000
#define OFLOW_MASK  0x1000



/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the Status Word ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef unsigned short SWRegister;
typedef SWRegister *SWRegPtr;


/*-----------------------------------------------------------------------------
 -  Prototypes for the Status Word ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

SWRegPtr sw_initialize();
int sw_destroy(SWRegPtr sw);
int sw_clearFlags(SWRegPtr sw);
int sw_setFlag(SWRegPtr sw, ushort flag_mask);
ushort sw_getFlags(SWRegPtr sw, int * error_code);


/****************************************************************************** 
 *
 *  ALU ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for the ALU ADT
 ############################################################################*/


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the ALU ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef struct alu_str {
  word  inputA;
  word  inputB;
  word  outputR;
  word  secondaryOutputR;
  uchar currentOp;
  SWRegPtr sw;
} AluStr;

typedef AluStr * AluPtr;


/*-----------------------------------------------------------------------------
 -  Prototypes for the ALU ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

AluPtr alu_initialize(SWRegPtr the_sw);
int alu_destroy(AluPtr alu);
int alu_putInputA(AluPtr alu, word value);
int alu_putInputB(AluPtr alu, word value);
int alu_putInputBImm(AluPtr alu, short value);
int alu_putCurrentOp(AluPtr alu, uchar op);
word alu_getOutputR(AluPtr alu, int * error_code);
word alu_getSecondaryOutputR(AluPtr alu, int * error_code);
int alu_performOperation(AluPtr alu);


/****************************************************************************** 
 *
 *  PC ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for the PC ADT
 ############################################################################*/


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the PC ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef Register *PCRegPtr;

/*-----------------------------------------------------------------------------
 -  Prototypes for the PC ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

PCRegPtr pc_initialize();
int pc_incrementPC(PCRegPtr pc);
int pc_set(PCRegPtr pc, ushort newPC);
ushort pc_get(PCRegPtr pc, int * error_code);

/****************************************************************************** 
 *
 *  IR ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for the IR ADT
 ############################################################################*/


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the IR ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef Register *IRRegPtr;

/*-----------------------------------------------------------------------------
 -  Prototypes for the IR ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

IRRegPtr ir_initialize();
int ir_set(IRRegPtr ir, ushort newIR);
ushort ir_get(IRRegPtr ir, int * error_code);

/****************************************************************************** 
 *
 *  Halt Bit ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for the Halt Bit ADT
 ############################################################################*/

#define HALT_ASSERT 0x1
#define HALT_CLEAR  0x0

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the Halt Bit ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef uchar *HaltBitPtr;

/*-----------------------------------------------------------------------------
 -  Prototypes for the Halt Bit ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

HaltBitPtr hb_initialize();
int hb_assert(HaltBitPtr hb);
int hb_clear(HaltBitPtr hb);
uchar hb_get(HaltBitPtr hb, int * error_code);


/****************************************************************************** 
 *
 *  CPU ADT
 *
 *****************************************************************************/

/*#############################################################################
 #  Defines for the CPU ADT
 ############################################################################*/

#define OPCODE_SHIFT_VAL 11
#define OPND_A_SHIFT_VAL 7
#define OPND_B_SHIFT_VAL 3
#define R_SHIFT_VAL      5

#define AMOD_MASK     0x0007
#define IO_PORT_MASK  0x07FF
#define OPND_A_MASK   0x0780
#define OPND_B_MASK   0x0078
#define IMM_OPND_MASK 0x007F
#define R_MASK        0x0060
#define BR_OFSET_MASK 0x001E

#define OP_FLAG_N 0x1
#define OP_FLAG_Z 0x2
#define OP_FLAG_C 0x3
#define OP_FLAG_O 0x4

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $  Typedefs for the Status Word ADT
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef enum inst_type_enum {
  alu_imm_type, alu_1op_type, alu_2op_type, alu_mul_type, alu_div_type,
  unconditional_control_type, conditional_control_type,
  ld_imm_type, ld_effadr_type, ld_byte_type, ld_word_type,
  ld_byte_br_type, ld_word_br_type,
  st_byte_type, st_word_type, st_byte_br_type, st_word_br_type,
  reg_byte_type, reg_word_type,
  io_in_type, io_out_type,
  halt_type,
  invalid_inst_type
} inst_type;

typedef struct cpu_struct {
  RegisterFilePtr regFile;
  SWRegPtr sw;
  AluPtr alu;
  IRRegPtr ir;
  PCRegPtr pc;
  HaltBitPtr hb;
  MemoryModulePtr mem;
} CPUStr;

typedef CPUStr *CPUPtr;


/*-----------------------------------------------------------------------------
 -  Prototypes for the CPU ADT
 -  Descriptions of public functions (all are public)
 ----------------------------------------------------------------------------*/

CPUPtr cpu_initialize();
int cpu_run(CPUPtr cpu);
int cpu_step(CPUPtr cpu);
int cpu_fetch(CPUPtr cpu);
inst_type cpu_decode(CPUPtr cpu, int * error_code);
int cpu_execute(CPUPtr cpu, inst_type instruction_type);
int cpu_reset(CPUPtr cpu);
int cpu_haltSet(CPUPtr cpu, uchar halt_toggle);


/******************************************************************************
 *
 *  Debug Monitor ADT
 *
 *****************************************************************************/
/*#############################################################################
 #  Defines for Debug Monitor ADT
 ############################################################################*/
#define LOADFILE	1
#define RUN			2
#define STEP		3
#define DISPLAYREG	4
#define DISPLAYMEM	5
#define QUIT		6
#define MESSAGE "Select: 1) load file, 2) run, 3) step, 4) display registers, 5) display memory, 6) quit"
#define ERROR "Invalid input!\nTry Again"
#define FILE_ERROR "Invalid file name.\n"
#define SECOND "If second switch is desired, it must be \"-s\"\n"
#define FIRST "First switch must be -p\n"
#define ARGUMENTS "Invalid Arguments\n"
#define LENGTH_OF_LINE 4
#define CR '\r'
#define NEW_LINE '\n'
#define NULL_CHAR '\0'
#define STEP_MESSAGE "Please enter step command: "
#define HALT_MESSAGE "The machine is halted! Cannot step while halted"
#define REGISTER_MESSAGE "Registers\n"
#define MEM_START "Please select the starting memory address in hex (e.g. 0x3000)"
#define MEM_END "Please select the final memory address in hex (e.g. 0xFFFF)"
#define ADDRESS "Invalid address!"
#define FILE_ERR "Invalid File\n"
#define STEP_MENU "STEP\nCommands are:\n1. \' \' (space) = Step\n2. \'r\' = View registers\n3. \'m\' = View memory\n4. \'c\' = Continue until end\n5. \'x\' = Exit step\n"
#define ASCII_NUMBER_OFFSET 48
#define ASCII_LETTER_OFFSET 55
#define HEX_VALUES 16
#define FILENAME_MESSAGE "Please enter the filename: "
#define LOAD_SUCCESS "\nFile loaded.\n"
#define LOAD_FAIL "\nFile not loaded.\n"
#define FINISHED "\nFinished execution of program.\n"
#define SWITCH_LOADFILE "-p"
#define SWITCH_STEP		"-s"
#define OBJ				"obj"
#define SWITCH_ARG_NUM	3
#define START_ADDRESS	0x3000
#define LAST_ADDRESS	0xFFFF
#define LINESIZE		7
#define INPUT_SIZE		20

#define ERR_STRING_SIZE		9
#define ERR_OBJ_FILE_FORMAT	10

/* Member data*/

typedef enum {
	run, step, menu
} startCommand;

static char *message = MESSAGE;

/*-----------------------------------------------------------------------------
 -  Prototypes for the Debug Monitor ADT
 ----------------------------------------------------------------------------*/

int dbm_loadFile(CPUPtr cpu, char *filename);
void dbm_run(CPUPtr cpu);
void dbm_step(CPUPtr cpu);
void dbm_displayReg(CPUPtr cpu);
void dbm_displayMem(CPUPtr cpu);
int dbm_userSelect(CPUPtr cpu);
ushort dbm_convertStringToShort(char *string, int *error);
char *dbm_getFileName();
char *dbm_checkFileName(char * filename);
startCommand dbm_initialize(int argc, char *argv[], CPUPtr cpu);
/*Helper function*/
int dbm_pow(int base, int exp);

