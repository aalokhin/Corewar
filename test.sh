./corewar vm_champs/champs/Gagnant.cor -v 31 > test_files/all_v_my
./corewar vm_champs/champs/toto.cor -v 31 > test_files/all_v_my_toto
./corewar vm_champs/champs/jumper.cor -v 31 > test_files/all_v_my_jumper
./corewar vm_champs/champs/slider2.cor -v 31 > test_files/all_v_my_slider
./corewar vm_champs/champs/Octobre_Rouge_V4.2.cor -v 31 -d 30000 > test_files/all_v_my_octobre
./corewar vm_champs/champs/Car.cor -v 31 -d 30000 > test_files/all_v_my_car
./corewar vm_champs/champs/maxidef.cor -v 31 > test_files/all_v_my_maxidef
./corewar vm_champs/champs/mortel.cor -v 31 > test_files/all_v_my_mortel
./corewar vm_champs/champs/ex.cor -v 31 > test_files/all_v_my_ex

./vm_champs/corewar vm_champs/champs/ex.cor -v 31 > test_files/all_v_or_ex
./vm_champs/corewar vm_champs/champs/Car.cor -v 31 -d 30000 > test_files/all_v_or_car
./vm_champs/corewar vm_champs/champs/jumper.cor -v 31 > test_files/all_v_or_jumper
./vm_champs/corewar vm_champs/champs/maxidef.cor -v 31 > test_files/all_v_or_maxidef
./vm_champs/corewar vm_champs/champs/mortel.cor -v 31 > test_files/all_v_or_mortel
./vm_champs/corewar vm_champs/champs/Octobre_Rouge_V4.2.cor -v 31 -d 30000 > test_files/all_v_or_octobre
./vm_champs/corewar vm_champs/champs/slider2.cor -v 31 > test_files/all_v_or_slider
./vm_champs/corewar vm_champs/champs/toto.cor -v 31 > test_files/all_v_or_toto
./vm_champs/corewar vm_champs/champs/Gagnant.cor -v 31 > test_files/all_v_or

diff test_files/all_v_or test_files/all_v_my > test_files/diff_v_gagnant
diff test_files/all_v_or_ex test_files/all_v_my_ex > test_files/diff_v_ex
diff test_files/all_v_or_car test_files/all_v_my_car > test_files/diff_v_car
diff test_files/all_v_or_jumper test_files/all_v_my_jumper > test_files/diff_v_jumper
diff test_files/all_v_or_maxidef test_files/all_v_my_maxidef > test_files/diff_v_maxidef
diff test_files/all_v_or_mortel test_files/all_v_my_mortel > test_files/diff_v_mortel
diff test_files/all_v_or_octobre test_files/all_v_my_octobre > test_files/diff_v_octobre
diff test_files/all_v_or_toto test_files/all_v_my_toto > test_files/diff_v_toto
diff test_files/all_v_or_slider test_files/all_v_my_slider > test_files/diff_v_slider