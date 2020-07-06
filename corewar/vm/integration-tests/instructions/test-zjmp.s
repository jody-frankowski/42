.name "test-zjmp"
.comment "test ins_zjmp"

l2:			ld %49, r1
			and r2, %0, r16
			zjmp %522
			ld %48, r1
tt:			aff r1
			ld %49, r2
			sub r1, r2, r16
			zjmp %:ok

display:	ld %48, r1
			aff r1
			ld %0, r1
			zjmp %:end

ok:			ld %49, r1
			aff r1

end:	

