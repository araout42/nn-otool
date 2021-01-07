#!/bin/sh
for file in $(find /usr/share -name "*.o" 2>/dev/null); do
	echo $file;
	./ft_nm $file > /tmp/a 2>/dev/null;
	nm $file >/tmp/b 2>/dev/null;
	diff /tmp/a /tmp/b
done
