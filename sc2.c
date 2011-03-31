/*CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
 C
 C  sc2.c
 C
 C
 C  Created by Tyler Crocker, Michael Palmer,
 C  Stanislava Auchynnikava on 1/20/11.
 C  Date completed: 3/9/11
 C
 C  Description: A test-driver to show that you can successfully transfer data,
 C    both byte and word, to and from registers/main memory.
 C
 CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sc2.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  Register ADT Implementations
 +  Implements the functions for the 16 bit Register ADT.
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: register_initialize
 =  Programmer name:
 =  Final test and approval date: 1-23-11
 =  Synopsis:
 =      Parameters: N/A
 =      Return type: RegisterPtr
 =      Possible error conditions: N/A
 =
 =  Allocates space and returns pointer to the created "object".
 ============================================================================*/
RegisterPtr register_initialize()
{
  RegisterPtr new_reg = (RegisterPtr) malloc(sizeof(Register));
  
  *new_reg = NULL_BYTE;
  
  return new_reg;
}

/*=============================================================================
 =  Comment block for function: register_getLoByte
 =  Programmer name:
 =  Final test and approval date: 1-23-11
 =  Synopsis:
 =      Parameters: RegisterPtr containing the register get from
 =                  int * to store any error codes in
 =      Return type: word
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 =  Errors are assigned to the passed integer pointer.
 ============================================================================*/
byte register_getLoByte(RegisterPtr the_reg, int * error)
{
  if (the_reg != (RegisterPtr) NULL)
  {
    return *the_reg; /* will return the lowest byte */
  }
  else
  {
    *error = ERR_NULL_POINTER_EXCEPTION;
  }
  
  return NULL_BYTE;
}

/*=============================================================================
 =  Comment block for function: register_getHiByte
 =  Programmer name:
 =  Final test and approval date: 1-23-11
 =  Synopsis:
 =      Parameters: RegisterPtr containing the register get from
 =                  int * to store any error codes in
 =      Return type: word
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 =  Errors are assigned to the passed integer pointer.
 ============================================================================*/
byte register_getHiByte(RegisterPtr the_reg, int * error)
{
  if (the_reg != (RegisterPtr) NULL)
  {
    *error = ERR_NO_ERROR;
    return *the_reg >> BYTE_SIZE; /* will return the lowest byte */
  }
  else
  {
    *error = ERR_NULL_POINTER_EXCEPTION;
  }
  
  return NULL_BYTE;
}

/*=============================================================================
 =  Comment block for function: register_getRegVal
 =  Programmer name:
 =  Final test and approval date: 1-23-11
 =  Synopsis:
 =      Parameters: RegisterPtr containing the register get from
 =                  int * to store any error codes in
 =      Return type: word
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 =  Errors are assigned to the passed integer pointer.
 ============================================================================*/
word register_getRegVal(RegisterPtr the_reg, int * error)
{
  if (the_reg != (RegisterPtr) NULL)
  {
    *error = ERR_NO_ERROR;
    
    return *the_reg;
  }
  else
  {
    *error = ERR_NULL_POINTER_EXCEPTION;
  }
  
  return NULL_WORD;
}

/*=============================================================================
 =  Comment block for function: register_putLoByte
 =  Programmer name:
 =  Final test and approval date: 1-23-11
 =  Synopsis:
 =      Parameters: RegisterPtr containing the register to put to
 =                  byte the data to be written to the register (0-255)
 =      Return type: int containing the error code
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 ============================================================================*/
int register_putLoByte(RegisterPtr the_reg, byte data)
{
  /* not checking for NULL for "data" since you might want to pass NULL */
  if (the_reg != (RegisterPtr) NULL)
  {
    *the_reg &= HI_BYTE_BIT_MASK; /* clears low byte */
    *the_reg |= data;
    
    return ERR_NO_ERROR;
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}

/*=============================================================================
 =  Comment block for function: register_putHiByte
 =  Programmer name:
 =  Final test and approval date: 1-23-11
 =  Synopsis:
 =      Parameters: RegisterPtr containing the register to put to
 =                  byte the data to be written to the register (0-255)
 =      Return type: int containing the error code
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 ============================================================================*/
int register_putHiByte(RegisterPtr the_reg, byte data)
{
  /* not checking for NULL for "data" since you might want to pass NULL */
  if (the_reg != (RegisterPtr) NULL)
  {
    *the_reg &= LO_BYTE_BIT_MASK; /* clears high byte */
    *the_reg |= data << BYTE_SIZE;
    
    return ERR_NO_ERROR;
  }
  return ERR_NULL_POINTER_EXCEPTION;
}

/*=============================================================================
 =  Comment block for function: register_putRegVal
 =  Programmer name:
 =  Final test and approval date: 1-23-11
 =  Synopsis:
 =      Parameters: RegisterPtr containing the register to put to
 =                  byte the data to be written to the register (0-65535)
 =      Return type: int containing the error code
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 ============================================================================*/
int register_putRegVal(RegisterPtr the_reg, word data)
{
  /* not checking for NULL for "data" since you might want to pass NULL */
  if (the_reg != (RegisterPtr) NULL)
  {
    *the_reg = data;
    return ERR_NO_ERROR;
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}

/*=============================================================================
 =  Comment block for function: register_signOf
 =  Programmer name:
 =  Final test and approval date: 1-23-11
 =  Synopsis:
 =      Parameters: RegisterPtr containing the register get the sign of
 =      Return type: uchar containing the sign bit
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 =  Returns 0 for negative, 1 for positive, 2 and up are error codes
 ============================================================================*/
uchar register_signOf(RegisterPtr thePtr)
{
  if (thePtr != (RegisterPtr) NULL)
  {
    return (uchar) (*thePtr >> 15);
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  Register File ADT Implementations
 +  Brief description of operations
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: registerFile_initialize
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: N/A
 =      Return type: RegisterFilePtr
 =      Possible error conditions: N/A
 =
 ============================================================================*/
RegisterFilePtr registerFile_initialize()
{
  RegisterFilePtr reg_file = (RegisterFilePtr) malloc(sizeof(Register) *
                                                      REGISTER_COUNT);
  /* Use the defined register names like this: reg_file[$RX] to refer to a
   register in the register file */
  
  int i = 0;
  
  for (i = 0; i < REGISTER_COUNT; i++)
  {
    reg_file[i] = NULL_WORD;
  }
  
  return reg_file;
}


/*=============================================================================
 =  Comment block for function: registerFile_getByteFrom
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: RegisterFilePtr the register file to work with
 =                  uchar the register to work with (0-15)
 =                  uchar 0 or 1 stating to work with low or high byte (0-1)
 =                  int * to store any error codes in
 =      Return type: byte
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 =  Errors are assigned to the passed integer pointer.
 ============================================================================*/
byte registerFile_getByteFrom(RegisterFilePtr reg_file, uchar reg_num,
                              uchar which_byte, int * error)
{
  if (reg_file != (RegisterFilePtr) NULL)
  {
    switch (which_byte) {
      case HI_BYTE:
        return register_getHiByte(&reg_file[reg_num], error);
        break;
      case LO_BYTE:
        return register_getLoByte(&reg_file[reg_num], error);
        break;
      default:
        *error = ERR_INVALID_BYTE_DESCRIPTOR;
        return NULL_BYTE;
        break;
    }
  }
  
  *error = ERR_NULL_POINTER_EXCEPTION;
  
  return NULL_BYTE;
}

/*=============================================================================
 =  Comment block for function: registerFile_getRegVal
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: RegisterFilePtr the register file to work with
 =                  uchar the register to work with (0-15)
 =                  int * to store any error codes in
 =      Return type: word
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 =  Errors are assigned to the passed integer pointer.
 ============================================================================*/
word registerFile_getRegVal(RegisterFilePtr reg_file, uchar reg_num,
                            int * error)
{
  if (reg_file != (RegisterFilePtr) NULL)
  {
    return register_getRegVal(&reg_file[reg_num], error);
  }
  
  *error = ERR_NULL_POINTER_EXCEPTION;
  
  return NULL_WORD;
}

/*=============================================================================
 =  Comment block for function: registerFile_putByteTo
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: RegisterFilePtr the register file to work with
 =                  uchar the register to work with (0-15)
 =                  uchar 0 or 1 stating to work with low or high byte (0-1)
 =                  byte the data to be written (0-255)
 =      Return type: int containing the error code
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 ============================================================================*/
int registerFile_putByteTo(RegisterFilePtr reg_file, uchar reg_num,
                           uchar which_byte, byte data)
{
  if (reg_file != (RegisterFilePtr) NULL)
  {
    switch (which_byte) {
      case HI_BYTE:
        return register_putHiByte(&reg_file[reg_num], data);
        break;
      case LO_BYTE:
        return register_putLoByte(&reg_file[reg_num], data);
        break;
      default:
        return ERR_INVALID_BYTE_DESCRIPTOR;
        break;
    }
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}

/*=============================================================================
 =  Comment block for function: registerFile_putRegVal
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: RegisterFilePtr the register file to work with
 =                  uchar the register to work with (0-15)
 =                  word the data to be written (0-65535)
 =      Return type: int containing the error code
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 ============================================================================*/
int registerFile_putRegVal(RegisterFilePtr reg_file, uchar reg_num, word data)
{
  if (reg_file != (RegisterFilePtr) NULL)
  {
    return register_putRegVal(&reg_file[reg_num], data);
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  Memory Module ADT Implementations
 +  Brief description of operations
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: memory_initialize
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: N/A
 =      Return type: MemoryModulePtr
 =      Possible error conditions: N/A
 =
 ============================================================================*/
MemoryModulePtr memory_initialize()
{
  MemoryModulePtr new_memModule = (MemoryModulePtr) malloc(sizeof(uchar) *
                                                           END_OF_MEMORY);
  return new_memModule;
}

/*=============================================================================
 =  Comment block for function: memory_fetchByteFrom
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: MemoryModulePtr the memory module to work with
 =                  ushort memory address to fetch from (0x3000-0xFFFF)
 =                  int *  to store any error codes in
 =      Return type: byte
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 =  Errors are assigned to the passed integer pointer.
 ============================================================================*/
byte memory_fetchByteFrom(MemoryModulePtr mem_module, ushort address,
                          int * error)
{
  if (mem_module != (MemoryModulePtr) NULL)
  {
    if (address >= START_OF_MEMORY)
    {
      return mem_module[address];
    }
    else
    {
      *error = ERR_MEMORY_ADDRESS_OUT_OF_BOUNDS;
      
      return NULL_BYTE;
    }
  }
  
  *error = ERR_NULL_POINTER_EXCEPTION;
  
  return NULL_BYTE;
}

/*=============================================================================
 =  Comment block for function: memory_fetchWordFrom
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: MemoryModulePtr the memory module to work with
 =                  ushort memory address to fetch from (0x3000-0xFFFF)
 =                  int * to store any error codes in
 =      Return type: word
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 =  Errors are assigned to the passed integer pointer.
 ============================================================================*/
word memory_fetchWordFrom(MemoryModulePtr mem_module, ushort address,
                          int * error)
{
  if (mem_module != (MemoryModulePtr) NULL)
  {
    if (address >= START_OF_MEMORY && address < END_OF_MEMORY - 1)
    {
      word data = mem_module[address] << BYTE_SIZE;
	  data |= mem_module[address + 1];
      return data;
    }
    else
    {
      *error = ERR_MEMORY_ADDRESS_OUT_OF_BOUNDS;
      
      return NULL_WORD;
    }
  }
  
  *error = ERR_NULL_POINTER_EXCEPTION;
  
  return NULL_WORD;
}

/*=============================================================================
 =  Comment block for function: memory_storeByteTo
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: MemoryModulePtr the memory module to work with
 =                  ushort memory address to store to (0x3000-0xFFFF)
 =                  byte the data to be stored (0-255)
 =      Return type: int containing the error code
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 ============================================================================*/
int memory_storeByteTo(MemoryModulePtr mem_module, ushort address, byte data)
{
  if (mem_module != (MemoryModulePtr) NULL)
  {
    if (address >= START_OF_MEMORY && address < END_OF_MEMORY - 1)
    {
      mem_module[address] = data;
      
      return ERR_NO_ERROR;
    }
    else
    {
      return ERR_MEMORY_ADDRESS_OUT_OF_BOUNDS;
    }
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}

/*=============================================================================
 =  Comment block for function: memory_storeWordTo
 =  Programmer name:
 =  Final test and approval date: 1-24-11
 =  Synopsis:
 =      Parameters: MemoryModulePtr the memory module to work with
 =                  ushort memory address to store to (0x3000-0xFFFF)
 =                  word the data to be stored (0-65535)
 =      Return type: int containing the error code
 =      Possible error conditions: NO ERROR, NULL POINTER EXCEPTION
 =
 ============================================================================*/
int memory_storeWordTo(MemoryModulePtr mem_module, ushort address, word data)
{
  if (mem_module != (MemoryModulePtr) NULL)
  {
    if (address >= START_OF_MEMORY && address < END_OF_MEMORY - 1)
    {
      mem_module[address] = data >> BYTE_SIZE;
      mem_module[address + 1] = data;
      
      return ERR_NO_ERROR;
    }
    else
    {
      return ERR_MEMORY_ADDRESS_OUT_OF_BOUNDS;
    }
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  ALU ADT Implementations
 +  Brief description of operations
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: sw_initialize
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: n/a
 =      Return type: SWRegPtr for a newly malloced SWRegister
 =
 =  Initializes a Status Word Register.
 ============================================================================*/
SWRegPtr sw_initialize()
{
  SWRegPtr sw = (SWRegPtr) malloc(sizeof(SWRegister));
  
  *sw = NULL_WORD;
  
  return sw;
}

/*=============================================================================
 =  Comment block for function: sw_destroy
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: SWRegPtr for the SWRegister to be released from memory
 =      Return type: int containing any error codes
 =
 =  Releases the passed SWRegister from memory
 ============================================================================*/
int sw_destroy(SWRegPtr sw)
{
  if (sw != (SWRegPtr) NULL)
  {
    free(sw);
    return ERR_NO_ERROR;
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}

/*=============================================================================
 =  Comment block for function: sw_clearFlags
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: SWRegPtr for the SWRegister to be operated on
 =      Return type: int containing any error codes
 =
 =  Clears the contents of the passed SWRegister.
 ============================================================================*/
int sw_clearFlags(SWRegPtr sw)
{
  if (sw != (SWRegPtr) NULL)
  {
    *sw &= FLAG_CLEAR_MASK;
    return ERR_NO_ERROR;
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}

/*=============================================================================
 =  Comment block for function: sw_setFlag
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: SWRegPtr for the SWRegister to be operated on
 =                  ushort containing the mask value to set a flag
 =      Return type: int containing any error codes.
 =
 =  Sets the passed flag in the passed SWRegister. (Only the predefined
 =    constants should be used with this method.)
 ============================================================================*/
int sw_setFlag(SWRegPtr sw, ushort flag_mask)
{
  if (sw != (SWRegPtr) NULL)
  {
    *sw |= flag_mask;
    return ERR_NO_ERROR;
  }
  
  return ERR_NULL_POINTER_EXCEPTION;
}

/*=============================================================================
 =  Comment block for function: sw_getFlags
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: SWRegPtr for the SWRegister to be operated on
 =      Return type: ushort containing the SWRegister's flags
 =
 =  Returns the value of the passed SWRegister.
 ============================================================================*/
ushort sw_getFlags(SWRegPtr sw, int * error_code)
{
  if (sw != (SWRegPtr) NULL)
  {
    *error_code = ERR_NO_ERROR;
    return *sw;
  }
  
  *error_code = ERR_NULL_POINTER_EXCEPTION;
  return NULL_BYTE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  PC ADT Implementations
 +  Brief description of operations
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: pc_initialize
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: N/A
 =      Return type: PCRegPtr for the newly malloced PC Register
 =
 =  Initializes a PC Register.
 ============================================================================*/
PCRegPtr pc_initialize()
{
  PCRegPtr pc = (PCRegPtr) malloc(sizeof(Register));
  
  *pc = NULL_WORD;
  
  return pc;
}

/*=============================================================================
 =  Comment block for function: pc_incrementPC
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: PCRegPtr to be incremented
 =      Return type: int containing an error code
 =
 =  Takes in a PCRegPtr, increments it, and then returns and error codes.
 ============================================================================*/
int pc_incrementPC(PCRegPtr pc)
{
  if (pc != (PCRegPtr) NULL)
  {
    *pc += 1;
    
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: pc_set
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: PCRegPtr to be set
 =                  ushort containing the new value to set the PC to
 =      Return type: int containing an error code
 =
 =  Sets the PC value.
 ============================================================================*/
int pc_set(PCRegPtr pc, ushort newPC)
{
  if (pc != (PCRegPtr) NULL)
  {
    *pc = newPC;
    
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: pc_get
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: PCRegPtr containing the PC to be returned
 =                  int* containing a pointer to an error holder
 =      Return type: ushort containing the contents of the PC
 =
 =  Returns the value of the passed PC.
 ============================================================================*/
ushort pc_get(PCRegPtr pc, int * error_code)
{
  if (pc != (PCRegPtr) NULL)
  {
    *error_code = ERR_NO_ERROR;
    
    return *pc;
  }
  else
  {
    *error_code = ERR_NULL_POINTER_EXCEPTION;
    
    return NULL_WORD;
  }
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  IR ADT Implementations
 +  Brief description of operations
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: ir_initialize
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: N/A
 =      Return type: IRRegPtr for the newly malloced IR Register
 =
 =  Initializes a IR Register.
 ============================================================================*/
IRRegPtr ir_initialize()
{
  IRRegPtr ir = (IRRegPtr) malloc(sizeof(Register));
  
  *ir = NULL_WORD;
  
  return ir;
}


/*=============================================================================
 =  Comment block for function: ir_set
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: IRRegPtr to be set
 =                  ushort containing the new value to set the IR to
 =      Return type: int containing an error code
 =
 =  Sets the IR value.
 ============================================================================*/
int ir_set(IRRegPtr ir, ushort newIR)
{
  if (ir != (IRRegPtr) NULL)
  {
    *ir = newIR;
    
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: ir_get
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: IRRegPtr containing the IR to be returned
 =                  int* containing a pointer to an error holder
 =      Return type: ushort containing the contents of the IR
 =
 =  Returns the value of the passed IR.
 ============================================================================*/
ushort ir_get(IRRegPtr ir, int * error_code)
{
  if (ir != (IRRegPtr) NULL)
  {
    *error_code = ERR_NO_ERROR;
    
    return *ir;
  }
  else
  {
    *error_code = ERR_NULL_POINTER_EXCEPTION;
    
    return NULL_WORD;
  }
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  IR ADT Implementations
 +  Brief description of operations
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: hb_initialize
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: N/A
 =      Return type: HaltBitPtr for the newly malloced HB
 =
 =  Initializes a HaltBit.
 ============================================================================*/
HaltBitPtr hb_initialize()
{
  HaltBitPtr hb = (HaltBitPtr) malloc(sizeof(ushort));
  
  *hb = NULL_BYTE;
  
  return hb;
}

/*=============================================================================
 =  Comment block for function: hb_assert
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: HaltBitPtr to be asserted
 =      Return type: int containing an error code
 =
 =  Asserts the passed HaltBit.
 ============================================================================*/
int hb_assert(HaltBitPtr hb)
{
  if (hb != (HaltBitPtr) NULL)
  {
    *hb = HALT_ASSERT;
    
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: hb_clear
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: HaltBitPtr to be set
 =      Return type: int containing an error code
 =
 =  Clears the passed HaltBit.
 ============================================================================*/
int hb_clear(HaltBitPtr hb)
{
  if (hb != (HaltBitPtr) NULL)
  {
    *hb = HALT_CLEAR;
    
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: hb_get
 =  Programmer name:
 =  Final test and approval date: 2-22-11
 =  Synopsis:
 =      Parameters: HaltBitPtr containing the HaltBit to be returned
 =                  int* containing a pointer to an error holder
 =      Return type: uchar containing the contents of the HaltBit
 =
 =  Returns the value of the passed HaltBit.
 ============================================================================*/
uchar hb_get(HaltBitPtr hb, int * error_code)
{
  if (hb != (HaltBitPtr) NULL)
  {
    *error_code = ERR_NO_ERROR;
    
    return *hb;
  }
  else
  {
    *error_code = ERR_NULL_POINTER_EXCEPTION;
    
    return NULL_WORD;
  }
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  ALU ADT Implementations
 +  Brief description of operations
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: alu_initialize
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: SWRegPtr for the SWRegister to be used with the ALU
 =      Return type: AluPtr for the newly malloced ALU
 =
 =  Initializes an ALU, setting all of its values to NULL, and assigning the
 =    passed SWRegister.
 ============================================================================*/
AluPtr alu_initialize(SWRegPtr the_sw)
{
  AluPtr alu = (AluPtr) malloc(sizeof(AluStr));
  
  alu->inputA = NULL_WORD;
  alu->inputB = NULL_WORD;
  alu->outputR = NULL_WORD;
  alu->secondaryOutputR = NULL_WORD;
  alu->currentOp = NULL_BYTE;
  alu->sw = the_sw;
  return alu;
}

/*=============================================================================
 =  Comment block for function: alu_destroy
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: AluPtr for the ALU to be operated on
 =      Return type: int containing any error codes
 =
 =  Releases any memory alloted to the passed ALU. (Note: this won't free
 =     the SWRegister assigned to the ALU.)
 ============================================================================*/
int alu_destroy(AluPtr alu)
{
  if (alu != (AluPtr) NULL)
  {
    free(alu);
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: alu_putInputA
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: AluPtr for the ALU to be operated on
 =                  word containing the value to be set to inputA
 =      Return type: int containing any error codes
 =
 =  Assigns the passed value to the passed ALU's InputA field.
 ============================================================================*/
int alu_putInputA(AluPtr alu, word value)
{
  if (alu != (AluPtr) NULL)
  {
    alu->inputA = value;
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: alu_putInputB
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: AluPtr for the ALU to be operated on
 =                  word containing the value to be set to inputB
 =      Return type: int containing any error codes
 =
 =  Assigns the passed value to the passed ALU's InputB field.
 ============================================================================*/
int alu_putInputB(AluPtr alu, word value)
{
  if (alu != (AluPtr) NULL)
  {
    alu->inputB = value;
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: alu_putInputBImm
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: AluPtr for the ALU to be operated on
 =                  short containing the value to be set to inputB
 =      Return type: int containing any error codes
 =
 =  Assigns the passed value to the passed ALU's InputB field.
 ============================================================================*/
int alu_putInputBImm(AluPtr alu, short value)
{
  if (alu != (AluPtr) NULL)
  {
    alu->inputB = value;
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: alu_getOutputR
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: AluPtr for the ALU to be operated on
 =                  int * for any error codes
 =      Return type: void
 =
 =  Returns the passed ALU's OutputR field.
 ============================================================================*/
word alu_getOutputR(AluPtr alu, int * error_code)
{
  if (alu != (AluPtr) NULL)
  {
    *error_code = ERR_NO_ERROR;
    return alu->outputR;
  }
  else
  {
    *error_code = ERR_NULL_POINTER_EXCEPTION;
    return NULL_WORD;
  }
}

/*=============================================================================
 =  Comment block for function: alu_getSecondaryOutputR
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: AluPtr for the ALU to be operated on
 =                  int * for any error codes
 =      Return type: void
 =
 =  Returns the passed ALU's SecondaryOutputR field, which is used in Division
 =    to hold the remainder, and in Multiplication to hold the low order
 =    portion of the answer.
 ============================================================================*/
word alu_getSecondaryOutputR(AluPtr alu, int * error_code)
{
  if (alu != (AluPtr) NULL)
  {
    *error_code = ERR_NO_ERROR;
    return alu->secondaryOutputR;
  }
  else
  {
    *error_code = ERR_NULL_POINTER_EXCEPTION;
    return NULL_WORD;
  }
}

/*=============================================================================
 =  Comment block for function: alu_putCurrentOp
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: AluPtr for the ALU to be operated on
 =                  uchar containing the opcode to be assigned
 =      Return type: int containing any error codes
 =
 =  Assigns the operation to be used the next time alu_performOperation is
 =     called.
 ============================================================================*/
int alu_putCurrentOp(AluPtr alu, uchar op)
{
  if (alu != (AluPtr) NULL)
  {
    alu->currentOp = op;
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*=============================================================================
 =  Comment block for function: alu_performOperation
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: AluPtr for the ALU to be operated on
 =      Return type: int containing any error codes
 =
 =  Performs the operation that is currently assigned to the passed ALU on the
 =    passed ALU's two Input fields, also sets any flags in the SWRegister
 =    assigned to the passed ALU.
 ============================================================================*/
int alu_performOperation(AluPtr alu)
{
  if (alu != (AluPtr) NULL)
  {
    short val_a = alu->inputA;
    short val_b = alu->inputB;
    int result = 0;
    
    /* CLEAR FLAGS */
    sw_clearFlags(alu->sw);
    
    switch (alu->currentOp)
    {
      case ADD:
      case ADDI:
        result = val_a + val_b;
        alu->outputR = result;
        
        if (((result >> WORD_SIZE) > 0) || (val_a - val_b == 0))
        {
          sw_setFlag(alu->sw, CARRY_MASK);
        }
        break;
        
      case SUB:
      case SUBI:
        result = val_a - val_b;
        alu->outputR = result;
        
        if (result >= 0)
        {
          sw_setFlag(alu->sw, CARRY_MASK);
        }
        break;
        
      case MUL:
        result = val_a * val_b;
        alu->outputR = result >> WORD_SIZE;
        alu->secondaryOutputR = result;
        break;
        
      case DIV:
        result = val_a / val_b;
        alu->outputR = result;
        alu->secondaryOutputR = val_a % val_b;
        break;
        
      case NEG:
        result = (~val_a) + 1;
        alu->outputR = result;
        break;
        
      case NOT:
        result = ~val_a;
        alu->outputR = result;
        break;
        
      case AND:
        result = val_a & val_b;
        alu->outputR = result;
        break;
        
      case OR:
        result = val_a | val_b;
        alu->outputR = result;
        break;
        
      case XOR:
        result = val_a ^ val_b;
        alu->outputR = result;
        break;
        
      case SHR_ALU:
        result = (val_b >> 1);
        alu->outputR = result;
        break;
        
      case SHL_ALU:
        result = (val_b << 1);
        alu->outputR = result;
        
        if ((result >> WORD_SIZE) > 0)
        {
          sw_setFlag(alu->sw, CARRY_MASK);
        }
        break;
        
      default:
        return ERR_INVALID_OPERATION;
        break;
    }
    
    /* NEGATIVE */
    if (((short) alu->outputR) < 0)
    {
      sw_setFlag(alu->sw, NEG_MASK);
    }
    
    /* ZERO */
    if (((short) alu->outputR) == 0)
    {
      sw_setFlag(alu->sw, ZERO_MASK);
    }
    
    /* OVERFLOW */
    if (alu->currentOp <= SUB)
    {
      if (((val_a & SIGN_BIT_MASK) & (val_b & SIGN_BIT_MASK)) ^
          (result & SIGN_BIT_MASK))
      {
        sw_setFlag(alu->sw, OFLOW_MASK);
      }
    }
    
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 +  CPU ADT Implementations
 +  Brief description of operations
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=============================================================================
 =  Comment block for function: cpu_initialize
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: N/A
 =      Return type: CPUPtr that is newly malloced
 =
 =  Initializes a CPU and all of its components.
 ============================================================================*/
CPUPtr cpu_initialize()
{
  CPUPtr cpu = (CPUPtr) malloc(sizeof(CPUStr));
  
  cpu->regFile = registerFile_initialize();
  cpu->sw = sw_initialize();;
  cpu->alu = alu_initialize(cpu->sw);
  cpu->ir = ir_initialize();
  cpu->pc = pc_initialize();
  cpu->hb = hb_initialize();
  cpu->mem = memory_initialize();
  
  pc_set(cpu->pc, 0x3000);
  
  return cpu;
}

/*=============================================================================
 =  Comment block for function: cpu_run
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: CPUPtr to the CPU to be run
 =      Return type: int containing any error codes
 =
 =  Calls the cpu_step() in a loop while the HaltBit is clear.
 ============================================================================*/
int cpu_run(CPUPtr cpu)
{
  int error_code = ERR_NO_ERROR;
  uchar hb_value = hb_get(cpu->hb, &error_code);
  while (hb_value == HALT_CLEAR && error_code == ERR_NO_ERROR)
  {
    error_code = cpu_step(cpu);
    if (error_code == ERR_NO_ERROR)
    {
      hb_value = hb_get(cpu->hb, &error_code);
    }
  }
  return error_code;
}

/*=============================================================================
 =  Comment block for function: cpu_step
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: CPUPtr to the CPU to perform a cycle on
 =      Return type: int containing any error codes
 =
 =  Performs one CPU cycle on the passed CPU.
 ============================================================================*/
int cpu_step(CPUPtr cpu)
{
  int error_code = ERR_NO_ERROR;
  inst_type instruction_type = invalid_inst_type;
  error_code = cpu_fetch(cpu);
  
  if (error_code == ERR_NO_ERROR)
  {
    instruction_type = cpu_decode(cpu, &error_code);
    
    if (error_code == ERR_NO_ERROR)
    {
      error_code = cpu_execute(cpu, instruction_type);
    }
  }
  
  if (error_code != ERR_NO_ERROR)
  {
    hb_assert(cpu->hb);
  }
  
  return error_code;
}

/*=============================================================================
 =  Comment block for function: cpu_fetch
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: CPUPtr to the CPU to fetch an operation for
 =      Return type: int containing any error codes
 =
 =  Fetches the operation from memory in the passed CPU's PC, and stores the
 =    instruction in its IR.
 ============================================================================*/
int cpu_fetch(CPUPtr cpu)
{
  int error_code = ERR_NO_ERROR;
  
  if (cpu != (CPUPtr) NULL)
  {
    ushort addr = pc_get(cpu->pc, &error_code);
    
    if (error_code != ERR_NO_ERROR)
    {
      return error_code;
    }
    
    ushort instruction = memory_fetchWordFrom(cpu->mem, addr, &error_code);
    
    if (error_code != ERR_NO_ERROR)
    {
      return error_code;
    }
    
    error_code = ir_set(cpu->ir, instruction);
    
    if (error_code != ERR_NO_ERROR)
    {
      return error_code;
    }
    
    error_code = pc_set(cpu->pc, addr+2);
  }
  else
  {
    error_code = ERR_NULL_POINTER_EXCEPTION;
  }
  
  return error_code;
}

/*=============================================================================
 =  Comment block for function: cpu_decode
 =  Programmer name:
 =  Final test and approval date: 2-28-11
 =  Synopsis:
 =      Parameters: CPUPtr to have its instruction decoded
 =      Return type: inst_type containing the instruction that should be
 =                              performed
 =
 =  Attempts to decode the current instruction in the passed CPU.
 ============================================================================*/
inst_type cpu_decode(CPUPtr cpu, int * error_code)
{
  inst_type return_inst_type = invalid_inst_type;
  
  if (cpu != (CPUPtr) NULL)
  {
    *error_code = ERR_NO_ERROR;
    
    unsigned int ir = ir_get(cpu->ir, error_code);
    
    if (*error_code == ERR_NO_ERROR)
    {
      unsigned int extracted_op = ir >> OPCODE_SHIFT_VAL;
      
      *error_code = alu_putCurrentOp(cpu->alu, extracted_op);
      
      if (extracted_op >= ADD && extracted_op <= XOR)
      {
        switch (extracted_op)
        {
          case MUL:
            return_inst_type = alu_mul_type;
            break;
            
          case DIV:
            return_inst_type = alu_div_type;
            break;
            
          default:
            return_inst_type = alu_2op_type;
            break;
        }
      }
      else
      {
        switch (extracted_op)
        {
          case ADDI:
          case SUBI:
            return_inst_type = alu_imm_type;
            break;
            
          case SH:
            if ((ir & AMOD_MASK) == 0)
            {
              *error_code = alu_putCurrentOp(cpu->alu, SHL_ALU);
              return_inst_type = alu_2op_type;
            }
            else if ((ir & AMOD_MASK) == 1)
            {
              *error_code = alu_putCurrentOp(cpu->alu, SHR_ALU);
              return_inst_type = alu_2op_type;
            }
            else
            {
              return_inst_type = invalid_inst_type;
            }
            break;
            
          case NEG:
          case NOT:
            return_inst_type = alu_1op_type;
            break;
            
          case BR:
            return_inst_type = unconditional_control_type;
            break;
            
          case BRcc:
            return_inst_type = conditional_control_type;
            break;
            
          case LDI:
            return_inst_type = ld_imm_type;
            break;
            
          case LADR:
            return_inst_type = ld_effadr_type;
            break;
            
          case LDB_MOVB:
            if ((ir & AMOD_MASK) == LDB_AMOD)
            {
              return_inst_type = ld_byte_type;
            }
            else if ((ir & AMOD_MASK) == MOVB_AMOD)
            {
              return_inst_type = reg_byte_type;
            }
            else
            {
              return_inst_type = invalid_inst_type;
            }
            break;
            
          case LDW_MOVW:
            if ((ir & AMOD_MASK) == LDW_AMOD)
            {
              return_inst_type = ld_word_type;
            }
            else if ((ir & AMOD_MASK) == MOVW_AMOD)
            {
              return_inst_type = reg_word_type;
            }
            else
            {
              return_inst_type = invalid_inst_type;
            }
            break;
            
          case LDB_BR:
            return_inst_type = ld_byte_br_type;
            break;
            
          case LDW_BR:
            return_inst_type = ld_word_br_type;
            break;
            
          case STB:
            return_inst_type = st_byte_type;
            break;
            
          case STW:
            return_inst_type = st_word_type;
            break;
            
          case STB_BR:
            return_inst_type = st_byte_br_type;
            break;
            
          case STW_BR:
            return_inst_type = st_word_br_type;
            break;
            
          case IN:
            return_inst_type = io_in_type;
            break;
            
          case OUT:
            return_inst_type = io_out_type;
            break;
            
          case HALT:
            return_inst_type = halt_type;
            break;
            
          default:
            break;
        }
      }
    }
  }
  else
  {
    *error_code = ERR_NULL_POINTER_EXCEPTION;
  }
  
  return return_inst_type;
}

/*=============================================================================
 =  Comment block for function: cpu_execute
 =  Programmer name:
 =  Final test and approval date: 2-28-11
 =  Synopsis:
 =      Parameters: CPUPtr to have its instruction executed
 =                  inst_type enumeration which contains the instruction type to
 =                            execute
 =      Return type: int containing any error codes
 =
 =  Attempts to execute the passed instruction type on the passed CPU.
 ============================================================================*/
int cpu_execute(CPUPtr cpu, inst_type instruction_type)
{
  int error_code = ERR_NO_ERROR;
  
  if (cpu != (CPUPtr) NULL)
  {
    word inputA;
    word inputB;
    word outputR;
    word secondaryOutputR;
    uchar reg_num;
    uchar amod;
    ushort sw_flags;
    ushort cc_flags;
    word word_data;
    byte byte_data;
    uchar reg_destin;
    uchar reg_source;
    uchar reg_base;
    uchar reg_offset;
    ushort base_address;
    ushort offset_amount;
    word mem_source;
    ushort port_num;
    ushort pc;
    
    ushort ir = ir_get(cpu->ir, &error_code);
    
    if (error_code == ERR_NO_ERROR)
    {
      pc = pc_get(cpu->pc, &error_code);
    }
    
    if (error_code == ERR_NO_ERROR)
    {
      switch (instruction_type)
      {
        case alu_imm_type:
          reg_num = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          inputB = ir & IMM_OPND_MASK;
          
          inputA = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            error_code = alu_putInputA(cpu->alu, inputA);
          
            if (error_code == ERR_NO_ERROR)
            {
              error_code = alu_putInputBImm(cpu->alu, inputB);
              
              if (error_code == ERR_NO_ERROR)
              {
                error_code = alu_performOperation(cpu->alu);
                
                if (error_code == ERR_NO_ERROR)
                {
                  outputR = alu_getOutputR(cpu->alu, &error_code);
                  
                  if (error_code == ERR_NO_ERROR)
                  {
                    error_code = registerFile_putRegVal(cpu->regFile, reg_num,
                                                        outputR);
                  }
                }
              }
            }
          }
          
          break;
          
        case alu_mul_type:
          reg_num = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          inputB = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
          if (error_code != ERR_NO_ERROR) return error_code;

          reg_num = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          inputA = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = alu_putInputA(cpu->alu, inputA);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = alu_putInputB(cpu->alu, inputB);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = alu_performOperation(cpu->alu);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          outputR = alu_getOutputR(cpu->alu, &error_code);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          secondaryOutputR = alu_getSecondaryOutputR(cpu->alu, &error_code);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = registerFile_putRegVal(cpu->regFile, $R8, outputR);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = registerFile_putRegVal(cpu->regFile, $R9,
                                              secondaryOutputR);
          break;
          
        case alu_div_type:
          reg_num = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          inputB = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          reg_num = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          inputA = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = alu_putInputA(cpu->alu, inputA);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = alu_putInputB(cpu->alu, inputB);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = alu_performOperation(cpu->alu);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          outputR = alu_getOutputR(cpu->alu, &error_code);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          secondaryOutputR = alu_getSecondaryOutputR(cpu->alu, &error_code);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = registerFile_putRegVal(cpu->regFile, $RA, outputR);
          if (error_code != ERR_NO_ERROR) return error_code;
          
          error_code = registerFile_putRegVal(cpu->regFile, $RB,
                                              secondaryOutputR);
          break;
          
        case alu_2op_type:
          reg_num = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          inputB = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            reg_num = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
            inputA = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
            
            if (error_code == ERR_NO_ERROR)
            {
              error_code = alu_putInputA(cpu->alu, inputA);
              
              if (error_code == ERR_NO_ERROR)
              {
                error_code = alu_putInputB(cpu->alu, inputB);
                
                if (error_code == ERR_NO_ERROR)
                {
                  error_code = alu_performOperation(cpu->alu);
                  
                  if (error_code == ERR_NO_ERROR)
                  {
                    outputR = alu_getOutputR(cpu->alu, &error_code);
                    
                    if (error_code == ERR_NO_ERROR)
                    {
                      error_code = registerFile_putRegVal(cpu->regFile, reg_num,
                                                          outputR);
                    }
                  }
                }
              }
            }
          }
          
          break;
          
        case alu_1op_type:
          reg_num = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          inputA = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            error_code = alu_putInputA(cpu->alu, inputA);
            
            if (error_code == ERR_NO_ERROR)
            {
              error_code = alu_performOperation(cpu->alu);
              
              if (error_code == ERR_NO_ERROR)
              {
                outputR = alu_getOutputR(cpu->alu, &error_code);
                
                if (error_code == ERR_NO_ERROR)
                {
                  error_code = registerFile_putRegVal(cpu->regFile, reg_num,
                                                      outputR);
                }
              }
            }
          }
          
          break;
          
        case unconditional_control_type:
          reg_num = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          word_data = registerFile_getRegVal(cpu->regFile, reg_num, &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            error_code = pc_set(cpu->pc, word_data);
          }
          
          break;
          
        case conditional_control_type:
          amod = ir & AMOD_MASK;
          sw_flags = sw_getFlags(cpu->sw, &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            switch (amod)
            {
              case OP_FLAG_N:
                cc_flags = NEG_MASK;
                break;
                
              case OP_FLAG_Z:
                cc_flags = ZERO_MASK;
                break;
                
              case OP_FLAG_C:
                cc_flags = CARRY_MASK;
                break;
                
              case OP_FLAG_O:
                cc_flags = OFLOW_MASK;
                break;
                
              default:
                break;
            }
            
            if ((cc_flags & sw_flags) == cc_flags)
            {
              reg_num = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
              
              word_data = registerFile_getRegVal(cpu->regFile, reg_num,
                                                 &error_code);
              
              if (error_code == ERR_NO_ERROR)
              {
                error_code = pc_set(cpu->pc, word_data);
              }
            }
          }
          
          break;
          
        case ld_imm_type:
          reg_destin = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          word_data = ir & IMM_OPND_MASK;
          error_code = registerFile_putRegVal(cpu->regFile, reg_destin,
                                              word_data);
          
          break;
          
        case ld_effadr_type:
          reg_destin = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          
          word_data = memory_fetchWordFrom(cpu->mem, pc, &error_code);	
          if (error_code == ERR_NO_ERROR)
          {
            error_code = registerFile_putRegVal(cpu->regFile, reg_destin,
                                                word_data);
            
            if (error_code == ERR_NO_ERROR)
            {
              pc += 2;
              
              error_code = pc_set(cpu->pc, pc);
            }
          }
          
          break;
          
        case ld_byte_type:
          reg_destin = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_source = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          mem_source = registerFile_getRegVal(cpu->regFile, reg_source,
                                              &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            byte_data = memory_fetchByteFrom(cpu->mem, mem_source, &error_code);
            
            if (error_code == ERR_NO_ERROR)
            {
              if (reg_destin <= $R3)
              {
                error_code = registerFile_putByteTo(cpu->regFile, reg_destin,
                                                    LO_BYTE, byte_data);
              }
              else
              {
                error_code = ERR_INVALID_REGISTER;
              }
            }
          }
          
          break;
          
        case ld_word_type:
          reg_destin = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_source = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          mem_source = registerFile_getRegVal(cpu->regFile, reg_source,
                                              &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            word_data = memory_fetchWordFrom(cpu->mem, mem_source, &error_code);
            
            if (error_code == ERR_NO_ERROR)
            {
              error_code = registerFile_putRegVal(cpu->regFile, reg_destin,
                                                  word_data);
            }
          }
          
          break;
          
        case ld_byte_br_type:
          reg_destin = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_base = (ir & R_MASK) >> R_SHIFT_VAL;
          reg_offset = (ir & BR_OFSET_MASK) >> 1;
          
          switch (reg_base)
          {
            case 0:
              base_address = registerFile_getRegVal(cpu->regFile, $R8,
                                                    &error_code);
              break;
              
            case 1:
              base_address = registerFile_getRegVal(cpu->regFile, $R9,
                                                    &error_code);
              break;
              
            case 2:
              base_address = registerFile_getRegVal(cpu->regFile, $RA,
                                                    &error_code);
              break;
              
            case 3:
              base_address = registerFile_getRegVal(cpu->regFile, $RB,
                                                    &error_code);
              break;
              
            default:
              error_code = ERR_INVALID_REGISTER;
              break;
          }
          
          if (error_code == ERR_NO_ERROR)
          {
            offset_amount = registerFile_getRegVal(cpu->regFile, reg_offset,
                                                   &error_code);
            
            if (error_code == ERR_NO_ERROR)
            {
              byte_data = memory_fetchByteFrom(cpu->mem,
                                               base_address + offset_amount,
                                               &error_code);
              
              if (error_code == ERR_NO_ERROR)
              {
                error_code = registerFile_putByteTo(cpu->regFile, reg_destin,
                                                    LO_BYTE, byte_data);
              }
            }
          }
          
          break;
          
        case ld_word_br_type:
          reg_destin = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_base = (ir & R_MASK) >> R_SHIFT_VAL;
          reg_offset = (ir & BR_OFSET_MASK) >> 1;
          
          switch (reg_base)
          {
            case 0:
              base_address = registerFile_getRegVal(cpu->regFile, $R8,
                                                    &error_code);
              break;
              
            case 1:
              base_address = registerFile_getRegVal(cpu->regFile, $R9,
                                                    &error_code);
              break;
              
            case 2:
              base_address = registerFile_getRegVal(cpu->regFile, $RA,
                                                    &error_code);
              break;
              
            case 3:
              base_address = registerFile_getRegVal(cpu->regFile, $RB,
                                                    &error_code);
              break;
              
            default:
              error_code = ERR_INVALID_REGISTER;
              break;
          }
          
          if (error_code == ERR_NO_ERROR)
          {
            offset_amount = registerFile_getRegVal(cpu->regFile, reg_offset,
                                                   &error_code);
            
            if (error_code == ERR_NO_ERROR)
            {
              word_data = memory_fetchWordFrom(cpu->mem,
                                               base_address + offset_amount,
                                               &error_code);
              
              if (error_code == ERR_NO_ERROR)
              {
                error_code = registerFile_putRegVal(cpu->regFile, reg_destin,
                                                    word_data);
              }
            }
          }
          
          break;
          
        case st_byte_type:
          reg_source = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_destin = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          byte_data = registerFile_getByteFrom(cpu->regFile, reg_source,
                                               LO_BYTE, &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            mem_source = registerFile_getRegVal(cpu->regFile, reg_destin,
                                                &error_code);
            if (error_code == ERR_NO_ERROR)
            {
              error_code = memory_storeByteTo(cpu->mem, mem_source, byte_data);
            }
          }
          
          break;
          
        case st_word_type:
          reg_source = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_destin = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          word_data = registerFile_getRegVal(cpu->regFile, reg_source,
                                             &error_code);
          
          if (error_code == ERR_NO_ERROR)
          {
            mem_source = registerFile_getRegVal(cpu->regFile, reg_destin,
                                                &error_code);
            
            if (error_code == ERR_NO_ERROR)
            {
              error_code = memory_storeWordTo(cpu->mem, mem_source, word_data);
            }
          }
          
          break;
          
        case st_byte_br_type:
          reg_source = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_base = (ir & R_MASK) >> R_SHIFT_VAL;
          reg_offset = (ir & BR_OFSET_MASK) >> 1;
          byte_data = registerFile_getByteFrom(cpu->regFile, reg_source,
                                               LO_BYTE, &error_code);
          
          switch (reg_base)
          {
            case 0:
              base_address = registerFile_getRegVal(cpu->regFile, $R8,
                                                    &error_code);
              break;
              
            case 1:
              base_address = registerFile_getRegVal(cpu->regFile, $R9,
                                                    &error_code);
              break;
              
            case 2:
              base_address = registerFile_getRegVal(cpu->regFile, $RA,
                                                    &error_code);
              break;
              
            case 3:
              base_address = registerFile_getRegVal(cpu->regFile, $RB,
                                                    &error_code);
              break;
              
            default:
              error_code = ERR_INVALID_REGISTER;
              break;
          }
          
          if (error_code == ERR_NO_ERROR)
          {
            offset_amount = registerFile_getRegVal(cpu->regFile, reg_offset,
                                                   &error_code);
            
            if (error_code == ERR_NO_ERROR)
            {
              error_code = memory_storeByteTo(cpu->mem,
                                              base_address + offset_amount,
                                              byte_data);
            }
          }
          break;
          
        case st_word_br_type:
          reg_source = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_base = (ir & R_MASK) >> R_SHIFT_VAL;
          reg_offset = (ir & BR_OFSET_MASK) >> 1;
          word_data = registerFile_getRegVal(cpu->regFile, reg_source,
                                             &error_code);
          
          switch (reg_base)
          {
            case 0:
              base_address = registerFile_getRegVal(cpu->regFile, $R8,
                                                    &error_code);
              break;
              
            case 1:
              base_address = registerFile_getRegVal(cpu->regFile, $R9,
                                                    &error_code);
              break;
              
            case 2:
              base_address = registerFile_getRegVal(cpu->regFile, $RA,
                                                    &error_code);
              break;
              
            case 3:
              base_address = registerFile_getRegVal(cpu->regFile, $RB,
                                                    &error_code);
              break;
              
            default:
              error_code = ERR_INVALID_REGISTER;
              break;
          }
          
          if (error_code == ERR_NO_ERROR)
          {
            offset_amount = registerFile_getRegVal(cpu->regFile, reg_offset,
                                                   &error_code);
            
            if (error_code == ERR_NO_ERROR)
            {
              error_code = memory_storeWordTo(cpu->mem,
                                              base_address + offset_amount,
                                              word_data);
            }
          }
          break;
          
        case reg_byte_type:
          reg_destin = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_source = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          
          if (reg_source <= $R3 && reg_destin <= $R3)
          {
            byte_data = registerFile_getByteFrom(cpu->regFile,
                                                         reg_source, LO_BYTE,
                                                         &error_code);
            if (error_code == ERR_NO_ERROR)
            {
              error_code = registerFile_putByteTo(cpu->regFile, reg_destin,
                                                  LO_BYTE, byte_data);
            }
          }
          else
          {
            error_code = ERR_INVALID_REGISTER;
          }
          
          break;
          
        case reg_word_type:
          reg_destin = (ir & OPND_A_MASK) >> OPND_A_SHIFT_VAL;
          reg_source = (ir & OPND_B_MASK) >> OPND_B_SHIFT_VAL;
          
          word_data = registerFile_getRegVal(cpu->regFile, reg_source,
                                                &error_code);
          if (error_code == ERR_NO_ERROR)
          {
            error_code = registerFile_putRegVal(cpu->regFile, reg_destin,
                                                word_data);
          }
          
          break;
          
        case io_in_type:
          port_num = ir & IO_PORT_MASK;
          
          switch (port_num)
          {
            case IO_PORT_KBD:
              do
              {
                byte_data = getc(stdin);
              } while (byte_data == 0x0A);
              error_code = registerFile_putByteTo(cpu->regFile, $R0, LO_BYTE,
                                                  byte_data);
              break;
              
            default:
              error_code = ERR_INVALID_IO_PORT;
              break;
          }
		      break;
		      
		    case io_out_type:
		      port_num = ir & IO_PORT_MASK;
		      
		      switch (port_num)
          {
            case IO_PORT_VID:
              byte_data = registerFile_getByteFrom(cpu->regFile, $R0, LO_BYTE,
                                                   &error_code);
              if (error_code == ERR_NO_ERROR)
              {
                printf("%c", byte_data);
              }
              
              break;
              
            default:
              error_code = ERR_INVALID_IO_PORT;
              break;
          }
		      break;
          
		    case halt_type:
		      hb_assert(cpu->hb);
		      break;
          
		    default:
		      error_code = ERR_INVALID_OPERATION;
		      break;
      }
    }
    
  }
  else
  {
    error_code = ERR_NULL_POINTER_EXCEPTION;
  }
  
  return error_code;
}


/*=============================================================================
 =  Comment block for function: cpu_reset
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: CPUPtr to be reset
 =      Return type: int containing any error codes
 =
 =  Resets the passed in CPU.
 ============================================================================*/
int cpu_reset(CPUPtr cpu)
{
  if (cpu != (CPUPtr) NULL)
  {
    pc_set(cpu->pc, 0x3000);
    ir_set(cpu->ir, 0x0000);
    hb_clear(cpu->hb);
    sw_clearFlags(cpu->sw);
    
    return ERR_NO_ERROR;
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
  
}

/*=============================================================================
 =  Comment block for function: cpu_halt
 =  Programmer name:
 =  Final test and approval date: 2-10-11
 =  Synopsis:
 =      Parameters: CPUPtr for the ALU to be operated on
 =                  uchar containing the toggle value for the HaltBit
 =      Return type: int containing any error codes
 =
 =  Asserts or Clears the HaltBit for the passed CPU.
 ============================================================================*/
int cpu_haltSet(CPUPtr cpu, uchar halt_toggle)
{
  if (cpu != (CPUPtr) NULL)
  {
    if (halt_toggle == HALT_ASSERT)
    {
      return hb_assert(cpu->hb);
    }
    else if (halt_toggle == HALT_CLEAR)
    {
      return hb_clear(cpu->hb);
    }
    else
    {
      return ERR_ILLEGAL_ARGUMENT_EXCEPTION;
    }
  }
  else
  {
    return ERR_NULL_POINTER_EXCEPTION;
  }
}


/*=============================================================================
 =  Comment block for function: printErrMsg
 =  Programmer name:
 =  Final test and approval date: 1-25-11
 =  Synopsis:
 =      Parameters: int containing the error code
 =      Return type: void
 =
 =  Prints the error code associated with the value passed in, if none is
 =    assigned it prints nothing.
 ============================================================================*/
void printErrMsg(int error_code)
{
  switch (error_code)
  {
    case ERR_UNDEFINED_ERROR:
      printf("\nAn undefined error occured.\n");
      break;
      
    case ERR_NULL_POINTER_EXCEPTION:
      printf("\nError: NULL pointer exception.\n");
      break;
      
    case ERR_INVALID_BYTE_DESCRIPTOR:
      printf("\nError: Invalid byte descriptor.\n");
      break;
      
    case ERR_INVALID_REGISTER:
      printf("\nError: Invalid register.\n");
      break;
      
    case ERR_DATA_TYPE_MISMATCH:
      printf("\nError: Data type mismatch.\n");
      break;
      
    case ERR_MEMORY_ADDRESS_OUT_OF_BOUNDS:
      printf("\nError: Memory address out of bounds.\n");
      break;
      
    case ERR_INVALID_OPERATION:
      printf("\nError: Invalid Operation.\n");
      break;
      
    case ERR_ILLEGAL_ARGUMENT_EXCEPTION:
      printf("\nError: Invalid Argument Exception.\n");
      break;
      
    case ERR_INVALID_IO_PORT:
      printf("\nError: Invalid I/O Port.\n");
      break;
      
    default:
      break;
  }
}

/*=============================================================================
 =  Comment block for function: get_input
 =  Programmer name:
 =  Final test and approval date: 1-25-11
 =  Synopsis:
 =      Parameters: int containing the minimum value to allow
 =                  int containing the maximum value to allow
 =                  char * containing a prompt
 =                  char * containing the error message
 =      Return type: int containing the value recieved
 =
 =  This function accepts a min and max for range and two messages, it then
 =    takes user input until acceptable data is entered, once an acceptable
 =    value is inputted, it is converted to an int and returned.
 ============================================================================*/
int get_input(int min, int max, char * string, char * errorMessage)
{
  char char_input;
  char buffer[BUFFER_SIZE];
  short first = 0;
  int count = 0;
  
  int valueA = min - 1;
  
  while (valueA < min || valueA > max)
  {
    if (first++ == 0)
    {
      printf("%s\n", string);
    }
    else
    {
      printf("%s\n", errorMessage);
    }
    
    char_input = getc(stdin);
    if (char_input == '\n')
    {
      char_input = getc(stdin);
    }
    
    count = 0;
    while((char_input != '\n')  &&  (count < BUFFER_SIZE))
    {
      buffer[count++] = char_input;
      char_input = getc(stdin);
    }
    
    buffer[count] = NULL_BYTE; /* null terminate buffer */
    
    if (buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))
    {
      valueA = strtol(buffer, NULL, HEXADECIMAL);
    }
    else if ((buffer[0] >= '0' && buffer[0] <= '9') || (buffer[0] == '-'))
    {
      valueA = atoi(buffer);
    }
    else
    {
      printf("\nInput needs to be integer numbers ");
      printf("or hex values that start with '0x'\n");
    }
  }
  
  return valueA;
}


/*=====================================================================================================
 =   Comment block for function: dbm_initialize
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		startCommand dbm_initialize(int argc, char *argv[], CPUPtr cpu)
 =		return value ranges: menu: the program should begin by displaying the menu
 =                           run: the program should begin by running the provided program
 =                           step: the program should begin by stepping through the program
 =		parameter value ranges: N/A
 =		error conditions: N/A
 =
 =   Takes a CPUPtr and the command line arguments and determines how the program should begin. No arguments
 =	 results in going straight to the main menu. "-p" runs the file that follows. Adding "-s" will step through 
 =	 the program instead of running it. Any other arguments will cause the program to run the menu.
 =
 ====================================================================================================*/
startCommand dbm_initialize(int argc, char *argv[], CPUPtr cpu) {
	
	startCommand cmd;
	char * filename;
	
	/*No args*/
	if (argc == 1) {
		cmd = menu;
	} 
	
	/*Object file included*/
	else if ((argc == SWITCH_ARG_NUM) || (argc == SWITCH_ARG_NUM+1)) {
		
		if (!strcmp(argv[1], SWITCH_LOADFILE)){ /*Test first switch*/
			
			filename = dbm_checkFileName(argv[2]);
			
			if (filename == NULL) {
				printf(FILE_ERROR);
				cmd = menu;
			} 
			else if (dbm_loadFile(cpu, filename) != ERR_NO_ERROR) {
				printf(FILE_ERROR);
				cmd = menu;
			}
			else {
				if (argc == SWITCH_ARG_NUM) {
					cmd = run;
				} 
				else {
					if (!strcmp(argv[SWITCH_ARG_NUM], SWITCH_STEP)){ /*Test second switch*/
						cmd = step;
					}
					else {
						printf(SECOND);
						cmd = menu;
					}
				}
			}
			
		}
		else {
			printf(FIRST);
			cmd = menu;
		}
		
	} 
	
	/*Garbage provided*/
	else {
		printf(ARGUMENTS);
		cmd = menu;
	}
	
	return cmd;
}

/*=====================================================================================================
 =   Comment block for function: dbm_loadFile
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		int dbm_loadFile(CPUPtr cpu, char *filename)
 =		return value ranges: See error condtions below
 =		parameter value ranges: N/A
 =		error conditions: ERR_NO_ERROR: no error
 =						  ERR_OBJ_FILE_FORMAT: the provided object file is invalid
 =
 =   Loads an object file's contents into memory.
 =
 ====================================================================================================*/
int dbm_loadFile(CPUPtr cpu, char *filename) {
	int return_code = ERR_NO_ERROR;
	int error;
	int *errorPtr = (int *) malloc(sizeof(int));
	word value;
	ushort address = START_ADDRESS;
	FILE *file = fopen(filename, "r");
	char *line = (char *) malloc(sizeof(char) * LINESIZE);
	char *line1 = (char *) malloc(sizeof(char) * LINESIZE - 2);
	char *line2 = (char *) malloc(sizeof(char) * LINESIZE - 2);
	*errorPtr = ERR_NO_ERROR;
	
	if (file == NULL) {
		return_code =  ERR_OBJ_FILE_FORMAT;
	}
	
	while (return_code == ERR_NO_ERROR && !feof(file)) {
		
		line1 = fgets(line1, LINESIZE - 2, file);
		
		if (line1 == NULL) {
			break;
		} else if (feof(file)) {
			return_code = ERR_OBJ_FILE_FORMAT;
			break;
		}
		line2 = fgets(line2, LINESIZE - 2, file);
		
		if (line2 == NULL) {
			return_code = ERR_OBJ_FILE_FORMAT;
			break;
		} else if (line1[2] != '\n' && line1[2] != '\r' && line1[2] != '\0') {
			return_code = ERR_OBJ_FILE_FORMAT;
			break;
		} else if (line2[2] != '\n' && line2[2] != '\r'&& line2[2] != '\0') {
			return_code = ERR_OBJ_FILE_FORMAT;
			break;
		}
		
		line2[2] = '\0';
		strcpy(line, line2);
		line = strcat(line, line1);
		
		
		if (line[LENGTH_OF_LINE] != NEW_LINE && line[LENGTH_OF_LINE] != CR && line[LENGTH_OF_LINE] != NULL_CHAR) {
			return_code = ERR_OBJ_FILE_FORMAT;
			break;
		}
		
		line[LENGTH_OF_LINE]=NULL_CHAR;
		
		value = dbm_convertStringToShort(line, errorPtr);
		
		if (*errorPtr != ERR_NO_ERROR) {
			return_code = ERR_OBJ_FILE_FORMAT;
			break;
		}
		error = memory_storeWordTo(cpu->mem, address, value);
		address += 2; /*each instruction is a word (two memory slots)*/
		
		if (error != ERR_NO_ERROR) {
			return_code = error;
			
		}
	}
	
	if (return_code == ERR_NO_ERROR) {
		cpu_reset(cpu);
		printf(LOAD_SUCCESS);
	}
	else {
		printf(LOAD_FAIL);
	}

	
	free(line1);
	free(line2);
	free(line);
	free(errorPtr);
	fclose(file);
	return return_code;
}


/*=====================================================================================================
 =   Comment block for function: dbm_run
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		int dbm_run(CPUPtr cpu)
 =		return value ranges: N/A
 =		parameter value ranges: N/A
 =		error conditions: int containing any error codes
 =
 =   Runs the CPU with the program currently loaded in memory.
 =
 ====================================================================================================*/
void dbm_run(CPUPtr cpu) {
	printErrMsg(cpu_run(cpu));
	printf(FINISHED);
}


/*=====================================================================================================
 =   Comment block for function: dbm_step
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		void dbm_step(CPUPtr cpu)
 =		return value ranges: N/A
 =		parameter value ranges: N/A
 =		error conditions: N/A
 =
 =   Displays a sub menu which allows the user to step through the program. The user may select to step,
 =	 display a section of memory, display the registers, or exit to the main menu.
 =
 ====================================================================================================*/
void dbm_step(CPUPtr cpu) {
	
	char c;
	int *errorPtr = (int *) malloc(sizeof(int));
	word sw;
  word pc;
  word ir;
	
	printf(STEP_MENU);
  pc = pc_get(cpu->pc, errorPtr);
  ir = memory_fetchWordFrom(cpu->mem, pc, errorPtr);
	printf("PC: 0x%.4X\n", pc);
	printf("IR: 0x%.4X\n", ir);
	sw = sw_getFlags(cpu->sw, errorPtr);
	
	if ((sw & NEG_MASK) > 0)
	{
		printf("1 ");
	}
	else {
		printf("0 ");
	}

	if ((sw & ZERO_MASK) > 0)
	{
		printf("1 ");
	}
	else {
		printf("0 ");
	}

	if ((sw & CARRY_MASK) > 0)
	{
		printf("1 ");
	}
	else {
		printf("0 ");
	}

	if ((sw & OFLOW_MASK) > 0)
	{
		printf("1\n");
	}
	else {
		printf("0\n");
	}

	
	printf("N Z C O\n");
	
	printf(STEP_MESSAGE);
	while ((c = getchar()) == NEW_LINE);
	printf("\n");
	
	if (!hb_get(cpu->hb, errorPtr)) {
		
		switch (c) {
			case ' ':
				printErrMsg(cpu_step(cpu));
				dbm_step(cpu);
				break;
			case 'm':
				getchar();
				dbm_displayMem(cpu);
				dbm_step(cpu);
				break;
			case 'r':
				dbm_displayReg(cpu);
				dbm_step(cpu);
				break;
			case 'x':
				getchar();
				break;
			case 'c':
				while (!hb_get(cpu->hb, errorPtr)) {
					cpu_step(cpu);
				}
				getchar();
				break;
			default:
				printf("%s\n", ERROR);
				dbm_step(cpu);
				break;
		}
	} else {
		printf(HALT_MESSAGE);
		getchar();
	}
	
	free(errorPtr);
}


/*=====================================================================================================
 =   Comment block for function: dbm_displayReg
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		void dbm_displayReg(CPUPtr cpu)
 =		return value ranges: N/A
 =		parameter value ranges: N/A
 =		error conditions: N/A
 =
 =   Displays the contents of each register.
 =
 ====================================================================================================*/
void dbm_displayReg(CPUPtr cpu) {
	int i;
	int * errorPtr = (int *) malloc(sizeof(int));
	*errorPtr = ERR_NO_ERROR;
	printf("    %s", REGISTER_MESSAGE);
	for (i = 0; i < REGISTER_COUNT; i++) {
		printf("| $R%X | 0x%.4X |\n", i, registerFile_getRegVal(cpu->regFile, (uchar) i, errorPtr));
	}
	
	free(errorPtr);
}


/*=====================================================================================================
 =   Comment block for function: dbm_displayMem
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		void dbm_displayMem(CPUPtr cpu)
 =		return value ranges: N/A
 =		parameter value ranges: N/A
 =		error conditions: N/A
 =
 =   Displays a section of memory. The user selects a starting address and ending address and all
 =	 entries between (and including) are displayed.
 =
 ====================================================================================================*/
void dbm_displayMem(CPUPtr cpu) {
	int i, first, second;
	int * errorPtr = (int *) malloc(sizeof(int));
	*errorPtr = ERR_NO_ERROR;
	
	first = get_input(START_ADDRESS, LAST_ADDRESS, MEM_START, ADDRESS);
	printf("\n");
	second = get_input(first+1, LAST_ADDRESS, MEM_END, ADDRESS);
	printf("\n");
	
	
	for (i = first; i <= second; i++) {
		printf("| Memory[0x%.4X] | 0x%.2X |\n", i, memory_fetchByteFrom(cpu->mem, (ushort) i, errorPtr));
	}
	
	free(errorPtr);
}

/*=====================================================================================================
 =   Comment block for function: dbm_userSelect
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		int dbm_userSelect(CPUPtr cpu)
 =		return value ranges: non-zero if user selected quit, 0 otherwise
 =		parameter value ranges: N/A
 =		error conditions: N/A
 =
 =   Main menu, which prompts user for choice. Choices are load file, run, step, display registers,
 =	 display memory, and quit.
 =
 ====================================================================================================*/
int dbm_userSelect(CPUPtr cpu) {	
	char *fileName;
	char * errorMessage = (char *) malloc(sizeof ERROR);
	strcpy(errorMessage, ERROR);
	
	printf("\n");
	int input = get_input(LOADFILE, QUIT, message, errorMessage);
	printf("\n");
	
	switch (input) {
		case LOADFILE:
			fileName = dbm_getFileName();
			if (fileName != NULL) {
				if (dbm_loadFile(cpu, fileName) != ERR_NO_ERROR) {
					printf(FILE_ERR);
				}
				free(fileName);
			} else {
				printf(FILE_ERROR);
			}
			
			break;
		case RUN:
			dbm_run(cpu);
			break;
		case STEP:
			dbm_step(cpu);
			break;
		case DISPLAYREG:
			dbm_displayReg(cpu);
			break;
		case DISPLAYMEM:
			dbm_displayMem(cpu);
			break;
		case QUIT:
			return QUIT;
			break;
	}
	free(errorMessage);
	return 0;
}

/*=====================================================================================================
 =   Comment block for function: dbm_convertStringToShort
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		ushort dbm_convertStringToShort(char *string, int *error)
 =		return value ranges: 0 to 0xFFFF
 =		parameter value ranges: each character in string must be a hexidecimal digit
 =		error conditions:	ERR_NULL_POINTER_EXCEPTION if string is null
 =							ERR_DATA_TYPE_MISMATCH if string contains a character other than '0' or '1'
 =							ERR_STRING_TOO_LARGE if string is greater than 16 charatcer and a null terminator
 =
 =   Converts a char * into a ushort
 =
 ====================================================================================================*/
ushort dbm_convertStringToShort(char *string, int *error) {
	
	int i, length;
	ushort value = 0;
	char c;
	
	if (string != NULL){
		length = strlen(string);
		if (length == LENGTH_OF_LINE) { 
			
			for(i = 0; i < length; i++) {
				c = string[i];
				
				if (!isxdigit(c)) {
					*error = ERR_ILLEGAL_ARGUMENT_EXCEPTION;
					break;
				}
				
				c = toupper(c);
				
				if (isdigit(c)) {
					value += (c - ASCII_NUMBER_OFFSET) * dbm_pow(HEX_VALUES, length - 1 - i); 
				} else if (isalpha(c)) {
					value += (c - ASCII_LETTER_OFFSET) * dbm_pow(HEX_VALUES, length - 1 - i);
				}
			}
		}
		else {
			*error = ERR_STRING_SIZE;
		}
	}
	else {
		*error = ERR_NULL_POINTER_EXCEPTION;
	}
	return value;
}


/*=====================================================================================================
 =   Comment block for function: dbm_getFileName
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		char *dbm_getFileName()
 =		return value ranges: a char pointer
 =		parameter value ranges: N/A
 =		error conditions: N/A
 =
 =   Allows the user to input the name of an object file to load.
 =
 ====================================================================================================*/
char *dbm_getFileName() {
	int length;
	char *string;
	char *filename = (char *) malloc(sizeof(char) * (INPUT_SIZE + 1));
	
	printf(FILENAME_MESSAGE);
	filename = fgets(filename, INPUT_SIZE, stdin);
	printf("\n");
	if (filename != NULL) {
		length = strlen(filename);
		filename[length-1] = NULL_CHAR;
		string = (char *) malloc(sizeof(char) * length - 1);
		string = dbm_checkFileName(strcpy(string, filename));
	}
	free(filename);
	return string;
}


/*=====================================================================================================
 =   Comment block for function: dbm_checkFileName
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		char *dbm_checkFileName(char * filename)
 =		return value ranges: a char pointer or null
 =		parameter value ranges: a char pointer
 =		error conditions: N/A
 =
 =   Checks a file name to make sure that it is a valid object file with the .obj extention. If it is 
 =	 not then null it returned. If it is then the file name is returned.
 =
 ====================================================================================================*/
char *dbm_checkFileName(char * filename) {
	int result;
	char *dot;
	
	if (filename != NULL) {
		dot = strchr(filename, '.');
		if (dot == NULL) {
			filename = NULL;
		} else {
			result = strcmp(dot + 1, OBJ);
			
			if (result || *(dot + LENGTH_OF_LINE) != NULL_CHAR) {
				filename = NULL;
			} 
		}
	}
	return filename;
}


/*=====================================================================================================
 =   Comment block for function: dbm_pow
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		int dbm_pow(int base, int exp)
 =		return value ranges: an integer
 =		parameter value ranges: a base intenger and an exponent integer
 =		error conditions: N/A
 =
 =   Calculates the result of x^y recursively. 
 =
 ====================================================================================================*/
int dbm_pow(int base, int exp) {
	if (exp < 0) return 0; /*Doesn't deal with negative exponent*/
	else if (!exp) return 1;
	else if (exp == 1) return base;
	else return base * dbm_pow(base, exp - 1);
}


/*=====================================================================================================
 =   Comment block for function: main
 =   Programmer name: Avram Blaszka, Matt Smith
 =   Final test and approval date: February 28, 2011
 =   Synopsis:
 =		int main(int argc, char *argv[])
 =		return value ranges: N/A
 =		parameter value ranges: N/A (Command line arguments)
 =		error conditions: N/A
 =
 =   THE MAIN
 =
 ====================================================================================================*/

int main(int argc, char *argv[]) {
	
	CPUPtr cpu = cpu_initialize();
	
	switch (dbm_initialize(argc, argv, cpu)) {
		case menu:
			if (dbm_userSelect(cpu) == QUIT) exit(0);
			break;
		case run:
			dbm_run(cpu);
			break;
		case step:
			dbm_step(cpu);
			break;
	}
	
	while (dbm_userSelect(cpu) != QUIT);
	
}
