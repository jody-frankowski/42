.name "NAME"
.comment "COMMENT"

label:
	live %:label
	ld  32767, r1
	st  r16, -32768
	add r1, r2, r3
	sub r16, r15, r14
	and 32767, %-2147483648, r1
	or  %2147483647, -32767, r1
	xor %2147483647, 32767, r1
	zjmp %-32768
	ldi -1, %-1, r1
	sti r16, -32768, %32767
	fork %:label
	lld %:label, r2
	lldi :label, %:label2, r16
	lfork %:label2
	aff r1
label2:
