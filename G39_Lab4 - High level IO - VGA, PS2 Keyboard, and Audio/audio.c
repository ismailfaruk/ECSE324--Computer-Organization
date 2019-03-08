#include <stdio.h>

#include "./drivers/inc/audio.h"

int main(){
	int	frequency = 100;
	int sampling_rate = 48000;
	int half_cycle_samples = sampling_rate/(frequency * 2);
	while(1){
		int i;
		for(i = 0; i < half_cycle_samples;){
			if(write_audio_data_ASM(0x00FFFFFF)){
				i++;
			}
		}

		for(i = 0; i < half_cycle_samples;){
			if(write_audio_data_ASM(0x00000000)){
				i++;
			}
		}
	}
	return 0;
}