            .text
            .global MAX_2

MAX_2:		CMP R0, R1          // compare R0 to R1
            BXGE LR             // jump to LR if R0 is greater than or equal to R1
            MOV R0, R1          // else move the value of R1 into R0
            BX LR               // return
            .end
