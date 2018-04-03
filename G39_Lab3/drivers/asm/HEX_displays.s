            .text
            .equ HEX0_3_BASE, 0xFF200020
            .equ HEX4_5_BASE, 0xFF200030
            .global HEX_clear_ASM
            .global HEX_flood_ASM
            .global HEX_write_ASM

HEX_clear_ASM:
			MOV 	R2, #6	//loop counter
			MOV 	R4, #1	//bit identifier
			LDR		R6, =HEX0_3_BASE
			LDR 	R7, =HEX4_5_BASE
			MOV		R3, #0x00
			PUSH	{LR}        
			B		Flag                

HEX_flood_ASM:
			MOV 	R2, #6	//loop counter
			MOV 	R4, #1	//bit identifier
			LDR		R6, =HEX0_3_BASE
			LDR 	R7, =HEX4_5_BASE
			MOV		R3, #0x7F
			PUSH	{LR}        
			B		Flag
        
HEX_write_ASM:
			MOV 	R2, #6	//loop counter
			MOV 	R4, #1	//bit identifier
			LDR		R6, =HEX0_3_BASE
			LDR 	R7, =HEX4_5_BASE
            LDR     R5, =Value
			LDRB	R3, [R5, R1]       
			PUSH	{LR}        
			B		Flag
			            			
Flag:		TST 	R0, R4
			BLNE	Identify
			LSL 	R4, R4, #1
			SUBS	R2, R2, #1
			BEQ		Done
			B		Flag

Done:		POP		{LR}
			BX		LR			

Identify:	CMP		R2, #6
			BEQ		Hex0
			CMP		R2, #5
			BEQ		Hex1
			CMP		R2, #4
			BEQ		Hex2
			CMP		R2, #3
			BEQ		Hex3
			CMP		R2, #2
			BEQ		Hex4
			CMP		R2, #1
			BEQ		Hex5

Hex0:		STRB	R3, [R6]
			BX		LR

Hex1:		STRB	R3, [R6, #1]
			BX		LR

Hex2:		STRB	R3, [R6, #2]
			BX		LR

Hex3:		STRB	R3, [R6, #3]
			BX		LR

Hex4:		STRB	R3, [R7]
			BX		LR

Hex5:		STRB	R3, [R7, #1]
			BX		LR

Value:		.byte   0x3F                // '0'
            .byte   0x06                // '1'
            .byte   0x5B                // '2'
            .byte   0x4F                // '3'
            .byte   0x66                // '4'
            .byte   0x6D                // '5'
            .byte   0x7D                // '6'
            .byte   0x07                // '7'
            .byte   0x7F                // '8'
            .byte   0x67                // '9'
            .byte   0x77                // 'A'
            .byte   0x7F                // 'B'
            .byte   0x39                // 'C'
            .byte   0x3F                // 'D'
            .byte   0x79                // 'E'
            .byte   0x71                // 'F'

			.end
