#!/bin/bash

CORRECT=$1
PROGRAM=$2
EXIT=
sort $1 > ${CORRECT}_sorted.txt
sort $2 > ${PROGRAM}_sorted.txt

diff ${CORRECT}_sorted.txt ${PROGRAM}_sorted.txt

EXIT=$?

rm ${CORRECT}_sorted.txt
rm ${PROGRAM}_sorted.txt

exit $EXIT