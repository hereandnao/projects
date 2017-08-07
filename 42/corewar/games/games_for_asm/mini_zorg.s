.comment "Juste un gros boulet..."
.name "mini_zorg"

sti r1, %40, %40
sti r1, %80, %80
and r2, %0, r2				; N'a aucn véritable effet à part modifier le carry et ainsi permettre le zjmp		TIME=06
begin:
sti r1, %-512, %-512
sti r1, %:live, %1			; modifie la valeure après le live par son R1 (numero du joueur)					TIME=25	
live:
live %1 					; Avertit qu'il est en vie !														TIME=10
fork %:last
zjmp %:begin

last:	
sti r1, %:live1, %1			; modifie la valeure après le live par son R1 (numero du joueur)					TIME=25	
live1:
live %1 					; Avertit qu'il est en vie !
fork %:begin
zjmp %:last


sti r1, %:live, %1			; modifie la valeure après le live par son R1 (numero du joueur)					TIME=25			
and r1, %0, r1				; N'a aucn véritable effet à part modifier le carry et ainsi permettre le zjmp		TIME=06
						
live %1 					; Avertit qu'il est en vie !														TIME=10
zjmp %:live					; revient à live																	TIME=20
and r1, %0, r1				; N'a aucn véritable effet à part modifier le carry et ainsi permettre le zjmp		TIME=06
zjmp %:live					; revient à live																	TIME=20

babel:
zjmp %:begin				; revient à live																	TIME=20
and r1, %0, r1				; N'a aucn véritable effet à part modifier le carry et ainsi permettre le zjmp		TIME=06
zjmp %:begin				; revient à live																	TIME=20

