#include<reg51.h>
#define byte unsigned char
sbit P3_2	= P3^2;
#define DIEN P3_2
int idata IR_value,PR_value;
byte xdata lcdc_addr _at_ 0x01; // used to send command
byte xdata lcdc_data _at_ 0x00; // used to send command parameter

unsigned char xdata *ptr = 0x00;

void init_lcd();
void setReg(int a,int b);
void clear_screen();
/**********************************************************************************
	設定msm6255暫存器的函數
**********************************************************************************/
void setReg(int a,int b)
{
	DIEN = 1;
	P1=0xF4; 	
	lcdc_addr=a;	
	lcdc_data=b;
}
/**********************************************************************************
	初始化msm6255
	by external memory address 0x00 and 0x01 (2011/11/3  comment by Lu)
**********************************************************************************/
void init_lcd()
{

	P3=0xFF;	
	P1=0xF4;

	IR_value=0x00;	//MR			
	PR_value=0x1B;
	setReg(IR_value,PR_value);
	IR_value=0x01;	//RR	
	PR_value=0x07;
	setReg(IR_value,PR_value);
	IR_value=0x02;	//HNR	
	PR_value=79;		//80bytes	= 640
	setReg(IR_value,PR_value);
	IR_value=0x03;	//DVR		
	PR_value=239;		//239 = 2*240 = 480
	setReg(IR_value,PR_value);
	IR_value=0x04;	// 		
	PR_value=0x11;	//1-1
	setReg(IR_value,PR_value);
	IR_value=0x05;	//SLR		
	PR_value=0x00;
	setReg(IR_value,PR_value);
	IR_value=0x06;	//SUR		
	PR_value=0x00;
	setReg(IR_value,PR_value);
	IR_value=0x07;	//CLR		
	PR_value=0x00;
	setReg(IR_value,PR_value);
	IR_value=0x08;	//CUR	
	PR_value=0x00;
	setReg(IR_value,PR_value);

  P1=0xF4; 									
}

void clear_screen()
{
		
	//unsigned int idata i;	
	//ptr=0;	
	#pragma asm
  mov P1,#0f4h
	mov R2,#150
	mov R1,#0
	MOV a,#0ffh
	mov dptr,#0
	CLRSCN:
 	CLR P3.2
	movx @dptr,a
	;
	inc dptr
	djnz r2,CLRSCN
	djnz r1,CLRSCN
	SETB P3.2
	#pragma endasm
}	