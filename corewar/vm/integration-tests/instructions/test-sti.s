.name "test-sti"
.comment "test ins_sti"

l2:			ld %-1, r1
			sti r1, %-10, %500
			ld 483, r2
			xor r1, r2, r3
			zjmp %:next

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

next:		ld %262144, r2
			sti r2, %-500, r1
			ld -507, r1
			xor r1, r2, r3
			zjmp %:next2

display2:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

next2:		ld %-789, r1
			sti r1, 2, %-20000
			ld 138, r2
			xor r1, r2, r3
			zjmp %:ok

display3:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end	

ok:			ld %49, r1
			aff r1

end:	

