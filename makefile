#Regla para compilar la practica
p2: p2.c p2_lib.c p1_lib.c p0_lib.c lista.c 
	@gcc -o p2.out -Wall p2.c p2_lib.c p1_lib.c p0_lib.c lista.c
#Regla para borrar el codigo compilado
clear:
	@rm *.out
#Regla para probar las listas(En desuso)
lista: testLista.c p1_lib.c p0_lib.c lista.c 
	@gcc -o testlista.out -Wall testLista.c p1_lib.c p0_lib.c lista.c