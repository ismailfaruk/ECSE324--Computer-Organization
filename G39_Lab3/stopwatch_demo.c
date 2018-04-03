#include <stdio.h>

#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HPS_TIM.h"

int main(){
	int count0 = 0, count1 = 0, count2 = 0, count3 = 0;
	
	HPS_TIM_config_t hps_tim;

	hps_tim.tim = TIM0|TIM1|TIM2|TIM3;
	hps_tim.timeout = 1000000;
	hps_tim.LD_en = 1;
	hps_tim.INT_en = 1;
	hps_tim.enable = 1;

	HPS_TIM_config_ASM(&hps_tim);

	while(1){
		if(HPS_TIM_read_INT_ASM(TIM0)){
			HPS_TIM_clear_INT_ASM(TIM0);
			if(++count0 == 16)
				count0 = 0;
			HEX_write_ASM(HEX0, count0);
		}

		if(HPS_TIM_read_INT_ASM(TIM1)){
			HPS_TIM_clear_INT_ASM(TIM1);
			if(++count1 == 16)
				count1 = 0;
			HEX_write_ASM(HEX1, count1);
		}
		if(HPS_TIM_read_INT_ASM(TIM2)){
			HPS_TIM_clear_INT_ASM(TIM2);
			if(++count2 == 16)
				count2 = 0;
			HEX_write_ASM(HEX2, count2);
		}
		if(HPS_TIM_read_INT_ASM(TIM3)){
			HPS_TIM_clear_INT_ASM(TIM3);
			if(++count3 == 16)
				count3 = 0;
			HEX_write_ASM(HEX3, count3);
		}
	}
	return 0;
}
