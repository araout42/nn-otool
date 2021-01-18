#!/bin/sh
clear
GREEN='\033[1;32m\n'
NC='\033[0m'
printf "${GREEN}------------ \tFT_NM\t-----${NC}\n\n\n"
for file in $(find /usr/lib -name "*.so"); do
	echo $file;
	./ft_nm $file > /tmp/a;
	nm $file >/tmp/b 2>/dev/null;
	diff /tmp/a /tmp/b
done
clear
printf "${GREEN}------------ \tFT_OTOOL\t-----${NC}\n\n\n"

for file in $(find /usr/lib -name "*.so"); do
	echo $file;
	./ft_otool $file > /tmp/a;
	otool -t $file >/tmp/b 2>/dev/null;
	diff /tmp/a /tmp/b
done
