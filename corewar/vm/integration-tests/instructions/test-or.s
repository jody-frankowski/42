.name "test-or"
.comment "test ins_or"

l2:			ld %-484269930, r1
			ld %51069078, r2
			or r1, r2, r3
			zjmp %:display
			ld %485818337, r4
			or r3, r4, r5
			zjmp %:display
			ld %8, r6
			or r5, r6, r7
			zjmp %:display
			ld %1, r8
			add r7, r8, r9
			zjmp %:ok

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1

end:	

