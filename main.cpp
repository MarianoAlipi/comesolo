// Mariano García Alipi

#include <iostream>
#include <iomanip>
#include <cmath>
#include <locale>
#include <cstdlib>
#include <ctime>

#define SIZE 4

using namespace std;

char cMatTablero[SIZE][SIZE];
char const SIMBOLO = '$';

// Función para llenar el tablero con 13 fichas en posiciones aleatorias.
void llenaTablero() {

    int iR, iC, iCont;

    // Llenar la matriz con espacios vacíos.
    for (iR = 0; iR < 4; iR++)
        for (iC = 0; iC < 4; iC++)
            cMatTablero[iR][iC] = ' ';

    srand((int)time(0));

    // Llenar 13 espacios de la matriz con el símbolo de ficha.
    for (iCont = 1; iCont <= 13; ) {
        iR = rand() % 4; // esto genera un numero aleatorio
        iC = rand() % 4; // entre 0 y 3
        if (cMatTablero[iR][iC] == ' ') {
            cMatTablero[iR][iC] = SIMBOLO;
            iCont++;
        }
    }
}

// Función para mostrar el encabezado de bienvenida.
void mostrarEncabezado() {
    cout << setw(49) << setfill('#') << "" << endl;
    cout << "#" << setw(33) << setfill(' ') << "B I E N V E N I D O";
    cout << setw(15) << "#" << endl;
    cout << setw(49) << setfill('#') << "" << endl;
}

// Función para mostrar una línea divisora.
void mostrarLinea() {
    cout << setw(49) << setfill ('-') << "-" << endl;
}

// Función para mostrar el mensaje de fin del juego.
void mostrarFin() {
    cout << setw(49) << setfill('#') << "" << endl;
    cout << "#" << setw(29) << setfill(' ') << "FIN DEL JUEGO";
    cout << setw(19) << "#" << endl;
    cout << setw(49) << setfill('#') << "" << endl << endl;
}

// Función para mostrar el estado actual del tablero.
void mostrarTablero() {
    int id = 1;
    cout << endl;
    for(int row = 0; row < SIZE; row++) {
        for(int col = 0; col < SIZE; col++) {
            cout << setw(2) << setfill(' ') << id;
            cout << "[" << cMatTablero[row][col] << "] ";
            id++;
        }
        cout << endl;
    }
}

// Función para obtener la fila y columna de una casilla desde su número.
void obtenerCoordenadas(int casilla, int &fila, int &columna) {
    fila = floor((casilla / 4.0) - 0.1);
    columna = (casilla - 1) % 4;
}

// Función para obtener el contenido de la casilla.
char obtenerFichaEnCasilla(int fila, int columna) {
    return cMatTablero[fila][columna];
}

// Función para modificar el tablero al hacer un movimiento.
void moverFicha(int fila, int columna, int filaMedia, int columnaMedia, int filaDestino, int columnaDestino) {
    cMatTablero[fila][columna] = ' ';
    cMatTablero[filaMedia][columnaMedia] = ' ';
    cMatTablero[filaDestino][columnaDestino] = SIMBOLO;
}

int main() {

    // fila y columna de la ficha a mover. fila y columna Destino es a donde la ficha será movida. fila y columna Media es la ficha intermedia en el movimiento, la que será "comida".
    int fichaAMover, fila, columna, filaMedia, columnaMedia, filaDestino, columnaDestino;
    // Cantidad de fichas restantes en el tablero.
    int cantFichas = 13;
    char direccion, seguirJuego;

    setlocale(LC_CTYPE, "Spanish");

    mostrarEncabezado();
    llenaTablero();

    // Ciclo principal del juego.
    do {
        // Verificar que haya una ficha en el lugar elegido.
        do {
            // Verificar que la casilla exista.
            do {
                mostrarTablero();
                cout << "Casilla de la ficha a mover => ";
                cin >> fichaAMover;
            } while(fichaAMover < 1 || fichaAMover > SIZE*SIZE);

            obtenerCoordenadas(fichaAMover, fila, columna);

        } while(obtenerFichaEnCasilla(fila, columna) != SIMBOLO);

        // Verificar que la dirección sea una de las opciones.
        do {
            cout << "Dirección para mover la ficha\n\tW - arriba\n\tS - abajo\n\tA - izquierda\n\tD - derecha\n => ";
            cin >> direccion;
            direccion = toupper(direccion);
        } while(direccion != 'W' && direccion != 'S' && direccion != 'A' && direccion != 'D');

        // Obtener las coordenadas de las otras casillas relevantes.
        obtenerCoordenadas(fichaAMover, fila, columna);
        switch(direccion) {
            case 'W':
                filaMedia = fila - 1;
                columnaMedia = columna;
                filaDestino = fila - 2;
                columnaDestino = columna;
                break;
            case 'S':
                filaMedia = fila + 1;
                columnaMedia = columna;
                filaDestino = fila + 2;
                columnaDestino = columna;
                break;
            case 'A':
                filaMedia = fila;
                columnaMedia = columna - 1;
                filaDestino = fila;
                columnaDestino = columna - 2;
                break;
            case 'D':
                filaMedia = fila;
                columnaMedia = columna + 1;
                filaDestino = fila;
                columnaDestino = columna + 2;
                break;
        }

        // Verificar que el movimiento esté dentro de la matriz.
        if(filaDestino >= 0 && filaDestino < SIZE && columnaDestino >= 0 && columnaDestino < SIZE) {
            // Verificar que el espacio esté vacío.
            if(obtenerFichaEnCasilla(filaDestino, columnaDestino) == ' ') {
                // Verificar que haya una ficha que comer.
                if(obtenerFichaEnCasilla(filaMedia, columnaMedia) == SIMBOLO) {

                    moverFicha(fila, columna, filaMedia, columnaMedia, filaDestino, columnaDestino);
                    cantFichas--;
                }
            } else { // El espacio está ocupado.
                // No hacer nada; repetir iteración.
            }
        } else { // El espacio está fuera de la matriz.
            // No hacer nada; repetir iteración.
        }

        mostrarTablero();

        // Preguntar si se desea seguir jugando.
        do {
            cout << endl << "¿Desea seguir jugando? (S/N) => ";
            cin >> seguirJuego;
            seguirJuego = toupper(seguirJuego);
        } while(seguirJuego != 'S' && seguirJuego != 'N');

    mostrarLinea();

    } while(seguirJuego == 'S');

    mostrarFin();
    if(cantFichas == 1) {
        cout << "¡HA GANADO!" << endl << "Sólo queda una ficha." << endl;
    } else {
        cout << "¡HA PERDIDO!" << endl << "Quedan " << cantFichas << " fichas." << endl;
    }
}
