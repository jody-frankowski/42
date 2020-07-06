.name "test-sub"
.comment "test ins_sub"

l2:			ld %-2147483796, r1
			ld %2147483647, r2
			sub r2, r1, r16
			zjmp %:display
			ld %-152, r3
			ld %-299, r4
			sub r3, r4, r15
			zjmp %:display
			sub r16, r15, r14
			zjmp %:ok

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1

end:	

