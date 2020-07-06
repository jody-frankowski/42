.name "test-live"
.comment "test ins_live"

l2:		ld %42, r2
		sti r1, %:live, %1

live:	live %1

l2:		sti r2, %:live2, %1

live2:	live %1

