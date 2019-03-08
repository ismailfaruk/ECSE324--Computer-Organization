	.text
	
	.equ VGA_PIXEL_BUF_BASE, 0xC8000000
	.equ VGA_CHAR_BUF_BASE, 0xC9000000

	.global VGA_clear_charbuff_ASM
	.global VGA_clear_pixelbuff_ASM
	.global VGA_write_char_ASM
	.global VGA_write_byte_ASM
	.global VGA_draw_point_ASM
		
VGA_clear_pixelbuff_ASM:
	PUSH {R4-R5}	
	MOV R2, #0
	LDR R3, =VGA_PIXEL_BUF_BASE

	MOV R0, #0

PIXEL_LOOPX:
	MOV R1, #0
	ADD R4, R3, R0, LSL #1

PIXEL_LOOPY:
	ADD R5, R4, R1, LSL #10
	
	STRH R2, [R5]
	
	ADD R1, R1, #1
	CMP R1, #240
	BLT PIXEL_LOOPY
	
	ADD R0, R0, #1
	CMP R0, #320
	BLT PIXEL_LOOPX

	POP {R4-R5}
	BX LR

VGA_draw_point_ASM:
	LDR R3, =319
	CMP R0, #0
	BXLT LR
	CMP R1, #0
	BXLT LR
	CMP R0, R3
	BXGT LR
	CMP R1, #239
	BXGT LR
	
	LDR R3, =VGA_PIXEL_BUF_BASE

	ADD R3, R3, R0, LSL #1
	ADD R3, R3, R1, LSL #10

	STRH R2, [R3]

	BX LR
	
VGA_clear_charbuff_ASM:
	PUSH {R4-R5}	
	MOV R2, #0
	LDR R3, =VGA_CHAR_BUF_BASE

	MOV R0, #0
	
CHAR_LOOPX:
	MOV R1, #0
	ADD R4, R3, R0
CHAR_LOOPY:
	ADD R5, R4, R1, LSL #7
	
	STRB R2, [R5]
	
	ADD R1, R1, #1
	CMP R1, #60
	BLT CHAR_LOOPY
	
	ADD R0, R0, #1
	CMP R0, #80
	BLT CHAR_LOOPX
	
	POP {R4-R5}
	BX LR

VGA_write_char_ASM:
	CMP R0, #80			//validation
	BGE VGA_write_end
	CMP R0, #0
	BLT VGA_write_end
	CMP R1, #60
	BGE VGA_write_end
	CMP R1, #0
	BLT VGA_write_end

	PUSH {R4-R5}
	LDR R3, =VGA_CHAR_BUF_BASE
	
	ADD R4, R3, R0		//address calculaion
	ADD R5, R4, R1, LSL #7

	STRB R2, [R5]

	POP {R4-R5}
	BX LR	

VGA_write_byte_ASM:
	CMP R0, #80			//validation
	BGE VGA_write_end
	CMP R0, #0
	BLT VGA_write_end
	CMP R1, #60
	BGE VGA_write_end
	CMP R1, #0
	BLT VGA_write_end
	
	PUSH {R4-R8, LR}
	LDR R3, =VGA_CHAR_BUF_BASE
	LDR R8, =HEX_ASCII
	
	ADD R4, R3, R0		//address calculaion
	ADD R5, R4, R1, LSL #7
	
	AND R6, R2, #0x0F
	AND R7, R2, #0xF0
	LSR R7, R7, #4 
	
	LDRB R6, [R8, R6]
	LDRB R7, [R8, R7]

	STRB R6, [R5, #1]
	STRB R7, [R5] 

	POP {R4-R8, LR}
	BX LR

VGA_write_end:
	BX LR
	
HEX_ASCII:
	.byte 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46
	//      0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F  // 
	.end
	
