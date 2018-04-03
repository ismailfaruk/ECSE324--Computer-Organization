#include <stdio.h>

#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HPS_TIM.h"
#include "./drivers/inc/int_setup.h"
#include "./drivers/inc/ISRs.h"

int main(){
	int_setup(2, (int[]){73, 199});

	int count = 0;
	
	int edgecap;
	int flag;

	HPS_TIM_config_t hps_tim0;

	hps_tim0.tim = TIM0;
	hps_tim0.timeout = 10000;
	hps_tim0.LD_en = 1;
	hps_tim0.INT_en = 1;
	hps_tim0.enable = 1;

	HPS_TIM_config_ASM(&hps_tim0);

	int milisecond;
	int milisecond1;
	int milisecond2;
	int secondcount;
	int second;
	int second1;
	int second2;
	int minute;
	int minute1;
	int minute2;
	
	enable_PB_INT_ASM(PB0 | PB1 | PB2 | PB3);
	
	while(1){

		if(fpga_pb_key0_int_flag){
			flag = 1;
			fpga_pb_key0_int_flag = 0;
		}

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

		if (flag == 1){
			if(hps_tim0_int_flag){
				hps_tim0_int_flag = 0;
				count++;
				milisecond = count % 100;
				milisecond1 = milisecond % 10;
				milisecond2 = milisecond / 10;
				secondcount = count / 100;
				minute = secondcount / 60;
				minute1 = minute % 10;
				minute2 = minute / 10;
				second = secondcount % 60;
				second1 = second % 10;
				second2 = second / 10;
				HEX_write_ASM(HEX0, milisecond1);
				HEX_write_ASM(HEX1, milisecond2);
				HEX_write_ASM(HEX2, second1);
				HEX_write_ASM(HEX3, second2);
				HEX_write_ASM(HEX4, minute1);
				HEX_write_ASM(HEX5, minute2);
			}
		}
	}
	return 0;
}
