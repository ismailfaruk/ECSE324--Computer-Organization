#include <stdio.h>

#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HPS_TIM.h"

int main(){
	int count0 = 0, count1 = 0, count2 = 0, count3 = 0;
	
	HPS_TIM_config_t hps_tim0;
		
	hps_tim0.tim = TIM0;
	hps_tim0.timeout = 1000000;
	hps_tim0.LD_en = 1;
	hps_tim0.INT_en = 1;
	hps_tim0.enable = 1;

	HPS_TIM_config_ASM(&hps_tim0);

	HPS_TIM_config_t hps_tim1;
		
	hps_tim1.tim = TIM1;
	hps_tim1.timeout = 500000;
	hps_tim1.LD_en = 1;
	hps_tim1.INT_en = 1;
	hps_tim1.enable = 1;

	HPS_TIM_config_ASM(&hps_tim1);

	HPS_TIM_config_t hps_tim2;
		
	hps_tim2.tim = TIM2;
	hps_tim2.timeout = 250000;
	hps_tim2.LD_en = 1;
	hps_tim2.INT_en = 1;
	hps_tim2.enable = 1;

	HPS_TIM_config_ASM(&hps_tim2);

	HPS_TIM_config_t hps_tim3;
		
	hps_tim3.tim = TIM3;
	hps_tim3.timeout = 125000;
	hps_tim3.LD_en = 1;
	hps_tim3.INT_en = 1;
	hps_tim3.enable = 1;

	HPS_TIM_config_ASM(&hps_tim3);
	
	while(1){
		if (read_PB_edgecap_ASM() & PB0){
			if(HPS_TIM_read_INT_ASM(TIM0)){
				HPS_TIM_clear_INT_ASM(TIM0);
				if(++count0 == 16)
					count0 = 0;
				HEX_write_ASM(HEX0, count0);
			}
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
