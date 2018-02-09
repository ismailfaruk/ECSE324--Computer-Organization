			.text
			.global _start

_start:
			LDR R4, =RESULT			// R4 points to result
			LDR R2, [R4, #4]		// R2 holds number of elements in list
			LDR R6, [R4, #4]		// R6 holds number of elements in list
			LDR R9, [R4, #4]		// R9 holds number of elements in list
			ADD R3, R4, #8			// R3 points to the first number
			ADD R7, R4, #8			// R7 points to the first number
			LDR R0, [R3]			// R0 holds first number in the list
			LDR R8, [R7]			// R8 holds first number in the list
			MOV R10, #1				// R10 now holds a numerical 1, to compare with dividend
			MOV R11, #0				// R11 now holds a numerical 0, to find right shift 

TOTAL:		SUBS R2, R2, #1			// decrement the loop counter	
			BEQ DIVIDEND			// end loop if counter has reached 0	
			ADD R3, R3, #4			// R3 points to next number in the list
			LDR R1, [R3]			// R1 holds the next number in the list
			ADD R0, R0, R1			// add number in R0 and R1, store to R0 as total	
			B TOTAL					// branch back to the loop

DIVIDEND:	CMP R10, R9				// compare if R10 = R9
			BEQ AVERAGE				// end dividend if R6 = R9
			ADD R11, R11, #1		// Add value one to R11
			LSL R10, R10, #1		// Shift R10 by one to the left
			B DIVIDEND				// Repeat

AVERAGE:	ASR R0, R0, #1			// Shift total to the right by one
			SUBS R11, R11, #1 		// decrement the loop counter
			BEQ SUBTRACT			// If R7 is zero leave loop
			B AVERAGE				// Else repeat

SUBTRACT:	SUBS R8, R8, R0			// subtraction of average from signal
			STR R8, [R7]			// stores R8(centered value) to R7(address)
			SUBS R6, R6, #1			// decrement the loop counter
			BEQ END					// end loop if counter has reached 0
			ADD R7, R7, #4			// R7 points to next number in the list
			LDR R8, [R7]			// R1 holds the next number in the list	
			B SUBTRACT	

END:		B END					// infinite loop!

RESULT:		.word	0				// memory assigned for result location
N:			.word	8				// number of entries in the list
NUMBERS:	.word	4, 5, 3, 6		// the list data
			.word	1, 8, 2, 9
