#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    //Add
	if((int)ALUControl == 0)
		*ALUresult = A + B;
    //Subtract
	else if((int)ALUControl == 1)
		*ALUresult = A - B;
    //SOLT
	else if((int)ALUControl == 2){
		if((signed)A < (signed)B)
			*ALUresult = 1;
		else
			*ALUresult = 0;
	}
    //SOLT unsigned
	else if((int)ALUControl == 3){
		if(A < B)
			*ALUresult = 1;
		else
			*ALUresult = 0;
	}
    //Bitwise and
	else if((int)ALUControl == 4)
		*ALUresult = (A & B);
    //Bitwise or
	else if((int)ALUControl == 5)
		*ALUresult = (A | B);
    //Shift left 16
	else if((int)ALUControl == 6)
		B << 16;
    //Bitwise not
	else if((int)ALUControl == '7')
		*ALUresult == (~A);
    //Set 0
	if(*ALUresult == 0)
		*Zero = 1;
	else
		*Zero = 0;
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    //If not word aligned then halt
	if(PC % 4 != 0)
		return 1;

    //Adjust word then get the instruction from memory, return
	*instruction = Mem[PC >> 2];
	return 0;
}

/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    //Get bits we need and shift them all the way to the right
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

	switch (op) {

        	case 0:   //R-type instructions
   			       controls->RegDst = 1;
                   controls->Jump = 0;
			       controls->Branch = 0;
			       controls->MemRead = 0;
			       controls->MemtoReg = 0;
			       controls->ALUOp = 7;
			       controls->MemWrite = 0;
			       controls->ALUSrc = 0;
			       controls->RegWrite = 1;
                   break;

        	case 2:  //j
   			       controls->RegDst = 0;
                   controls->Jump = 1;
			       controls->Branch = 0;
			       controls->MemRead = 0;
			       controls->MemtoReg = 0;
			       controls->ALUOp = 0;
			       controls->MemWrite = 0;
			       controls->ALUSrc = 0;
			       controls->RegWrite = 0;
                   break;

        	case 4:  //beq
   			       controls->RegDst = 0;
                   controls->Jump = 0;
			       controls->Branch = 1;
			       controls->MemRead = 0;
			       controls->MemtoReg = 0;
			       controls->ALUOp = 1;
			       controls->MemWrite = 0;
			       controls->ALUSrc = 0;
			       controls->RegWrite = 0;
                   break;

         	case 8:   //add immediate
   			       controls->RegDst = 0;
                   controls->Jump = 0;
			       controls->Branch = 0;
			       controls->MemRead = 0;
			       controls->MemtoReg = 0;
			       controls->ALUOp = 0;
			       controls->MemWrite = 0;
			       controls->ALUSrc = 1;
			       controls->RegWrite = 1;
                   break;

        	case 9:  //sltiu
   			       controls->RegDst = 0;
                   controls->Jump = 0;
			       controls->Branch = 0;
			       controls->MemRead = 0;
			       controls->MemtoReg = 0;
			       controls->ALUOp = 3;
			       controls->MemWrite = 0;
			       controls->ALUSrc = 1;
			       controls->RegWrite = 1;
                   break;

         	case 10:  //slti (signed)
   			       controls->RegDst = 0;
                   controls->Jump = 0;
			       controls->Branch = 0;
			       controls->MemRead = 0;
			       controls->MemtoReg = 0;
			       controls->ALUOp = 2;
			       controls->MemWrite = 0;
			       controls->ALUSrc = 1;
			       controls->RegWrite = 1;
                   break;

			case 15:  //lui
   			       controls->RegDst = 0;
                   controls->Jump = 0;
			       controls->Branch = 0;
			       controls->MemRead = 0;
			       controls->MemtoReg = 0;
			       controls->ALUOp = 6;
			       controls->MemWrite = 0;
			       controls->ALUSrc = 1;
			       controls->RegWrite = 1;
                   break;

        	case 35:  //lw

				controls->RegDst = 0;
        		controls->Jump = 0;
		    	controls->Branch = 0;
		    	controls->MemRead = 1;
		    	controls->MemtoReg = 1;
		    	controls->ALUOp = 0;
		    	controls->MemWrite = 0;
		    	controls->ALUSrc = 1;
		    	controls->RegWrite = 1;
            	break;

        	case 43:  //sw

				controls->RegDst = 2;
                controls->Jump = 0;
		        controls->Branch = 0;
		        controls->MemRead = 0;
		        controls->MemtoReg = 2;
		        controls->ALUOp = 0;
		        controls->MemWrite = 1;
		        controls->ALUSrc = 1;
		        controls->RegWrite = 0;
                break;

        	default:

                return 1;
                   }
    return 0;

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
 	*data1=Reg[r1];
 	*data2=Reg[r2];

}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

	unsigned sign=offset;

	sign=sign>>15;

	int value = (0xFFFF0000 | offset);

    if (sign==1) {
        *extended_value = value;
    }
    else
        *extended_value & 0x0000FFFF;


}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	if(ALUSrc == 1)
		data2 = extended_value;

    //R Type
	if(ALUOp == 7){
        //Shift left 16
		if(funct == 6)
			ALU(data1, data2, 6, ALUresult, Zero);
        //Add
		else if(funct == 32)
			ALU(data1, data2, 0, ALUresult, Zero);
        //Subtract
		else if(funct == 34)
			ALU(data1, data2, 1, ALUresult, Zero);
        //And bitwise
		else if(funct == 36)
			ALU(data1, data2, 4, ALUresult, Zero);
        //Or bitwise
		else if(funct == 37)
			ALU(data1, data2, 5, ALUresult, Zero);
        //Not bitwise
		else if(funct ==39)
			ALU(data1, data2, 7, ALUresult, Zero);
        //Set on less than
		else if(funct == 42)
			ALU(data1, data2, 2, ALUresult, Zero);
        //Set on less than unsigned
		else if(funct == 43)
			ALU(data1, data2, 3, ALUresult, Zero);
        //illegal operation
		else return 1;

        //Finished
		return 0;
	}
    //Add or don't care
	else if(ALUOp == 0)
		ALU(data1, data2, 0, ALUresult, Zero);
    //Subtract
	else if(ALUOp == 1)
		ALU(data1, data2, 1, ALUresult, Zero);
    //Set on less than
	else if(ALUOp == 2)
		ALU(data1, data2, 2, ALUresult, Zero);
    //Set on less than unsigned
	else if(ALUOp == 3)
		ALU(data1, data2, 3, ALUresult, Zero);
    //And
	else if(ALUOp == 4)
		ALU(data1, data2, 4, ALUresult, Zero);
    //Or
	else if(ALUOp == 5)
		ALU(data1, data2, 5, ALUresult, Zero);
    //Shift 16
	else if(ALUOp == 6)
		ALU(data1, data2, 6, ALUresult, Zero);
    //illegal operation
	else return 1;

	return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	if(ALUresult % 4 != 0)
		return 1;

	if (MemRead == 1) {
        *memdata = Mem[ALUresult >> 2];

    }
    if (MemWrite == 1) {
        Mem[ALUresult >> 2] = data2;

    }
    return 0;
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
    //PC always gets updated intiially
    *PC += 4;

    //If branching and supposed to branch, add extended value
    if(Branch == 1 && Zero == 1)
        *PC = *PC + (extended_value<<2);
    //If jumping shift and concatenate
    else if(Jump == 1)
        *PC = (*PC & 0xF0000000) | (jsec<<2);
}
