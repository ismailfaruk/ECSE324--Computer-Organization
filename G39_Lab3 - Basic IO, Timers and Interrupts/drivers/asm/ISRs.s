	.text
	
	.global A9_PRIV_TIM_ISR
	.global HPS_GPIO1_ISR
	.global HPS_TIM0_ISR
	.global HPS_TIM1_ISR
	.global HPS_TIM2_ISR
	.global HPS_TIM3_ISR
	.global FPGA_INTERVAL_TIM_ISR
	.global FPGA_PB_KEYS_ISR
	.global FPGA_Audio_ISR
	.global FPGA_PS2_ISR
	.global FPGA_JTAG_ISR
	.global FPGA_IrDA_ISR
	.global FPGA_JP1_ISR
	.global FPGA_JP2_ISR
	.global FPGA_PS2_DUAL_ISR

	.global hps_tim0_int_flag
	.global fpga_pb_key0_int_flag
	.global fpga_pb_key1_int_flag
	.global fpga_pb_key2_int_flag
    .global fpga_pb_key3_int_flag
	
hps_tim0_int_flag:
	.word 0x0

fpga_pb_key0_int_flag:
	.word 0x0

fpga_pb_key1_int_flag:
	.word 0x0

fpga_pb_key2_int_flag:
	.word 0x0

fpga_pb_key3_int_flag:
	.word 0x0

A9_PRIV_TIM_ISR:
	BX LR
	
HPS_GPIO1_ISR:
	BX LR
	
HPS_TIM0_ISR:
	PUSH {LR}

	MOV R0, #0x1
	BL HPS_TIM_clear_INT_ASM
	
	LDR R0, =hps_tim0_int_flag
	MOV R1, #1
	STR R1, [R0]
	
	POP {LR}
	BX LR
	
HPS_TIM1_ISR:
	BX LR
	
HPS_TIM2_ISR:
	BX LR
	
HPS_TIM3_ISR:
	BX LR
	
FPGA_INTERVAL_TIM_ISR:
	BX LR
	
FPGA_PB_KEYS_ISR:
    PUSH    {R3, LR}                
    BL      read_PB_edgecap_ASM     // call read_PB_edgecap_ASM
    MOV     R3, R0                  // save return value in R3
    BL      PB_clear_edgecap_ASM    // call PB_clear_edgecap_ASM to clear edgecap register
                                   
    MOV     R1, #1                  
    TST     R3, #0x00000001         		
    LDRNE		R0, =fpga_pb_key0_int_flag 
    STRNE   	R1, [R0]                
    TST     R3, #0x00000002   
    LDRNE   	R0, =fpga_pb_key1_int_flag
    STRNE   	R1, [R0]
    TST     R3, #0x00000004   
    LDRNE   	R0, =fpga_pb_key2_int_flag
    STRNE   	R1, [R0]
    TST     R3, #0x00000008   
    LDRNE   	R0, =fpga_pb_key3_int_flag
    STRNE   	R1, [R0]
    POP     {R3, LR}               
	BX      LR
	
FPGA_Audio_ISR:
	BX LR
	
FPGA_PS2_ISR:
	BX LR
	
FPGA_JTAG_ISR:
	BX LR
	
FPGA_IrDA_ISR:
	BX LR
	
FPGA_JP1_ISR:
	BX LR
	
FPGA_JP2_ISR:
	BX LR
	
FPGA_PS2_DUAL_ISR:
	BX LR
	
	.end
