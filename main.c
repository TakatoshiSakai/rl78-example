#include "iodefine.h"
#include "iodefine_ext.h"
#include <stdint.h>
#include "r_cg_cgc.h"
#include "r_cg_lcd.h"
#include "lcd_panel.h"
#include "r_cg_userdefine.h"

int main (void) { 
	volatile uint32_t i = LCD_DELAY;

	Init_Display_Panel();
	while (--i)
	{
		LCD_On();
	}
	SEG8=0x1;
	//blink segment
	while(1)
    {
		i = 500000;
		while(i--) ;
		SEG8  ^=0xff;
		
	}
	return 0;
}
