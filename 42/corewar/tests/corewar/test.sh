#!/bin/bash
./reg.py $1 && ./reg_1.py $1 && ./compare.py $1
rm txt* _txt*
exit 0
