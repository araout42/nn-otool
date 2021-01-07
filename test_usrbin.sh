#!/bin/sh
for file in $(find /usr/bin); do
	echo $file;
	./ft_nm $file > /tmp/a 2> /tmp/a;
	nm $file >/tmp/b 2>/tmp/b;
	diff /tmp/a /tmp/b
done
