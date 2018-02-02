				.text
				.global _start

_start:
				LDR R4, =RESULT			//R4 points to result
				LDR R2, [R4, #4]		//R2 holds number of elements in list
				SUBS R2, R2, #1 		//R2 holds n-1
				MOV R6, R2				//R6 now also holds n-1
				ADD R3, R4, #8			//R3 now points to first number
				LDR R0, [R3]			//R0 holds first number in the list
				ADD R5, R4, #12			//R5 points to second number
				LDR R1, [R5]			//R1 holds second number in the list
				MOV R7, R6				//R7 holds length of current looping


OUTSIDELOOP:	SUBS R2, R2, #1			//Decrement R2
				BEQ END					//If R2 now zero, should be sorted
				SUBS R7, R7, #1 		//decrement length of current looping
				MOV R6, R7				//load current loop length into R6
				B INSIDELOOP			//enter inside loop


INSIDELOOP:		SUBS R6, R6, #1			//decrament current loop length
				BEQ OUTSIDELOOP
				CMP R1, R0
				BLT SWITCH
				ADD R5, R5, #4
				LDR R1, [R5]			//R1 holds second number in the list
				B INSIDELOOP

SWITCH:			MOV R9, R1
				MOV R1, R0
				MOV R0, R9
				STR R0, [R3]
				STR R1, [R5]
				ADD R5, R5, #4
				ADD R3, R3, #4
				LDR R0, [R3]
				LDR R1, [R5]
				B INSIDELOOP


END: 			B END

RESULT:			.word	0			// memory assigned for result location
N:				.word	8			// number of entries in the list
NUMBERS:		.word	4, 5, 3, 6	// the list data
				.word	1, 8, 2, 9