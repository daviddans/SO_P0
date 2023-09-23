#Regla para compilar p0 y dependencias
compile: p0.c p0_lib.c
	@gcc -o salida.out -Wall p0.c p0_lib.c

run: p0.c p0_lib.c
	@gcc -o salida.out -Wall p0.c p0_lib.c
	@./salida.out

clear:
	@rm *.out