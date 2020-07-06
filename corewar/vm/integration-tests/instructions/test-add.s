.name "test-add"
.comment "test ins_ad"

l2:			ld %-65536, r1
			ld %65500, r2
			add r1, r2, r16
			zjmp %:display
			ld %-1, r3
			ld %37, r4
			add r3, r4, r15
			zjmp %:display
			add r16, r15, r14
			zjmp %:ok

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:next

ok:			ld %49, r1
			aff r1	

next:		ld %2147483649, r5
			ld %-2147483649, r6
			add r6, r5, r14
			zjmp %:ok2

display2:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

ok2:		ld %49, r1
			aff r1	


end:	

