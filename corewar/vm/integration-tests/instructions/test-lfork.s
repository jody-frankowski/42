.name "test-lork"
.comment "test ins_lfork"

l2:			
			add r16, r16, r16
			zjmp %:next


fork1:		ld %49, r1
			aff r1
			add r16, r16, r16
			zjmp %:next2

next:		lfork %:fork1
			live %1
			lfork %528
			live %1
			add r16, r16, r16
			zjmp %:end
		
next2:		ld %49, r1
			aff r1
			add r16, r16, r16
			zjmp %:end

end:	

