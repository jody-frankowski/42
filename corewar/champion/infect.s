.name "infect"
.comment "lemme init it for ya"


#655357 = zjmp %-4

#rewrite the start of the program with a zjmp to keep ennemies away
#from our initializations
entry:
    xor %1, %1, r2
    ld %655357, r3
    st r3, -4

#init lives's ids
live_setup:
    sti r1, %:live, %1
    sti r1, %:front_wall, %1
    sti r1, %:back_wall, %1

#spawn the process neededs to wall and live
init:
    fork %:live
    st r1, 6
    live %0
    fork %:front_wall
    st r1, 6
    live %0
    fork %:back_wall

#spawn a process in the middle of the arena
#to rewrite ennemies live with our own id
corruption:
    lfork %1975

#live loop
live:
    live %0
    xor %1, %1, r2
    zjmp %:live

spawn:
    live %42
    fork %:live
    live %42
    fork %:front_wall
    live %42
    fork %:back_wall
    zjmp %:spawn

#keep a wall on the back and on the front of the program to stop chain reactions
#running wild toward our program
front_wall:
    live %0
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    st r2, 400
    xor %1, %1, r2
    zjmp %:front_wall

back_wall:
    live %42
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    st r2, -400
    xor %1, %1, r2
    zjmp %:back_wall
