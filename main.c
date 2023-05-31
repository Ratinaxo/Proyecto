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

  switch (opcionInstrucciones)
  {
    case 0:
      break;
    case 1:
    
      break;

    case 2:

      break;

    default:
      printf("Ingrese una opcion valida\n");
      break;
  }
  return;
}

void generarNuevoTablero(){
  
  return;
}

int main(){
  int opcionMenuPrincipal;
  printf("1. Crear nueva partida\n");
  printf("2. Instrucciones\n");
  printf("0. Salir\n");
  do{
    printf("Ingrese una opcion: ");
    scanf("%d", &opcionMenuPrincipal);

    if (opcionMenuPrincipal < 0 || opcionMenuPrincipal > 2)
      printf("Ingrese una opcion valida\n");

  }while (opcionMenuPrincipal < 0 || opcionMenuPrincipal > 2);

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
  return EXIT_SUCCESS;
}