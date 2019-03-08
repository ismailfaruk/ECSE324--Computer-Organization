	.text
	
	.equ PS2_data_base, 0xFF200100
	.equ PS2_control_base, 0xFF200104
	.global read_PS2_data_ASM
	
read_PS2_data_ASM:
	LDR	R1, =PS2_data_base
	LDRB R2, [R1, #1]
	LSR R2, R2, #7		//extracted RVALID to R2
	CMP R2, #1
	BEQ VALID
	MOV R0, #0
	BX LR

VALID:
	LDRB R2, [R1]
	STRB R2, [R0]
	MOV R0, #1
	BX LR

	.end
