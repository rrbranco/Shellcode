# Just to be quickly
# Rodrigo Rubira Branco <rodrigo@kernelhacking.com>

DECODERS="add-decoder.s inc-decoder.s rol-decoder.s sub-decoder.s dec-decoder.s not-decoder.s shuffle-decoder.S xor-decoder.s"
ENCODERS="add-encoder.c inc-encoder.c rol-encoder.c sub-encoder.c dec-encoder.c not-encoder.c shuffle-encoder.c xor-encoder.c"

if ! test -z $1
then
	for i in `ls`; do if [ -x $i ]; then rm $i; fi; done
	rm -f *.o
	exit
fi

for i in $DECODERS
do
	extension=`echo $i |grep .S`
	
	if test -z $extension
	then
		# .s file
		i=`echo $i |cut -f1 -d"."`
		as -o $i.o $i.s
	else
		# .S file
		nasm -f elf $i
	fi
done

for i in $ENCODERS
do
	i=`echo $i |cut -f1 -d"."`
	gcc -o $i $i.c
done
