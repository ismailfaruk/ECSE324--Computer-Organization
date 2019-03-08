            .text
            .equ SW_BASE, 0xFF200040
            .global read_slider_switches_ASM

read_slider_switches_ASM:
            LDR     R1, =SW_BASE        // R1 points to SW data register
            LDR     R0, [R1]            // R0 holds the value of SW data register
            BX      LR

            .end