.name "test-lld"
.comment "test ins_lld"

l2:			ld %48, r1
			zjmp %:display
			lld %-2, r2
			zjmp %:display
			lld %-47, r3
			zjmp %:display
			lld 65536, r4
			zjmp %:display
			lld -44, r5
			zjmp %:ok

display:	aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1	

end:
