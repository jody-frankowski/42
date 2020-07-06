.name "test-xor"
.comment "test ins_xor"

l2:			ld %0, r1
			ld %-1, r2
			xor r1, r2, r3
			zjmp %:display
			ld %4858137, r4
			xor r3, r4, r5
			zjmp %:display
			ld %-8, r6
			xor r5, r6, r7
			zjmp %:display
			ld %4858122, r8
			xor r7, r8, r9
			zjmp %:display
			ld %20, r10
			xor r9, r10, r11
			zjmp %:ok

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1

end:	

