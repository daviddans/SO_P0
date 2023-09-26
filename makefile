#Regla para compilar p0 y dependencias
compile: p0.c p0_lib.c 
	@gcc -o salida.out -Wall p0.c p0_lib.c p0_lib.h
#Regla para compilar y ejecutar
run: p0.c p0_lib.c
	@gcc -o salida.out -Wall p0.c p0_lib.c p0_lib.h
	@./salida.out
#Regla para borrar el codigo compilado
clear:
	@rm *.out
#Regla para probar las listas 
lista: testLista.c p0_lista.c p0_lista.h
	@gcc -o testlista.out -Wall testLista.c p0_lista.c p0_lista.h
