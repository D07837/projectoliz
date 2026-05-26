#include <stdio.h>
#include <stdlib.h>

int main() {

    int opcion = 0;

    char sala[4][5] = {
        {'L','L','X','L','L'},
        {'L','R','L','L','L'},
        {'X','L','L','L','L'},
        {'L','L','R','L','L'}
    };

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

    while(opcion != 4) {

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

        if(opcion == 1) {

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

        else if(opcion == 2) {

            system("cls");

            printf("\033[33m");

            printf("====================================\n");
            printf("        RESERVA DE ASIENTOS\n");
            printf("====================================\n");

            printf("\033[0m");

            printf("\nFuncion en desarrollo...\n");

            printf("\n");
            system("pause");
        }

        else if(opcion == 3) {

            system("cls");

            printf("\033[31m");

            printf("====================================\n");
            printf("       CANCELAR RESERVACION\n");
            printf("====================================\n");

            printf("\033[0m");

            printf("\nFuncion en desarrollo...\n");

            printf("\n");
            system("pause");
        }

        else if(opcion == 4) {

            system("cls");

            printf("\033[36m");

            printf("====================================\n");
            printf("      GRACIAS POR USAR CINEMAX\n");
            printf("====================================\n");

            printf("\033[0m");
        }

        else {

            printf("\n\033[31mOpcion invalida.\033[0m\n");

            printf("\n");
            system("pause");
        }
    }

    return 0;
}