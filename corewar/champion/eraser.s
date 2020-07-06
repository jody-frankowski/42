.name "eraser"
.comment "will grow a massiv colony to erase the map"

ld %2, r4				# r2 = 2
setup:
	live %2
    add r4, r4, r4
	#
    xor r4, %512, r7 	# if (%x \ 4 = process_count) 
    zjmp %:start		# go to start
    fork %:child		# else process_count *= 2
    live %0
    ld %0, r12	# carry
    zjmp %:setup

#when the time comes, each process will write 4 byte at a time
#so here the idea is to shift them by 4, and to stock it on r3.
#since child inherit parents reg:
#r3 table:
#p1->0:p3->8:p5->16
#p2->4:p4->12:p6->20
#p3:p7->24
#p4:p8->28
#...

child:
    add r3, r4, r3	
    ld %0, r12	# carry
    zjmp %:setup

#each process will load his piece of code in r14 and write it further

start:
    st r1, 12
    ldi %0, r3, r14 

code:
    live %1
    sti r14, %-511, r3 
    zjmp %-511
