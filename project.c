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
	
	int value = (0x0000FFFF & offset);
    int mask = 0x00008000;
    
    if (sign==1) {
        value += 0xFFFF0000;
    }
    
    extended_value=&value;
	
}


/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	


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

