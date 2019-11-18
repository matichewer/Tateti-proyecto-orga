


# Compilo todos los archivos fuente
gcc -Wall -c lista.c arbol.c partida .c ia.c main.c -fPIC
# Le tuve que agregar -fPIC ??




# Genero la libreria
ld -o libtateti.so lista.o arbol.o partida.o ia.o -shared
# son todas menos el main ???
# le tuve que sacar el -Wall




# Genero ejecutable
gcc -Wall -o tateti  main.o -L. -ltateti




# Le doy permisos a la libreria
sudo cp libtateti.so /usr/lib
sudo chmod 0755 /usr/lib/libtateti.so
sudo ldconfig