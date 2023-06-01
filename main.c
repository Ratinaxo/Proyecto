#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include "map.h"

typedef struct{
  int numero;
  char *terreno;

}tipoHexagono;

void crearNuevaPartida(){

  return;
}

void instrucciones(){
  int opcionInstrucciones;
  printf("1. Conocimientos generales\n");
  printf("2. Turnos\n");
  printf("0. Volver al menu principal\n");
  scanf("%d", &opcionInstrucciones);

  while (true){
    switch (opcionInstrucciones)
    {
      case 0:
        return;
      case 1:
        printf("caso 1\n");
        break;

      case 2:
        printf("caso 2\n");
        break;

      default:
        printf("Ingrese una opcion valida\n");
        break;
    }
  }
}

void generarNuevoTablero(){
  
  return;
}

int main(){
  int opcionMenuPrincipal;
  printf("1. Crear nueva partida\n");
  printf("2. Instrucciones\n");
  do{
    printf("Ingrese una opcion: ");
    scanf("%d", &opcionMenuPrincipal);

    if (opcionMenuPrincipal < 0 || opcionMenuPrincipal > 2)
      printf("Ingrese una opcion valida\n");

  }while (opcionMenuPrincipal < 0 || opcionMenuPrincipal > 2);

  while (true){
    switch (opcionMenuPrincipal)
    {
    case 0:
      printf("Gracias por jugar\n");
      exit(EXIT_SUCCESS);
    case 1:
      crearNuevaPartida();
      break;
    case 2:
      instrucciones();
      break;
    }
  }
  return EXIT_SUCCESS;
}