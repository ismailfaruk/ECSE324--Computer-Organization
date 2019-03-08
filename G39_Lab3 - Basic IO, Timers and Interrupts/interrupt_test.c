#include <stdio.h>

#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HPS_TIM.h"
#include "./drivers/inc/int_setup.h"
#include "./drivers/inc/ISRs.h"

int main(){
	int_setup(2, (int[]){73, 199});
	int flag; 
	enable_PB_INT_ASM(PB0 | PB1 | PB2 | PB3);

	while(1){	

		if(fpga_pb_key0_int_flag){
			flag = 1;
			printf("%d\n",fpga_pb_key0_int_flag);
			printf("%d\n",flag);
			
			//fpga_pb_key0_int_flag = 0;
		}
		printf("%d\n",flag);
/*
		if(fpga_pb_key1_int_flag){
			flag = 0;
			fpga_pb_key1_int_flag = 0;
		}
	
		if(fpga_pb_key2_int_flag){
			flag = 0;
			fpga_pb_key2_int_flag = 0;
			HEX_write_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5, 0x00);
			count = 0;
			milisecond = 0;
			minute = 0;
			second = 0;
		}
*/
	}	
}
