#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	if(ALUControl == 0)
		*ALUresult = A + B;
	else if(ALUControl == 1)
		*ALUresult = A - B;
	else if(ALUControl == 2){
		if(A < B)
			*ALUresult = 1;
		else
			*ALUresult = 0;
	}
	else if(ALUControl == 3){
		if(A < B)
			*ALUresult = 1;
		else
			*ALUresult = 0;
	}
	else if(ALUControl == 4)
		*ALUresult = (A & B);
	else if(ALUControl == 5)
		*ALUresult = (A | B);
	else if(ALUControl == 6)
		B >> 16;
	else if(ALUControl == '7')
		*ALUresult == (!A);
	
	if(*ALUresult == 0)
		*Zero = 1;
	else
		*Zero = 0;
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	if(PC % 4 != 0)
		return 1;

	*instruction = Mem[PC >> 2];
	return 0;	
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	*op = (instruction & 0xFC000000) >> 26;
	*r1 = (instruction & 0x3E00000) >> 21;
	*r2 = (instruction & 0x1F0000) >> 16;
	*r3 = (instruction & 0xF800) >> 11;
	*funct = (instruction & 0x00003F);
	*offset = (instruction & 0x00FFFF);
	*jsec = (instruction & 0x3FFFFFF);

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	if(ALUSrc == 1)
		data2 = extended_value;

	if(ALUOp == 7){
		if(funct == 6)
			ALU(data1, data2, 6, AlUresult, Zero); 
		else if(funct == 32)
			ALU(data1, data2, 0, ALUresult, Zero);
		else if(funct == 34)
			ALU(data1, data2, 1, ALUresult, Zero);
		else if(funct == 36)
			ALU(data1, data2, 4, ALUresult, Zero);
		else if(funct == 37)
			ALU(data1, data2, 5, ALUresult, Zero);
		else if(funct ==39)
			ALU(data1, data2, 7, ALUresult, Zero);
		else if(funct == 42)
			ALU(data1, data2, 2, ALUresult, Zero);
		else if(funct == 43)
			ALU(data1, data2, 3, ALUresult, Zero);
		else return 1;
	
		return 0;	
	}
	else if(ALUOp == 0)
		ALU(data1, data2, 0, ALUResult, Zero);
	else if(ALUOp == 1)
		ALU(data1, data2, 1, ALUResult, Zero);
	else if(ALUOp == 2)
		ALU(data1, data2, 2, ALUResult, Zero);
	else if(ALUOp == 3)
		ALU(data1, data2, 3, ALUResult, Zero);
	else if(ALUOp == 4)
		ALU(data1, data2, 4, ALUResult, Zero);
	else if(ALUOp == 5)
		ALU(data1, data2, 5, ALUResult, Zero);
	else if(ALUOp == 6)
		ALU(data1, data2, 6, ALUResult, Zero);
	else return 1;
	
	return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

