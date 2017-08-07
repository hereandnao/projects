.comment "I'M ALIIIIVE"
.name "Guldan"

fork %:babel
sti r1, %:live, %1
l2:
and r1, %0, r1
live:live %1 #fofo

and %1, %1, r1						# carry modif to 1 if result of AND, XOR, OR, ADD, SUB = 0, modif to 0 if everythings else.
and %1, %1, r1
add r2, r1, r1
add r3, r3, r1
sub r1, r3, r4
add r6, r6, r6
xor %1, %0, r1
xor %0, %1, r1						#-> Un OU exclusif 1 xor 1 = 1     0 xor 0 = 1 		1 xor 0 = 0		0 xor 1 = 0
ld %1, r1
lld %2, r1
#ldi r9, %100, r9 
#lldi r9, %100, r9 
and 1, 1, r1
and 10, 10, r1
and 502, 502, r1
and %4, %12, r3
and 0, %0, r6
ld %4, r1
ld %8, r2
ld 1, r3
ld 0, r4
aff r1
aff r2
aff r3
add r1, r2, r16
add r2, r2, r5
sub r1, r2, r6
sub r2, r1, r7
babel:
zjmp %:l2
and %0, %0, r1
zjmp %:l2


#lld #ld #ldi #lldi					Seul ldi ne semble pas modifier le carry.

#pour ld qui charge une simple valeure dans un registre, c'est simple, si la valeure chargée est 0, le carry sera mis à 1 (ld semble sensible à idx_mod)
#meme situation pour lld, la carry est modifié si la valeur chargée est 0. (apparement, pour lui, on peut faire un addressage à distance sans ce soucier de idx_mod)
#lldi indique aussi que si la valeure lue à l'addresse désignée vaut 0, le carry passe à 1. (non soumis à IDX_MOD)


#ldi, qui lui est soumis à IDX_MOD ne semble pas par contre pouvoir modifier le carry !

#Modif carry -> add sub and xor or ld lld lldi

#Il serait bon de savoir si les addressages indirects pour AND, OR et XOR sont soumis à IDX_MOD. Visiblement ils le sont ! XD 
#Les addressages sont relatif au PC global de l'instruction et non à celui + l'offser du paramètre en cours de traitement.
