#!/bin/bash
sedopt='q;d'
line=$(cat './status')
all=$(cat allfiles | wc -l)
echo "Starting at $line"
while true; do
	file_to_read=$(sed "$line$sedopt" allfiles)
	read -p "@$line/$all"
	less "$file_to_read"
	line="$(expr $line + 1)"
	echo "$line" > status
done
echo "@$line/$all"

