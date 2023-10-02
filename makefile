#Regla para compilar p0 y dependencias
compile: p1.c p1_lib.c p0_lib.c lista.c 
	@gcc -o p1.out -Wall p1.c p1_lib.c p0_lib.c lista.c
#Regla para borrar el codigo compilado
clear:
	@rm *.out
#Regla para probar las listas 
lista: testLista.c lista.c
	@gcc -o testlista.out -Wall testLista.c lista.c 
