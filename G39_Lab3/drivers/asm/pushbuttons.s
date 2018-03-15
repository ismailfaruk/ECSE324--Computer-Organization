            .text
            .equ KEY_BASE, 0xFF200050
            .global read_PB_data_ASM
            .global read_PB_data_is_pressed_ASM
            .global read_PB_edgecap_ASM
            .global PB_edgecap_is_pressed_ASM
            .global PB_clear_edgecap_ASM
            .global enable_PB_INT_ASM
            .global disable_PB_INT_ASM

read_PB_data_ASM:
            LDR     R1, =KEY_BASE       // R1 points to KEY data register
            LDR     R0, [R1]            // R0 holds the value of KEY data register
            BX      LR

read_PB_data_is_pressed_ASM:
            LDR     R2, =KEY_BASE       // R2 points to KEY data register
            LDR     R1, [R2]            // R1 holds the value of KEY data register
            AND     R0, R1, R0          // perform bitwise-and on R1 and PB mask to get only the
                                        // bits we care about
            BX      LR

read_PB_edgecap_ASM:
            LDR     R1, =KEY_BASE       // R1 points to KEY data register
            LDR     R0, [R1, #12]       // R0 holds the value of KEY edgecapture register
            BX      LR

PB_edgecap_is_pressed_ASM:
            LDR     R2, =KEY_BASE       // R2 points to KEY data register
            LDR     R1, [R2, #12]       // R1 holds the value of KEY edgecapture register
            AND     R0, R1, R0          // perform bitwise-and on R1 and PB mask to get only the
                                        // bits we care about
            BX      LR

PB_clear_edgecap_ASM:
            LDR     R1, =KEY_BASE       // R1 points to KEY data register
            STR     R0, [R1, #12]       // place R0 in KEY edgecapture register
            BX      LR

enable_PB_INT_ASM:
            LDR     R2, =KEY_BASE       // R2 points to KEY data register
            LDR     R1, [R2, #8]        // R1 holds the value of KEY interrupt register
            ORR     R1, R1, R0          // perform bitwise-or on R1 and PB mask to get only the
                                        // bits we want to enable interrupts for
            STR     R1, [R2, #8]        // place R1 in KEY interrupt register
            BX      LR

disable_PB_INT_ASM:
            LDR     R2, =KEY_BASE       // R2 points to KEY data register
            LDR     R1, [R2, #8]        // R1 holds the value of KEY interrupt register
            BIC     R1, R1, R0          // perform bit-clear on R1 using PB mask to get only the
                                        // bits we want to interrupts to be enabled for
            STR     R1, [R2, #8]        // place R1 in KEY interrupt register
            BX      LR

            .end
