#include<reg51.h>
#include <intrins.h>  
#define byte unsigned char
/*****************************
extern
*****************************/
extern void clear_screen();
extern void init_lcd();
extern void print_byte(byte a,byte xdata *ptr);		   //²Õ»y°Æµ{¦¡ assembly subroutine
/*******************************/
void main(void)										
{
	byte xdata *ptr;
	init_lcd();
	clear_screen();

	ptr=900;
	print_byte(0x55,ptr);

	for(;;)
	{	
		_nop_();
	}
}
	