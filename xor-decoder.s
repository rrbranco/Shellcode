/*
 *  Coded by Rodrigo Rubira Branco <rodrigo@kernelhacking.com>
 *
 *  the %ecx register contains the size of assembly code (shellcode).
 *
 *  pushl    $0x01
 *             ^^
 *             size of assembly code (shellcode)
 *
 *  xorb    $0x00,(%esi)
 *             ^^
 *             number to xor 
 */

    jmp     label3

label1:
    popl    %esi
    pushl   $0x00  /* <-- size of assembly code (shellcode) */
    popl    %ecx
    
label2:
    xorb    $0x00,(%esi) /* <-- number to xor */
    incl    %esi
    loop    label2
    jmp     label4

label3:
    call    label1

label4:

/* assembly code (shellcode) goes here */
