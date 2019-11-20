
# Compilo todos los archivos fuente
gcc -Wall -c arbol.c lista.c ia.c partida.c main.c


# Genero el ejecutable
g++ -o Tateti-ejecutable-linux arbol.o lista.o ia.o partida.o main.o


# Borro los archivos compilados que se generaron con el primer comando
rm *.o


# Ejecuto
#./Ejecutable


# Borro el ejecutable
#rm Ejecutable