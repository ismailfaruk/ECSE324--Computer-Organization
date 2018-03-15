			.text
			.global _start

_start:
			LDR R4, =RESULT		// R4 points to the result location
			LDR R2, [R4, #4]	// R2 holds the number of elements in the list
			ADD R3, R4, #8		// R3 points to the first number
			LDR R0, [R3]		// R0 holds the first number in the list, starting min
			LDR R5, [R3]		// R5 holds the first number in the list, starting max

LOOP:		SUBS R2, R2, #1		// decrement the loop counter
			BEQ DONE			// end loop if counter has reached 0
			ADD R3, R3, #4		// R3 points to next number in the list
			LDR R1, [R3]		// R1 holds the next number in the list
			CMP R1, R0			// check if R1 is less than the minimum
			BLT Min				// branch to Min if R0 is less than R1
			CMP R5, R1			// check if it is greater than the maximum
			BGE LOOP			// if no, branch back to the loop
			MOV R5, R1			// if yes, update the curent max
			B LOOP				// branch back to the loop

Min:		MOV R0, R1			// if yes, update minimum value
			B LOOP				// branch to Loop

DONE:		SUBS R6, R5, R0		// substraction, max - min
			LSR R7, R6, #2 		// divide by 4
			STR R7, [R4]		// store R7 in R4

END:		B END				// infinite loop!

RESULT:		.word	0			// memory assigned for result location
N:			.word	7			// number of enties in the lis
NUMBERS:	.word	4, 5, 3, 6	//the list data
			.word	1, 8, 2
