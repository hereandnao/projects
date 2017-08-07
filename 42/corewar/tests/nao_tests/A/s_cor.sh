#!/bin/bash
find . -name "*.cor" -exec ./../msa {} -o ../B/{}.s \;

