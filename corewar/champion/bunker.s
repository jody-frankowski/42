.name "gandalf"
.comment "you shall not write"

init:
	sti	    r1,	%:wall,	%1
	sti		r1, %:alive, %1
	sti		r1, %:forklive, %1
	sti		r1, %:wallstart, %1
	sti		r1, %:fork, %1
	sti     r1, %:fork, %9

#simple strategie, will prevent other process to come/write and wil keep living

fork:
	live	%0
	fork	%:wallstart
	live	%0
	fork	%:fork

forklive:	
	live	%0
	fork	%:forklive
	aff		r1

alive:
	live	%0
	ld		%0, r11
	zjmp	%:alive

#will load these instruction:
#zjmp %-3
#that will block ennemies process by making them jump backward

wallstart:
	live	%0
    ld      %655357, r2
	fork	%:wallstart

#st is a 5 bytes instruction, so only need to shift by -1
wall:
	live    %0
	st      r2, -300
	st      r2, -301
	st      r2, -302
	st      r2, -303
	st      r2, -304
	st      r2, -305
	st      r2, -306
	st      r2, -307
	st      r2, -308
	st      r2, -309
	st      r2, -310
	st      r2, -311
	st      r2, -312
	st      r2, -313
	st      r2, -314
    st      r2, -315
	st      r2, -316
	st      r2, -317
	st      r2, -318
	st      r2, -319
	st      r2, -320
	st      r2, -321
	st      r2, -322
	st      r2, -323
	st      r2, -324
	st      r2, -325
	st      r2, -326
	st      r2, -327
	st      r2, -328
	st      r2, -329
	ld		%0, r16
	zjmp	%:wall