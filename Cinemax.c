#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Asiento {
    int fila;
    int columna;
    char estado;          // L = Libre, R = Reservado, X = Vendido
    int idReserva;
    char *nombreCliente;  // Cadena dinamica
};

void limpiarBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void leerLinea(char texto[], int tam) {
    fgets(texto, tam, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

void pantallaInicio() {
    system("cls");

    printf("\033[36m");

    printf("====================================\n");
    printf("         SISTEMA CINEMAX\n");
    printf("====================================\n");

    printf("\033[0m");

    printf("\nInicializando sistema...\n\n");

    for(int i = 0; i < 10; i++) {
        printf("#");
        fflush(stdout);
        system("timeout /t 1 > nul");
    }

    printf("\n\nSistema cargado correctamente.\n\n");
    system("pause");
}

struct Asiento **crearSala(int filas, int columnas) {
    struct Asiento **sala;

    sala = (struct Asiento **)malloc(filas * sizeof(struct Asiento *));

    if(sala == NULL) {
        printf("Error al reservar memoria.\n");
        exit(1);
    }

    for(int i = 0; i < filas; i++) {
        sala[i] = (struct Asiento *)malloc(columnas * sizeof(struct Asiento));

        if(sala[i] == NULL) {
            printf("Error al reservar memoria.\n");
            exit(1);
        }
    }

    return sala;
}

void inicializarSala(struct Asiento **sala, int filas, int columnas) {
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            sala[i][j].fila = i;
            sala[i][j].columna = j;
            sala[i][j].estado = 'L';
            sala[i][j].idReserva = 0;
            sala[i][j].nombreCliente = NULL;
        }
    }
}

void liberarSala(struct Asiento **sala, int filas, int columnas) {
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            if(sala[i][j].nombreCliente != NULL) {
                free(sala[i][j].nombreCliente);
                sala[i][j].nombreCliente = NULL;
            }
        }

        free(sala[i]);
    }

    free(sala);
}

void mostrarMapa(struct Asiento **sala, int filas, int columnas) {
    system("cls");

    printf("\n");
    printf("====================================\n");
    printf("              PANTALLA\n");
    printf("====================================\n\n");

    printf("      ");

    for(int j = 0; j < columnas; j++) {
        printf("%d   ", j + 1);
    }

    printf("\n\n");

    for(int i = 0; i < filas; i++) {

        printf("%c    ", 'A' + i);

        for(int j = 0; j < columnas; j++) {

            if(sala[i][j].estado == 'L')
                printf("\033[32m[ ]\033[0m ");

            else if(sala[i][j].estado == 'R')
                printf("\033[33m[R]\033[0m ");

            else if(sala[i][j].estado == 'X')
                printf("\033[31m[X]\033[0m ");
        }

        printf("\n");
    }

    printf("\n");
    printf("====================================\n");
    printf("         DISFRUTE LA FUNCION\n");
    printf("====================================\n");

    printf("\nLeyenda:\n");
    printf("\033[32m[ ] Libre\033[0m\n");
    printf("\033[33m[R] Reservado\033[0m\n");
    printf("\033[31m[X] Vendido/Ocupado\033[0m\n");

    printf("\n");
}

int Menu() {
    int opcion;

    system("cls");

    printf("\033[36m");

    printf("====================================\n");
    printf("             CINEMAX\n");
    printf("====================================\n\n");

    printf("\033[0m");

    printf("\033[32m[1]\033[0m Ver sala\n");
    printf("\033[33m[2]\033[0m Reservar asiento\n");
    printf("\033[31m[3]\033[0m Cancelar reserva\n");
    printf("\033[31m[4]\033[0m Vender asiento\n");
    printf("\033[36m[5]\033[0m Salir\n\n");

    printf("Seleccione una opcion: ");

    if(scanf("%d", &opcion) != 1) {
        limpiarBuffer();
        return 0;
    }

    limpiarBuffer();

    return opcion;
}

int validarAsiento(char fila, int columna, int filas, int columnas, int *f, int *c) {
    fila = toupper(fila);

    *f = fila - 'A';
    *c = columna - 1;

    if(*f < 0 || *f >= filas || *c < 0 || *c >= columnas) {
        return 0;
    }

    return 1;
}

void reservarAsiento(struct Asiento **sala, int filas, int columnas, int *contadorID) {
    char fila;
    int columna;
    int f, c;
    char nombre[100];

    mostrarMapa(sala, filas, columnas);

    printf("\033[33m");

    printf("====================================\n");
    printf("        RESERVA DE ASIENTOS\n");
    printf("====================================\n");

    printf("\033[0m");

    printf("Selecciona la fila: ");
    scanf(" %c", &fila);

    printf("Selecciona la columna: ");
    scanf("%d", &columna);

    limpiarBuffer();

    if(!validarAsiento(fila, columna, filas, columnas, &f, &c)) {
        printf("\nAsiento invalido.\n");
        system("pause");
        return;
    }

    if(sala[f][c].estado == 'L') {
        printf("Nombre del cliente: ");
        leerLinea(nombre, 100);

        sala[f][c].nombreCliente = (char *)malloc(strlen(nombre) + 1);

        if(sala[f][c].nombreCliente == NULL) {
            printf("\nError al reservar memoria para el nombre.\n");
            system("pause");
            return;
        }

        strcpy(sala[f][c].nombreCliente, nombre);

        sala[f][c].estado = 'R';
        sala[f][c].idReserva = *contadorID;

        printf("\nAsiento reservado correctamente.\n");
        printf("ID de reserva: %d\n", sala[f][c].idReserva);
        printf("Cliente: %s\n", sala[f][c].nombreCliente);

        (*contadorID)++;
    }
    else {
        printf("\nEse asiento no esta disponible.\n");
    }

    printf("\n");
    system("pause");
}

void cancelarReserva(struct Asiento **sala, int filas, int columnas) {
    char fila;
    int columna;
    int f, c;

    mostrarMapa(sala, filas, columnas);

    printf("\033[33m");

    printf("====================================\n");
    printf("        CANCELACION DE RESERVA\n");
    printf("====================================\n");

    printf("\033[0m");

    printf("Selecciona la fila: ");
    scanf(" %c", &fila);

    printf("Selecciona la columna: ");
    scanf("%d", &columna);

    limpiarBuffer();

    if(!validarAsiento(fila, columna, filas, columnas, &f, &c)) {
        printf("\nAsiento invalido.\n");
        system("pause");
        return;
    }

    if(sala[f][c].estado == 'R') {
        sala[f][c].estado = 'L';
        sala[f][c].idReserva = 0;

        if(sala[f][c].nombreCliente != NULL) {
            free(sala[f][c].nombreCliente);
            sala[f][c].nombreCliente = NULL;
        }

        printf("\nReserva cancelada correctamente.\n");
    }
    else {
        printf("\nEse asiento no tiene una reserva activa.\n");
    }

    printf("\n");
    system("pause");
}

void venderAsiento(struct Asiento **sala, int filas, int columnas) {
    char fila;
    int columna;
    int f, c;

    mostrarMapa(sala, filas, columnas);

    printf("\033[31m");

    printf("====================================\n");
    printf("           VENTA DE ASIENTO\n");
    printf("====================================\n");

    printf("\033[0m");

    printf("Selecciona la fila: ");
    scanf(" %c", &fila);

    printf("Selecciona la columna: ");
    scanf("%d", &columna);

    limpiarBuffer();

    if(!validarAsiento(fila, columna, filas, columnas, &f, &c)) {
        printf("\nAsiento invalido.\n");
        system("pause");
        return;
    }

    if(sala[f][c].estado == 'X') {
        printf("\nEse asiento ya esta vendido.\n");
    }
    else {
        sala[f][c].estado = 'X';
        sala[f][c].idReserva = 0;

        if(sala[f][c].nombreCliente != NULL) {
            free(sala[f][c].nombreCliente);
            sala[f][c].nombreCliente = NULL;
        }

        printf("\nAsiento vendido correctamente.\n");
    }

    printf("\n");
    system("pause");
}

void Leer(int *filas, int *columnas){
    FILE *archivo=fopen("guardado.txt", "r");
    if(archivo==NULL){
        archivo = fopen("guardado.txt", "w");
        fprintf(archivo, "4 5");
        fclose(archivo);
        *filas=4;
        *columnas=5;
        return;
    }
    fscanf(archivo, "%d %d", filas, columnas);
    fclose(archivo);
}
void Guardar(struct Asiento **sala, int filas, int columnas){
    FILE *archivo=fopen("sala.dat","wb");
    if(archivo==NULL){
        printf("error");
        return;
    }
    fclose(archivo);
}
void Cargar(struct Asiento **sala, int filas, int columnas){
    FILE *archivo=fopen("sala.dat","rb");
    if(archivo==NULL){
        inicializarSala(sala, filas, columnas);
        return;
    }
    fclose(archivo);
}

int main() {

    int opcion = 0;
    int filas, columnas;
    Leer(&filas, &columnas);
    int contadorID = 1;

    struct Asiento **sala;

    sala = crearSala(filas, columnas);

    Cargar(sala, filas, columnas);

    pantallaInicio();

    while(opcion != 5) {

        opcion = Menu();

        switch(opcion) {

            case 1:
                mostrarMapa(sala, filas, columnas);
                system("pause");
                break;

            case 2:
                reservarAsiento(sala, filas, columnas, &contadorID);
                break;

            case 3:
                cancelarReserva(sala, filas, columnas);
                break;

            case 4:
                venderAsiento(sala, filas, columnas);
                break;

            case 5:
                printf("\nGracias por usar CINEMAX.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                system("pause");
                break;
        }
    }
    Guardar(sala, filas, columnas);
    liberarSala(sala, filas, columnas);

    return 0;
}