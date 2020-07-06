.name "test-fork"
.comment "test ins_fork"

l2:			
			add r16, r16, r16
			zjmp %:next


fork1:		ld %49, r1
			aff r1
			add r16, r16, r16
			zjmp %:next2

next:		fork %:fork1
			live %1
			fork %528
			live %1
			add r16, r16, r16
			zjmp %:end
		
next2:		ld %49, r1
			aff r1
			add r16, r16, r16
			zjmp %:end

end:	

