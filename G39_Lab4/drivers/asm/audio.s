	.text
	
	.equ audio_Fifospace_base, 0xFF203044
	.equ audio_leftdata_base, 0xFF203048
	.equ audio_rightdata_base, 0xFF20304C
	.global write_audio_data_ASM

write_audio_data_ASM:
	LDR R1, =audio_Fifospace_base 
	LDRB R2, [R1, #2]
	LDRB R3, [R1, #3]

	CMP R2, #0
	BEQ	write_audio_end
	CMP R3, #0
	BEQ write_audio_end

	LDR R2, =audio_leftdata_base
	STR R0, [R2]
	LDR R3, =audio_rightdata_base
	STR R0, [R3]

	MOV R0, #1
	BX LR

write_audio_end:
	MOV R0, #0
	BX LR

	.end
