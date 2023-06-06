#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "map.h"

#define barrita "|"

typedef unsigned short uShort;

typedef struct{
  int numero;
  char *terreno;

}tipoHexagono;

void crearNuevaPartida(){

  return;
}

uShort dado(){
  return (rand() % 6) + 1;
}

uShort dosDados(){
  return dado() + dado();
}

void instrucciones(){
  int opcionInstrucciones;
  

  while (true){
    printf("1. Conocimientos generales\n");
    printf("2. Turnos\n");
    printf("0. Volver al menu principal\n");
    scanf("%d", &opcionInstrucciones);
    switch (opcionInstrucciones)
    {
      case 0:
        return;
      case 1:
        printf(" ___________________________________________________________________________________________________________________________________________\n");
        printf("|Catan es un juego de estrategia que consiste en conseguir 10 puntos a traves de la construccion de edificios y la recoleccion de materiales|\n");
        printf("|Los materiales se consiguen a traves de los hexagonos que conforman el tablero %61s\n", barrita);
        printf("|Cada hexagono tiene un numero y un terreno %97s\n", barrita);
        printf("|Los numeros del hexagono seran dados a traves de un dado %83s\n", barrita);
        printf("|Los terrenos son: bosques (maderas), colinas (ladrillos), praderas (ovejas), cultivos (trigos) y canteras (rocas) %26s\n", barrita);
        printf("|Los edificios que se pueden construir son: caminos, pueblos y ciudades %69s\n", barrita);
        printf("|Los caminos se construyen con 1 ladrillo y 1 madera %88s\n", barrita);
        printf("|Los pueblos se construyen con 1 ladrillo, 1 madera, 1 oveja y 1 trigo                                                                      |\n");
        printf("|Las ciudades se construyen con 2 trigos y 3 rocas                                                                                          |\n");
        printf("|Los pueblos generan 1 punto y las ciudades 2 puntos                                                                                        |\n");
        printf("|Los caminos no generan puntos                                                                                                              |\n");
        printf("|Los pueblos generan 1 material por turno y las ciudades 2 materiales por turno                                                             |\n");
        printf("|Los caminos no generan materiales                                                                                                          |\n");
        printf("|Los pueblos y ciudades deben estar conectados a un camino                                                                                  |\n");
        printf("|Los pueblos deben estar a 2 caminos de distancia entre si                                                                                  |\n");
        printf("|Los pueblos y ciudades no pueden estar a 1 camino de distancia entre si                                                                    |\n");
        printf(" ___________________________________________________________________________________________________________________________________________\n");
        break;

      case 2:
        printf("Para comenzar la partida:\n");
        printf("1. Lanzar el dado para decidir el orden de los jugadores\n");
        printf("2. El orden para colocar los primeros edificios es el siguiente: jugador 1, jugador 2, jugador 3 y jugador 4\n");
        printf("Y luego: jugador 4, jugador 3, jugador 2 y jugador 1\n");
        printf("3. Cada jugador debe de haber colocado 2 pueblos y 2 caminos en total en la posicion que desee\n");
        printf("4. Luego de que todos los jugadores hayan colocado sus edificios, se procede a lanzar el dado\n");
        printf("5. El ultimo jugador que haya construido su edificio sera el primero en lanzar el dado\n");
        printf("6. Todos los jugadores obtendran los materiales correspondientes dependiendo del numero que haya salido en el dado\n");


    
        break;

      default:
        printf("Ingrese una opcion valida\n");
        break;
    }
  }
}

void tableroCostos(){
  printf("Costos de los edificios:\n");
  printf("Caminos: 1 madera y 1 ladrillo\n");
  printf("Pueblos: 1 madera, 1 ladrillo, 1 trigo y 1 oveja\n");
  printf("Ciudades: 2 trigos y 3 rocas\n");
  printf("Carta de desarrollo: 1 trigo, 1 oveja y 1 roca\n");
  return;
}

void generarNuevoTablero(){
  
  return;
}

int main(){
  srand(time(NULL));
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