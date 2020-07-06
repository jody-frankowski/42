.name "test-ld"
.comment "test ins_ld"

l2:			ld %48, r1
			zjmp %:display
			ld %-2, r2
			zjmp %:display
			ld %-47, r3
			zjmp %:display
			ld 0, r4
			zjmp %:display
			ld -44, r5
			zjmp %:ok

display:	aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1	

end:
