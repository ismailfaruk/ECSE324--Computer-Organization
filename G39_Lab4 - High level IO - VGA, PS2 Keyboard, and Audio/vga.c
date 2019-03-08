#include <stdio.h>

#include "./drivers/inc/slider_switches.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/vga.h"

void test_char(){
	int x, y;
	char c = 0;

	for(y=0; y<=59; y++){
		for(x=0; x<=79; x++){
			VGA_write_char_ASM(x,y,c++);
		}
	}
}

void test_byte(){
	int x,y;
	char c = 0;

	for(y=0; y<=59; y++){
		for(x=0; x<=79; x+=3){
			VGA_write_byte_ASM(x,y,c++);
		}
	}
}

void test_pixel(){
	int x,y;
	unsigned short colour = 0;

	for(y=0; y<=239; y++){
		for(x=0; x<=319; x++){
			VGA_draw_point_ASM(x,y,colour++);
		}
	}
}

int main(){
    int sw_input;

	while (1){
		
		// Read Slide Switch
		sw_input = read_slider_switches_ASM();

		if (PB_edgecap_is_pressed_ASM(PB0)){
			if (sw_input == 0){
				//printf("PB0\n");
				test_char();
			}
			else{
				//printf("PB0 and SWITCH\n");	
				test_byte();
			}
		}
		
		if (PB_edgecap_is_pressed_ASM(PB1)){
			//printf("PB1\n");
			test_pixel();
		}
		
		if (PB_edgecap_is_pressed_ASM(PB2)){
			//printf("PB2\n");
			VGA_clear_charbuff_ASM();			
		}

		if (PB_edgecap_is_pressed_ASM(PB3)){
			//printf("PB3\n");
			VGA_clear_pixelbuff_ASM();
		}
		
		PB_clear_edgecap_ASM(PB0 | PB1 | PB2 | PB3);
	}
    return 0;
}
