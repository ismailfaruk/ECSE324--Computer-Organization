#include "./drivers/inc/vga.h"
#include "./drivers/inc/ISRs.h"
#include "./drivers/inc/audio.h"
#include "./drivers/inc/HPS_TIM.h"
#include "./drivers/inc/int_setup.h"
#include "./drivers/inc/wavetable.h"
#include "./drivers/inc/ps2_keyboard.h"

//global variables declaration and definition

double C_FREQUENCY = 130.813;
double D_FREQUENCY = 146.832;
double E_FREQUENCY = 164.814;
double F_FREQUENCY = 174.614;
double G_FREQUENCY = 195.998;
double A_FREQUENCY = 220.000;
double B_FREQUENCY = 246.942;
double C2_FREQUENCY = 261.626;

int C_NOTE_KEY = 0x1C;
int D_NOTE_KEY = 0x1B;
int E_NOTE_KEY = 0x23;
int F_NOTE_KEY = 0x2B;
int G_NOTE_KEY = 0x3B;
int A_NOTE_KEY = 0x42;
int B_NOTE_KEY = 0x4B;
int C2_NOTE_KEY = 0x4C;
int break_code = 0xF0;
int Volume_UP_KEY =	0x79;
int Volume_DOWN_KEY = 0x7B;


int sampling_frequency = 48000;
static int amplitude = 5;

//function for extracting signal values from the wave table
int signal(double frequency, int t){
	int pre_index = (int)(frequency * t);
	int index_int =  pre_index % sampling_frequency;	// find the integer remainder
	double remainder = (frequency * t) - pre_index;		// find the decimal remainder
	int result = (1-remainder)*sine[index_int] + remainder * sine[index_int + 1];
	return result;
}

//arrays for storing generated waves
int note1[48000];		//note C key A
int note2[48000];		//note D key S
int note3[48000];		//note E key D
int note4[48000];		//note F key F
int note5[48000];		//note G key J
int note6[48000];		//note A key K
int note7[48000];		//note B key L
int note8[48000];		//note C key ;

//function to generate signals and store to array
void wave_generator(){
	printf("wave gen called\n");
	int t;
	for(t = 0; t < sampling_frequency; t++){
		note1[t] = signal(C_FREQUENCY,t);
		note2[t] = signal(D_FREQUENCY,t);
		note3[t] = signal(E_FREQUENCY,t);
		note4[t] = signal(F_FREQUENCY,t);
		note5[t] = signal(G_FREQUENCY,t);
		note6[t] = signal(A_FREQUENCY,t);
		note7[t] = signal(B_FREQUENCY,t);
		note8[t] = signal(C2_FREQUENCY,t);
	}
	printf("wave gen finished\n");
}


int main() {
	//declare and define varialbes
	int_setup(3, (int []) {199, 200, 201});		//turning on interrupts for HPS Timer 1, 2, 3
	int t_note1 = 0;
	int t_note2 = 0;
	int t_note3 = 0;
	int t_note4 = 0;
	int t_note5 = 0;
	int t_note6 = 0;
	int t_note7 = 0;
	int t_note8 = 0;


	int total_sample;

	char *data;
 
	int input_key;	//int variable for keyboard input
	
	//define flags for notes
	int note1_flag = 0;
	int note2_flag = 0;
	int note3_flag = 0;
	int note4_flag = 0;
	int note5_flag = 0;
	int note6_flag = 0;
	int note7_flag = 0;
	int note8_flag = 0;
	
	printf("variables done\n");
	//audio timer

	HPS_TIM_config_t hps_tim0;

    hps_tim0.tim = TIM0;
    hps_tim0.timeout = 20;	//21	//microseconds, calculated from (1/48000) to feed the codec each sample at the rate each sample is processed 
    hps_tim0.LD_en = 1;
    hps_tim0.INT_en = 1;
    hps_tim0.enable = 1;

	HPS_TIM_config_ASM(&hps_tim0);		//Configure timer

	printf("timer 1 done\n");

	//keyboard timer
    HPS_TIM_config_t hps_tim1;
    hps_tim1.tim = TIM1;
    hps_tim1.timeout = 1000;	//10000	//microseconds
    hps_tim1.LD_en = 1;
    hps_tim1.INT_en = 1;
    hps_tim1.enable = 1;

	HPS_TIM_config_ASM(&hps_tim1);		//Configure timer

	
/*	//VGA timer
    HPS_TIM_config_t hps_tim2;
    hps_tim2.tim = TIM2;
    hps_tim2.timeout = 100000;	//100000	//microseconds
    hps_tim2.LD_en = 1;
    hps_tim2.INT_en = 1;
    hps_tim2.enable = 1;

    //HPS_TIM_config_ASM(&hps_tim2);      //Configure timer
*/
	//VGA_clear_pixelbuff_ASM();		//clear the screen at first


	//printf("timer 2 done\n");

	//printf("wave gen start\n");
 	wave_generator();		//generated wave and store into array
	printf("all start\n");

	while(1) {
		//printf("while loop started\n");
		//KEYBOARD FUNCTION USING TIMER INTERRUPT
		if (read_ps2_data_ASM(data)){
			input_key = *data;
			if (input_key != break_code){
				//identifying which key was pressed
				if (input_key == C_NOTE_KEY){note1_flag = 1;}
			}
			if (input_key == break_code){
				read_ps2_data_ASM(data);
				input_key = *data;
				//identifying which key was released
				if (input_key == C_NOTE_KEY){
					note1_flag = 0;
					t_note1 = 0;
				}
			}
		}
		if(note1_flag){total_sample += amplitude * note1[t_note1 % (int)(sampling_frequency/C_FREQUENCY)];}	
		if(audio_write_data_ASM(total_sample, total_sample)){
			if(note1_flag){t_note1++;}
		}
		
		//printf("%d,\n",note1_flag);
		//printf("%d,\n",t_note1);
		total_sample = 0;
	}		
	return 0;
}
