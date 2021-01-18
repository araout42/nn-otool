#!/bin/sh
clear
GREEN='\033[1;32m\n'
NC='\033[0m'
printf "${GREEN}------------ \tFT_NM\t-----${NC}\n\n\n"
#for file in $(find /usr/bin); do
#	echo $file;
#	./ft_nm $file > /tmp/a 2> /dev/null;
#	nm $file >/tmp/b 2>/dev/null;
#	diff /tmp/a /tmp/b
#done
clear
printf "${GREEN} ----------- \tFT_OTOOL\t ---------${NC}"
for file in $(find /usr/bin); do
	echo $file;
	./ft_otool $file > /tmp/a 2>/dev/null;
	otool -t $file > /tmp/b 2>/dev/null;
	diff /tmp/a /tmp/b
done
