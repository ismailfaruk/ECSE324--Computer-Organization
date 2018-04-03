#include <stdio.h>

#include "./drivers/inc/LEDs.h"
#include "./drivers/inc/slider_switches.h"
#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/pushbuttons.h"

int main(){
    int sw_input;
	int sw_data;
	int pb_data;

	while (1){
		// Read Slide Switch
		sw_input = read_slider_switches_ASM();

		// Turn on LEDs per flipped switch
        //write_LEDs_ASM(sw_input);

		// Read Push Button
		pb_data = read_PB_data_ASM();
		
		//Clear Display if SW9 is flipped
		if ((sw_input & 0x200) == 0x200){
			HEX_clear_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5);
		}
		else {
		
		//The last 4 switch selection operation
        sw_data = sw_input & 0x0F;
		
        //Switch on HEX displays for each corresponding button that is pressed
		HEX_write_ASM(pb_data, sw_data);
				
        // HEX4 and HEX5 are flooded by default
		HEX_flood_ASM(HEX4 | HEX5);
		}

		//HEX_flood_ASM(sw_input);

		//HEX_write_ASM(HEX1, 5); 
		//HEX_flood_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5);
		//HEX_clear_ASM(HEX0 | HEX1);
		
		//continue;
		    
		//else {HEX_flood_ASM(HEX1);}
	}
    return 0;
}
