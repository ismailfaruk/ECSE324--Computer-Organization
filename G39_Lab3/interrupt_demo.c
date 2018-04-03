#include <stdio.h>

#include "./drivers/inc/int_setup.h"
#include "./drivers/inc/ISRs.h"
#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/HPS_TIM.h"

int main(){
	int_setup(1, (int[]){199});

	int count = 0;
	HPS_TIM_config_t hps_tim;
	
	hps_tim.tim = TIM0;
	hps_tim.timeout = 1000000;
	hps_tim.LD_en = 1;
	hps_tim.INT_en = 1;
	hps_tim.enable = 1;

	HPS_TIM_config_ASM(&hps_tim);
	
	while(1){
		if(hps_tim0_int_flag){
			hps_tim0_int_flag = 0;
			if(++count ==15){
				count = 0;
			}
			HEX_write_ASM(HEX0, count);
		}
	}

	return 0;
}
