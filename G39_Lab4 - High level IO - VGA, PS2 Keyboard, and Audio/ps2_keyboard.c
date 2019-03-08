#include <stdio.h>

#include "./drivers/inc/slider_switches.h"
#include "./drivers/inc/vga.h"
#include "./drivers/inc/ps2_keyboard.h"

int main(){
	int sw_input;


	int x = 0;
	int y = 0;
	char *data = (char*) malloc(sizeof(char));
	while(1){

		sw_input = read_slider_switches_ASM();
		if (sw_input > 0){
			VGA_clear_charbuff_ASM();
			x = 0;
			y = 0;
		}
		
		if (read_PS2_data_ASM(data)){
			VGA_write_byte_ASM(x,y,*data);
			x = x + 3;
			if (x >=80) {
				x = 0;
				y++;
				if (y >=60) {
				y = 0;
				VGA_clear_charbuff_ASM();
				}
			}
		}
	}

	return 0;
}
