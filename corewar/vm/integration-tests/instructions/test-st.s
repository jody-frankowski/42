.name "test-st"
.comment "test ins_st"

l2:			ld %-65536, r1
			st r1, r2
			st r2, 373
			ld %3229816, r3
			st r3, 366
			ld 359, r4
			ld %49, r5
			sub r4, r5, r6
			zjmp %:ok

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1	

end:
