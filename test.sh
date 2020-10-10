#!/bin/sh
for file in $(find /usr/bin); do
	echo $file;
	./ft_nm $file > /tmp/a;
	nm $file >/tmp/b 2>/dev/null;
	diff /tmp/a /tmp/b
done
