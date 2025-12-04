#!/bin/bash

if [ -e weekly_report.txt ]
then
    echo "Weekly Report Found!"
else
    exit 1
fi

if [ -e EFT_report.txt ]
then
    echo "EFT report found!"
else
    exit 1
fi