#!/bin/bash
for i in *.cor; do diff "$i" ../A/"${i%.cor}";
echo "OK !";
done
rm *.s
rm *.cor

