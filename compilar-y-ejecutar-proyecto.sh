
# Compilo todos los archivos fuente
gcc -Wall -g -c arbol.c -o arbol.o
gcc -Wall -g -c lista.c -o lista.o
gcc -Wall -g -c ia.c -o ia.o
gcc -Wall -g -c main.c -o main.o
gcc -Wall -g -c partida.c -o partida.o


# Genero el ejecutable
g++ -o Tateti-Ejecutable arbol.o ia.o lista.o main.o partida.o  


# Borro los archivos compilados
rm *.o


# Ejecuto
./Tateti-Ejecutable


# Borro el ejecutable
rm Tateti-Ejecutable