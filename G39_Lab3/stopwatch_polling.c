#include <stdio.h>

#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HPS_TIM.h"

int main(){
	int count0 = 0; int count1 = 0;
	int edgecap;
	int flag;

	
	HPS_TIM_config_t hps_tim0;
	HPS_TIM_config_t hps_tim1;

	hps_tim0.tim = TIM0;
	hps_tim0.timeout = 10000;
	hps_tim0.LD_en = 1;
	hps_tim0.INT_en = 1;
	hps_tim0.enable = 1;
	HPS_TIM_config_ASM(&hps_tim0);

	hps_tim1.tim = TIM1;
	hps_tim1.timeout = 5000;
	hps_tim1.LD_en = 1;
	hps_tim1.INT_en = 1;
	hps_tim1.enable = 1;
	HPS_TIM_config_ASM(&hps_tim1);

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

	while(1){
		if(HPS_TIM_read_INT_ASM(TIM1)){
			HPS_TIM_clear_INT_ASM(TIM1);
			
			//PB_clear_edgecap_ASM(PB0 | PB1 | PB2 | PB3);
			edgecap = read_PB_edgecap_ASM();

			if(edgecap & PB0){
				flag = 1;
				PB_clear_edgecap_ASM(PB0 | PB1 | PB2 | PB3);
			}

			if(edgecap & PB1){
				flag = 0;
				PB_clear_edgecap_ASM(PB0 | PB1 | PB2 | PB3);
			}
		
			if(edgecap & PB2){
				flag = 0;
				PB_clear_edgecap_ASM(PB0 | PB1 | PB2 | PB3);
				HEX_write_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5, 0x00);
				count0 = 0;
				minute = 0;
				second = 0;
				milisecond = 0;
			}
		}
		
		
		if (flag ==	1){
			if(HPS_TIM_read_INT_ASM(TIM0)){
				HPS_TIM_clear_INT_ASM(TIM0);
				count0++;
				milisecond = count0 % 100;
				milisecond1 = milisecond % 10;
				milisecond2 = milisecond / 10;
				secondcount = count0 / 100;
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
