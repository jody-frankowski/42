#!/bin/bash

#TEST INS_LIVE
nblive=$(../corewar instructions/test-live.cor -a | grep "alive" | wc -l)

nbliveoff=$(../../resources/corewar-linux instructions/test-live.cor -v 1 | grep "alive" | wc -l)

if [ $nblive -ne $nbliveoff ]; then
	echo "Incorrect live instruction"
fi

#TEST INS_LD
output=$(../corewar instructions/test-ld.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-ld.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect ld instruction"
fi

#TEST INS_ST
output=$(../corewar instructions/test-st.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-st.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect st instruction"
fi

#TEST INS_ADD
output=$(../corewar instructions/test-add.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-add.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect add instruction"
fi

#TEST INS_SUB
output=$(../corewar instructions/test-sub.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-sub.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect sub instruction"
fi

#TEST INS_AND
output=$(../corewar instructions/test-and.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-and.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect and instruction"
fi

#TEST INS_OR
output=$(../corewar instructions/test-or.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-or.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect or instruction"
fi

#TEST INS_XOR
output=$(../corewar instructions/test-xor.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-xor.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect xor instruction"
fi

#TEST INS_ZJMP
output=$(../corewar instructions/test-zjmp.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-zjmp.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect zjmp instruction"
fi

#TEST INS_LDI
output=$(../corewar instructions/test-ldi.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-ldi.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect ldi instruction"
fi

#TEST INS_STI
output=$(../corewar instructions/test-sti.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-sti.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect sti instruction"
fi

#TEST INS_FORK
output=$(../corewar instructions/test-fork.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-fork.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect fork instruction"
fi

#TEST INS_LLD
output=$(../corewar instructions/test-lld.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-lld.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect lld instruction"
fi

#TEST INS_LLDI
output=$(../corewar instructions/test-lldi.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-lldi.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect lldi instruction"
fi

#TEST INS_LFORK
output=$(../corewar instructions/test-lfork.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-lfork.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect lfork instruction"
fi

#TEST INS_AFF
output=$(../corewar instructions/test-aff.cor -a | grep "Aff")

outputoff=$(../../resources/corewar-linux instructions/test-aff.cor -a | grep "Aff")

if [ "$output" != "$outputoff" ]; then
	echo "Incorrect aff instruction"
fi
