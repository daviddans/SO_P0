#Regla para compilar p0 y dependencias
compilar: p0.c p0_lib.c
  gcc -o salida.out -Wall p0.c p0_lib.c
