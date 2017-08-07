.comment "I'm forking" 
.name "alive_fork"

sti r1, %:live, %1
live:
live %404
fork %:banane
after:
and r2, r2, r2
zjmp %:after
and r2, r2, r2
and r2, r2, r2
and r2, r2, r2
and r2, r2, r2
banane:
and r2, r2, r2
zjmp %:banane
