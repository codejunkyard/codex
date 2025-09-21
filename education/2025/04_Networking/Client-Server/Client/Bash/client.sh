#!/bin/bash

#curl -L "http://localhost:8080/?player=Sonic&increment=9"

for i in {1..5}; do
    curl -X POST http://localhost:8080/ \
        -H "Content-Type: application/json" \
        -d "{\"player\": \"Sonic\", \"increment\": $i}"

    echo ""   # this prints a newline
done