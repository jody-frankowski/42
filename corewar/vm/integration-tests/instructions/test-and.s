.name "test-and"
.comment "test ins_and"

l2:			ld %-2, r1
			ld %255, r2
			and r1, r2, r3
			zjmp %:display
			ld %-21458974, r4
			and r3, r4, r5
			zjmp %:display
			ld %-227, r6
			and r5, r6, r7
			zjmp %:ok

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1

end:	

