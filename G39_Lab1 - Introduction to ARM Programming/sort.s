			.text
			.global _start

_start:
			LDR R4, =RESULT		// R4 points to the result location
			LDR R6, [R4, #4]	// R6 holds the number of elements in the list
				
LOOP_ONE:	MOV R7, R6		 	// R7 holds loop couner for LOOP_TWO
			SUBS R6, R6, #1		// decrement the loop counter of LOOP_ONE
			BEQ END				// end loop if counter has reached 0
			ADD R3, R4, #8		// R3 points to the first number
			LDR R0, [R3]		// R0 holds the first number in the list
			ADD R5, R4, #12		// R5 points to second number
			LDR R1, [R5]		// R1 holds second number in the list
			B LOOP_TWO			// branch to LOOP_TWO
			
LOOP_TWO:	SUBS R7, R7, #1		// decrement current loop length
			BEQ LOOP_ONE		// end loop if counter has reached 0
			CMP R1, R0			// check if R1 is less than the R0
			BLT SWAP			// branch to SWAP if R1 is less than R0
			B SHIFT				// branch to SHIFT
			
SWAP:		MOV R9, R1			// R9 holds content in R1	
			MOV R1, R0			// R1 holds content in R0	
			MOV R0, R9			// R0 holds data in R9, swapped data in R1 and R0	
			STR R0, [R3]		// store R0 in the location R3 is pointing to
			STR R1, [R5]		// store R1 in the location R5 is pointing to	
			B SHIFT				// branch to SHIFT

SHIFT:		ADD R3, R3, #4		// R3 points to the next number	
			LDR R0, [R3]		// R0 holds the number R3 is now pointing to
			ADD R5, R5, #4		// R5 points to the next number
			LDR R1, [R5]		// R1 holds the number R5 is now pointing to  	
			B LOOP_TWO			// branch to LOOP_TWO

END: 		B END				// infinite loop!

RESULT:		.word	0			// memory assigned for result location
N:			.word	7			// number of entries in the list
NUMBERS:	.word	4, 5, 3, 6	// the list data
			.word	1, 8, 2 
