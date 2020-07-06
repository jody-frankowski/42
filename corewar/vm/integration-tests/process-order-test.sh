#!/bin/bash

output=$(../corewar process-order/testorder1.cor process-order/testorder2.cor -a -dump 1657 | grep Aff)

outputoff=$(../../resources/corewar-linux process-order/testorder1.cor process-order/testorder2.cor -a -d 1657 | grep Aff)

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect process order"
fi
