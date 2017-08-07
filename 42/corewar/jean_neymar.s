.name		"Potato"
.comment	"When the testing is over, you will be baked, and then there will be cake."

start:
	sti		r1 , %:live, %1
	sti		r1, %:live1, %1
	sti		r1, %:live2, %1
	fork	%:live
	add		r2, r3, r4

live:
	live	%0
	zjmp	%:live

live1:
live	%0

live2:
	live %0
return:
	  zjmp %:start

sti		r1 , %:live, %85
sti		r1, %:live1, %99
sti		r1, %:live2, %121
fork	%:live1
add		r6, r7, r8
