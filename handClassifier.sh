#!/usr/bin/env bash
# pass in file to bash script
# read first line
# replace " " and "%" with "."
# rewrite first line
# Test for column names

if [[ $# -eq 0 ]]
  then
    echo "Missing <file>"
    exit 1
fi

infile=$1
line=$(head -n 1 ${infile})
newLine=$(echo ${line}| tr '.' '_' | tr '%' '_' | tr ' ' '_')
sed -i "1 s/^.*$/$newLine/" ${infile}
head -n 1 ${infile}
