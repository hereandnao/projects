#!/bin/bash
find ./A/ -name "*.cor" -exec ./msa {} -o {}.s \;
./asm ./A/*.s
rm ./A/*.s
cd B
find . -name "*.cor" -exec diff -s {} ../A/{}.cor \;
cd ..
rm ./A/*.cor.cor
exit 0
