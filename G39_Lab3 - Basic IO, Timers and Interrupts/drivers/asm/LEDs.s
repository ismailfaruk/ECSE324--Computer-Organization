            .text
            .equ LEDR_BASE, 0xFF200000
            .global read_LEDs_ASM
            .global write_LEDs_ASM

read_LEDs_ASM:
            LDR     R1, =LEDR_BASE      // R1 points to LEDR data register
            LDR     R0, [R1]            // R0 holds the value of LEDR data register
            BX      LR

write_LEDs_ASM:
            LDR     R1, =LEDR_BASE      // R1 points to LEDR data register
            STR     R0, [R1]            // set the value of LEDR data register to R0
            BX      LR

            .end
