.name "zork1"
.comment "I'M1 ALIIIIVE1"

<<<<<<< HEAD
l2: sti r1, %:end, %1
	and r1, %0, r1 
end: live %1
	 zjmp %:end

||||||| merged common ancestors
l2:		sti r1, %:live, %1
		and r1, %0, r1

l2ive:	live %1
		zjmp %:live

=======
l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
>>>>>>> 2c1c5442bd8b069b042a08da637c2350f234f34a
