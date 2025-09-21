#!/bin/bash

# Install if needed: sudo apt install pv
clear
name=${1:-"Hello, world!"}
echo "$name" | pv -qL 10
echo