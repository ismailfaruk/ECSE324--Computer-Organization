            .text
            .global _start

_start:
            MOV R0, #0x00000001     // move an identifiable value into R0
            MOV R1, #0x00000002     // move an identifiable value into R1
            MOV R2, #0x00000003     // move an identifiable value into R2

STACK_PUSH:
            STMDB SP!, {R0}         // push R0 onto the stack
            STMDB SP!, {R1}         // push R1 onto the stack
            STMDB SP!, {R2}         // push R2 onto the stack

STACK_POP:
            LDMIA SP!, {R0 - R2}    // POP {R0 - R2}

END:
            B END                   // infinite loop!
