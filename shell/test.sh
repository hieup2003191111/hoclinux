#!/bin/bash
file_path="hehe.txt"
if [ -f "$file_path" ]; then
	echo "$file_path found"
else
	echo "$file_path not found"
	touch "$file_path"
	echo "$file_path is created"
fi
