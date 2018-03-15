            .text
            .equ HEX0_3_BASE, 0xFF200020
            .equ HEX4_5_BASE, 0xFF200030
            .global HEX_clear_ASM
            .global HEX_flood_ASM
            .global HEX_write_ASM

HEX_clear_ASM:
            MOV     R1, #0x00           // R1 holds 0x00 to clear the display to 0
            PUSH    {LR}                // save the value of LR
            BL      _HEX_impl           // jump to _HEX_impl
            POP     {LR}                // restore the value of LR
            BX      LR                  // jump to LR

HEX_flood_ASM:
            MOV     R1, #0x7F           // R1 holds 0x7F to clear the display to 1
            PUSH    {LR}                // save the value of LR
            BL      _HEX_impl           // jump to _HEX_impl
            POP     {LR}                // restore the value of LR
            BX      LR                  // jump to LR

HEX_write_ASM:
            CMP     R1, #0x00           // confirm that R1 is between 0x00 and 0x0F,
            BLT     _ERR                // otherwise jump to _ERR
            CMP     R1, #0x0F
            BLE     _HEX_write_ASM_unsafe
_ERR:
            //
            // An error value (e.g. 1) should be returned here, but since
            // the Lab #3 specification shows this routine's return value
            // to be `void`, we'll just ignore the error.
            //

            BX      LR                  // jump to LR

_HEX_write_ASM_unsafe:
            LDR     R2, =_H_DISPLAY     // R2 points to _H_DISPLAY
            LDRB    R1, [R2, R1]        // R1 holds the HEX display value
            PUSH    {LR}                // save the value of LR
            BL      _HEX_impl           // jump to _HEX_impl
            POP     {LR}                // restore the value of LR
            BX      LR                  // jump to LR

//
// _HEX_impl:
//
// R0 = the bitwise-or of the HEX displays to modify
// R1 = the value to which the HEX displays should bet set
//

_HEX_impl:
            PUSH    {R4 - R9, LR}       // save the current state of the registers
            LDR     R9, =HEX4_5_BASE    // R9 points to HEX data register 2
            LDR     R8, =HEX0_3_BASE    // R8 points to HEX data register 1
            LDR     R7, [R9]            // R7 holds the HEX (register 2) value
            LDR     R6, [R8]            // R6 holds the HEX (register 1) value
            MOV     R5, #0x00000020     // R5 holds the current HEX index one-hot-encoding
            MOV     R4, #6              // R4 holds the current HEX index
_LOOP:
            SUBS    R4, R4, #1          // decrement the loop counter
            BMI     _DONE               // jump to _DONE if R4 is negative
            TST     R5, R0              // check if one-hot-encoded R5 (bit) is set in R0
            BEQ     _JUMP               // jump to _JUMP if the bit is _not_ set

            // Jump table

            CMP     R4, #6
            ADDLS   PC, PC, R4, LSL #2
            B       _DONE
            B       _H0
            B       _H1
            B       _H2
            B       _H3
            B       _H4

            //
            // Micro-optimization:
            //
            // We can save a jump instruction (i.e. `B _H5`) here,
            // since the jump table will cause execution to branch directly
            // to _H5 if R4 is set to 5.
            //

_H5:
            BIC     R7, R7, #0x00007F00 // clear HEX5 value in R7 to 0
            ORR     R7, R7, R1, LSL #8  // set HEX5 value in R7 to the value in R1
            B       _JUMP               // jump to _JUMP
_H4:
            BIC     R7, R7, #0x0000007F
            ORR     R7, R7, R1, LSL #0
            B       _JUMP
_H3:
            BIC     R6, R6, #0x7F000000
            ORR     R6, R6, R1, LSL #24
            B       _JUMP
_H2:
            BIC     R6, R6, #0x007F0000
            ORR     R6, R6, R1, LSL #16
            B       _JUMP
_H1:
            BIC     R6, R6, #0x00007F00
            ORR     R6, R6, R1, LSL #8
            B       _JUMP
_H0:
            BIC     R6, R6, #0x0000007F
            ORR     R6, R6, R1, LSL #0

_JUMP:
            LSR     R5, R5, #1          // shift R5 right by 1
            B       _LOOP               // jump to _LOOP
_DONE:
            STR     R6, [R8]            // store HEX0-3 data to R8
            STR     R7, [R9]            // store HEX4-5 data to R9
            POP     {R4 - R9, LR}       // restore registers to their previous state
            BX      LR                  // jump to LR

//
// _H_DISPLAY:
//
// A mapping of hexadecimal values to their corresponding
// representation on the DE1-SoC's HEX display.
//

_H_DISPLAY:
            .byte   0x3F                // '0'
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
