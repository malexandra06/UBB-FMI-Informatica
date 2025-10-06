#!/bin/bash

if [ $# -ne 4 ]
then
	echo "Numar incorect de argumente."
	echo "Utilizare: $0 file1 file2 file3 file4"
	exit 1
fi

CRITERIUL1=$(grep -E '\<[aeiouAEIOU][a-zA-Z]*[^AEIOUaeiou]\>' -o $1)
echo "$CRITERIUL1" > $2
CRITERIUL2=$(grep -E '\<[a-zA-Z]*[0-9]{1,}[a-zA-Z]*\>' -o $1)
echo "$CRITERIUL2" > $3
nrCrt1=$(echo "$CRITERIUL1" | wc -l)
nrCrt2=$(echo "$CRITERIUL2" | wc -l)
echo "Numarul de cuvinte care incep cu o vocala si se termina cu o consoana este $nrCrt1" > $4
echo "Numarul de cuvinte care contin un numar este $nrCrt2" >> $4
declare -A vector
for el in $CRITERIUL1
do
	l=$(echo $el | grep -E '[a-zA-Z]' -o | wc -l)
	c=$(echo $el | grep -E '[0-9]' -o | wc -l)
	echo "$el incepe-cu-vocala-se-termina-cu-consoana $l-litere $c-cifre" >> $4
done
for el in $CRITERIUL2
do
        l=$(echo $el | grep -E '[a-zA-Z]' -o | wc -l)
        c=$(echo $el | grep -E '[0-9]' -o | wc -l)
        echo "$el contine-cel-putin-un-numar $l-litere $c-cifre" >> $4
done
exit 0
