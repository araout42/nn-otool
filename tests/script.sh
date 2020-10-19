#! /bin/zsh

GREEN="\x1b[32m"
RESET="\x1b[0m"
RED="\x1b[31m"
YELLOW="\x1b[33m"

rm -f script_false

BIN=/usr/bin/nm
MYBIN=../ft_nm
for i in $@ ;
do
	diff <( $MYBIN	$OPT $i 2>err) <( $BIN $OPT $i 2>>err)
	if [ $? -ne 0 ]
	then
		echo "$RED$i:\n$RESET"
		echo "$i\n" >> script_false
	elif [ -s err ]
	then
		E=$(cat err)
		echo "$YELLOW$i: $RESET$E"
	else
		echo "$GREEN$i$RESET"
	fi
done

rm -f err
