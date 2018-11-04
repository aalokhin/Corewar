.name "zork"
.comment "just a basic living prog"
		
l2:	sti	r1,%:live,%0  #aaaa
	and	r1,%0,r1		#bbbb
live:	live	%1		#cccc
	zjmp	%:live		#dddd
