.name "champ1"
.comment "champ1"


test:	ld %48, r2
		ld %51, r3
		ld %52, r4
		ld %51, r5
		ld %-51, r6
		add r5, r6, r7
		fork %:pr1
		live %0
		fork %:l2
		live %0
		aff r2
		zjmp%:l2

pr2:	live %0
		aff r4
		zjmp%:l2

pr1:	live %0
		fork %:pr2
		live %0
		aff r3

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
