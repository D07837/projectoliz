#include <stdio.h>
#include <stdlib.h>

void pantallaInicio(){
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
void mostrarMapa(char sala[4][5]){
    system("cls");

            printf("\n");
            printf("====================================\n");
            printf("              PANTALLA\n");
            printf("====================================\n\n");

            printf("      1   2   3   4   5\n\n");

            for(int i = 0; i < 4; i++) {

                printf("%c    ", 'A' + i);

                for(int j = 0; j < 5; j++) {

                    if(sala[i][j] == 'L')
                        printf("\033[32m[ ]\033[0m ");

                    else if(sala[i][j] == 'R')
                        printf("\033[33m[R]\033[0m ");

                    else if(sala[i][j] == 'X')
                        printf("\033[31m[X]\033[0m ");
                }

                printf("\n");
            }

            printf("\n");
            printf("====================================\n");
            printf("         DISFRUTE LA FUNCION\n");
            printf("====================================\n");

            printf("\nLeyenda:\n");
            printf("\033[32m[ ] Disponible\033[0m\n");
            printf("\033[33m[R] Reservado\033[0m\n");
            printf("\033[31m[X] Vendido\033[0m\n");

            printf("\n");
            system("pause");
}
int Menu(){
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
        printf("\033[36m[4]\033[0m Salir\n\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        return opcion;
}
void Reservar(char sala[4][5]){
    system("cls");
    mostrarMapa(sala);
    char fila;
    int columna;


        printf("\033[33m");

        printf("====================================\n");
        printf("        RESERVA DE ASIENTOS\n");
        printf("====================================\n");

        printf("\033[0m");

        printf("selecciona la fila: ");
        scanf(" %c", &fila);
            
        printf("\n selecciona la columna: ");
        scanf("%d", &columna);
            
        int f=fila-'A';
        int c=columna-1;
            
        if(sala[f][c]=='L'){
            sala[f][c]='R';
            printf("\n asiento reservado");
        }
        else{
            printf("\n asiento ocupado");
        }

        printf("\n");
        system("pause");
}
void Cancelar(char sala[4][5]){
    system("cls");
    mostrarMapa(sala);
    char fila;
    int columna;

        printf("\033[33m");

        printf("====================================\n");
        printf("        CANCELACION DE RESERVA\n");
        printf("====================================\n");

        printf("selecciona la fila: ");
        scanf(" %c", &fila);
            
        printf("\n selecciona la columna: ");
        scanf("%d", &columna);
            
        int f=fila-'A';
        int c=columna-1;
            
        if(sala[f][c]=='R'){
            sala[f][c]='L';
            printf("\n asiento cancelado");
        }
        else{
            printf("\n asiento sin reservar");
        }

        printf("\n");
        system("pause");
}
int main() {

int opcion = 0;
char sala[4][5] = {
        {'L','L','X','L','L'},
        {'L','R','L','L','L'},
        {'X','L','L','L','L'},
        {'L','L','R','L','L'}
    };
pantallaInicio();
    while(opcion != 4) {
        opcion = Menu();
        switch(opcion) {
            case 1:
            mostrarMapa(sala); break;
            case 2:
            Reservar(sala); break;
            case 3:
            Cancelar(sala); break;
            case 4:
            printf("Gracias por usar CINEMAX\n"); break;
            default:
                printf("Opcion invalida\n");
        }
    }
    return 0;
}
