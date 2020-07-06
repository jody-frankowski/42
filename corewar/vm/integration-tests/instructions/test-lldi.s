.name "test-lldi"
.comment "test ins_lldi"

l2:			lldi -4, %0, r2
			zjmp %:display
			ld %249888764, r3
			st r2, 300
			sub r2, r3, r4
			zjmp %:next

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

next:		lldi %262144, r16, r5
			zjmp %:display
			ld %244580352, r6
			sub r5, r6, r4
			zjmp %:next2

display2:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

next2:		ld %-2, r7
			lldi r7, %-78, r8
			zjmp %:display
			ld %-738546690, r9
			add r8, r9, r10
			zjmp %:next3

display3:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

next3:		lldi 789, %720, r2
			zjmp %:ok

display4:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1

end:	

