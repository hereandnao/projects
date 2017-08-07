.name "p_prog"
.comment "i'm just a fork"

l1:
fork %:banane
and r2, r2, r2
zjmp %:exit

banane:
and r2, r2, r2
live %404
zjmp %:banane

exit:
