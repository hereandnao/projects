#!/bin/bash
find $2 -name "*" -exec $1 `readlink -n {}` \;
