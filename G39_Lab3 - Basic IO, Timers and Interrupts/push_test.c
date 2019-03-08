#include <stdio.h>

#include "./drivers/inc/pushbuttons.h"

int main(){
	int check;
		
	while(1){
	if(read_PB_edgecap_ASM() & PB0){
		check = 1;
	}
	printf("%d\n",check);

	}
}
