.name "test-ldi"
.comment "test ins_ldi"

l2:			ldi 4, %0, r2
			ld %262144, r3
			sub r2, r3, r4
			zjmp %:next

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

next:		ldi %262144, r16, r5
			ld %177471488, r6
			sub r5, r6, r4
			zjmp %:next2

display2:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

next2:		ld %-2, r7
			ldi r7, %-78, r8
			ld %-67108867, r9
			add r8, r9, r10
			zjmp %:ok

display3:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end	

ok:			ld %49, r1
			aff r1

end:	

