#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "map.h"
#include "vector.h"
#include <conio.h>

typedef struct{
  int numero;
  char *terreno;
  Vector *caminos;
  Vector *vertices;
  int idHexagono;
  bool tieneRobinson;
}tipoHexagono;

typedef struct{
  char nombre[20];
  int puntos; 
  Vector *recursos;
  Vector *edificios;
  int prioridad;
}tipoJugador;

typedef struct{
  tipoHexagono *hexagono1;
  tipoHexagono *hexagono2;
  char *jugador;
}tipoCamino;

typedef struct{
  Vector *hexagonosAdj;
  char *jugador;
  bool poblado;
  bool ciudad;
}tipoVertice;

tipoHexagono *crearTipoHexagono(int numero, char *terreno, int idHexagono, bool tieneLadron){
  tipoHexagono *nuevoHexagono = (tipoHexagono *)malloc(sizeof(tipoHexagono));
  nuevoHexagono->numero = numero;
  nuevoHexagono->terreno = terreno;
  nuevoHexagono->caminos = NULL;
  nuevoHexagono->vertices = NULL;
  nuevoHexagono->idHexagono = idHexagono;
  nuevoHexagono->tieneRobinson = tieneLadron;
  return nuevoHexagono;
}

tipoCamino *crearCamino(tipoHexagono *hex1, tipoHexagono *hex2){
  tipoCamino *nuevoCamino = (tipoCamino *)malloc(sizeof(tipoCamino));
  nuevoCamino->hexagono1 = hex1;
  nuevoCamino->hexagono2 = hex2;
  nuevoCamino->jugador = NULL;
  return nuevoCamino;
}

tipoVertice *crearVertice(){
  tipoVertice *nuevoVertice = (tipoVertice *)malloc(sizeof(tipoVertice));
  nuevoVertice->hexagonosAdj = NULL;
  nuevoVertice->jugador = NULL;
  nuevoVertice->poblado = false;
  nuevoVertice->ciudad = false;
  return nuevoVertice;
}

Vector *generarTerrenos(){
  Vector *terrenos = createVector(19);
  for (int i = 0; i < 4; i++){
    appendVector(terrenos, "bosque");
    appendVector(terrenos, "pradera");
    appendVector(terrenos, "cultivo");
  }
  for (int i = 0; i < 3; i++){
    appendVector(terrenos, "cantera");
    appendVector(terrenos, "colina");
  }
  appendVector(terrenos, "desierto");

  for(int i = 0; i < 3; i++){
    shuffleVector(terrenos);
  }
  
  return terrenos;
}

Vector *generarNumeros(){ //Genera los numeros de forma aleatoria para los hexagonos y sus recursos
  Vector *numeros = createVector(18);
  for (int i = 0; i < 2; i++){
    appendVector(numeros, "5");
    appendVector(numeros, "6");
    appendVector(numeros, "3");
    appendVector(numeros, "8");
    appendVector(numeros, "10");
    appendVector(numeros, "9");
    appendVector(numeros, "11");
    appendVector(numeros, "4");
  }
  appendVector(numeros, "2");
  appendVector(numeros, "12");

  for(int i = 0; i < 3; i++){
    shuffleVector(numeros);
  }
  return numeros;
}


Vector *crearTodosLosHexagonos(){ //Funcion para crear los 19 hexagonos del tablero
  Vector *terrenos = generarTerrenos();
  Vector *numeros = generarNumeros();
  Vector *hexagonos = createVector(19);
  tipoHexagono *hexagonoAux = NULL;
  int j = 0;
  for (int i = 0; i < 19; i++){
    int numero = strtol(getVector(numeros, j), NULL, 10);
    char *terreno = (char *)(getVector(terrenos, i));

    if (terreno == "desierto"){
      hexagonoAux = crearTipoHexagono(0, terreno, i + 1, true); //ID VAN DE 1 A 19, A LA HORA DE OPERARLOS COMO INDICES RESTAR 1
      j--;
    }
    else{
      hexagonoAux = crearTipoHexagono(numero, terreno, i + 1, false);
    }
    j++;
    printf("terreno: %s\n", hexagonoAux->terreno);
    printf("numero: %d\n", hexagonoAux->numero);
    printf("ID: %d\n", hexagonoAux->idHexagono);
    printf("\n");
    appendVector(hexagonos, hexagonoAux);
  }
  return hexagonos;
}
void crearTodosLosCaminos(Vector *hexagonos){ //Crea los 42 caminos que unen los hexagonos del tablero
  tipoHexagono *hexagonoAux = NULL;
  tipoCamino *caminoAux = NULL;
  int idPreestablecidos[19][6] = { //Estos ID vienen dados por la forma en la que se colocan las piezas dentro del tablero. Corresponde a la lista de adyacencia entre los hexágonos (nodos) y los caminos (arcos).
    {2, 12, 13, -1, -1, -1},
    {1, 3, 13, 14, -1, -1},
    {2, 4, 14, -1, -1, -1},
    {3, 5, 14, 15, -1, -1},
    {4, 6, 15, -1, -1, -1},
    {5, 7, 15, 16, -1, -1},
    {6, 8, 16, -1, -1, -1},
    {7, 9, 16, 17, -1, -1},
    {8, 10, 17, -1, -1, -1},
    {9, 11, 17, 18, -1, -1},
    {10, 12, 18, -1, -1, -1},
    {1, 11, 13, 18, -1, -1},
    {1, 2, 12, 14, 18, 19},
    {2, 3, 4, 13, 15, 19},
    {4, 5, 6, 14, 16, 19},
    {6, 7, 8, 15, 17, 19},
    {8, 9, 10, 16, 18, 19},
    {10, 11, 12, 13, 17, 19},
    {13, 14, 15, 16, 17, 18},
  };
  for (int i = 0; i < 19; i++){
    hexagonoAux = getVector(hexagonos, i);
    hexagonoAux->caminos = createVector(6);

    for (int j = 0; j < 6; j++){
      int ID = idPreestablecidos[i][j]; //ID de los hexagonos que se encuentran alrededor del hexagono actual desde 1 a 19
      if (ID != -1){
        tipoHexagono *hexagonoAux2 = getVector(hexagonos, ID-1);
        caminoAux = crearCamino(hexagonoAux, hexagonoAux2);
        if (caminoAux != NULL){
          appendVector(hexagonoAux->caminos, caminoAux);
          printf("SE HA CREADO LA CONEXION ENTRE EL HEXAGONO %d Y EL HEXAGONO %d\n", hexagonoAux->idHexagono, hexagonoAux2->idHexagono);
        }else printf("ERROR AL CREAR EL CAMINO");
      }
    }
  }
  return;
}
void comprobarRecorridoEntreHexagonosYCaminos(Vector *hexagonos){//Comprueba correctamente la conexion entre los hexagonos y los caminos
  tipoHexagono *hexagonoAux = NULL;
  tipoCamino *caminoAux = NULL;
  
  for (int i = 0; i < 19; i++){
    hexagonoAux = getVector(hexagonos, i);
    printf("\nSE MOSTRARAN LOS DATOS DEL HEXAGONO DE ID %d\n", hexagonoAux->idHexagono);
    printf("El numero de este hexagono es: %d\n", hexagonoAux->numero);
    printf("El terreno de este hexagono es: %s\n", hexagonoAux->terreno);
    for (int j = 0; j < 6; j++){
      if (getVector(hexagonoAux->caminos, j) != NULL){
        caminoAux = getVector(hexagonoAux->caminos, j);
        printf("El camino %d de este hexagono conecta con el hexagono %d\n", j+1, caminoAux->hexagono2->idHexagono);
      }
    }
  }

  system("pause");
  return;
}

void representacionTablero(){
    printf("           / \\     / \\     / \\\n");
    printf("          /   \\   /   \\   /   \\\n");
    printf("         /     \\ /     \\ /     \\\n");
    printf("        |        |       |       |\n");
    printf("        |        |       |       |\n");
    printf("       / \\     / \\     / \\     / \\\n");
    printf("      /   \\   /   \\   /   \\   /   \\\n");
    printf("     /     \\ /     \\ /     \\ /     \\\n");
    printf("    |        |        |        |       |\n");
    printf("    |        |        |        |       | \n");
    printf("   / \\     / \\     / \\     / \\     / \\\n");
    printf("  /   \\   /   \\   /   \\   /   \\   /   \\\n");
    printf(" /     \\ /     \\ /     \\ /     \\ /     \\\n");
    printf("|       |         |        |        |       |\n");
    printf("|       |         |        |        |       |\n");
    printf(" \\     / \\     / \\     / \\     / \\     /\n");
    printf("  \\   /   \\   /   \\   /   \\   /   \\   /\n");
    printf("   \\ /     \\ /     \\ /     \\ /     \\ /\n");
    printf("     |       |        |         |       |\n");
    printf("     |       |        |         |       |\n");
    printf("     \\     / \\     / \\     / \\     /\n");
    printf("      \\   /   \\   /   \\   /   \\   /\n");
    printf("       \\ /     \\ /     \\ /     \\ /\n");
    printf("         |        |        |       |\n");
    printf("         |        |        |       |\n");
    printf("         \\     / \\     / \\     /\n");
    printf("          \\   /   \\   /   \\   /\n");
    printf("           \\ /     \\ /     \\ /\n");
}


tipoJugador *crearJugador(char nombre[20]){
  tipoJugador *nuevoJugador = (tipoJugador *)malloc(sizeof(tipoJugador));
  nuevoJugador->puntos = 0;
  strcpy(nuevoJugador->nombre, nombre);
  nuevoJugador->recursos = createVector(20);
  nuevoJugador->edificios = createVector(20);
  return nuevoJugador;
}

Queue *crearTurnoDeJugadores(int cantidadJugadores){
  Vector *vectorTurnos = createVector(cantidadJugadores);
  tipoJugador *jugadorAux = NULL;
  char nombre[20];

  for (int i = 0; i < cantidadJugadores; i++){ //Se crean los jugadores y se agregan a un vector para luego ser mezclados
    printf("Ingrese el nombre del jugador %d: ", i+1);
    scanf("%s", nombre);
    jugadorAux = crearJugador(nombre);
    appendVector(vectorTurnos, jugadorAux);
  }
  for (int i = 0; i < 3; i++){
    shuffleVector(vectorTurnos);
  }
  Queue *turnosJugadores = queue_create();
  
  for (int i = 0; i < cantidadJugadores; i++){ //Se agregan los jugadores a una cola para poder manejar los turnos
    jugadorAux = getVector(vectorTurnos, i);
    queue_enqueue(turnosJugadores, jugadorAux);
  }
  system("cls");
  return turnosJugadores;
}

Vector *crearTableroDeJuego(){
  Vector *hexagonos = crearTodosLosHexagonos();
  crearTodosLosCaminos(hexagonos);
  representacionTablero();
  return hexagonos;
}

void crearNuevaPartida(){
  int cantidadJugadores;
  Queue *turnos = NULL;
  Vector *tablero = NULL;
  printf("Ingrese la cantidad de jugadores: ");
  scanf("%d", &cantidadJugadores);
  while (cantidadJugadores < 2 || cantidadJugadores > 4){
    printf("Ingrese una cantidad valida de jugadores: ");
    scanf("%d", &cantidadJugadores);
  }

  turnos = crearTurnoDeJugadores(cantidadJugadores);

  for (int i = 0; i < cantidadJugadores*cantidadJugadores; i++){//VER ORDEN DE JUGADORES
    printf("EL ORDEN DE JUEGO SERA EL SIGUIENTE:\n");
    tipoJugador *jugadorAux = queue_dequeue(turnos);
    printf("Jugador %d: %s\n", i+1, jugadorAux->nombre);
    queue_enqueue(turnos, jugadorAux);
  }
  tablero = crearTableroDeJuego();


  return;
}

int unDado(){
  return (rand() % 6) + 1;
}

int dosDados(){
  return unDado() + unDado();
}



void instrucciones(){
  int opcionInstrucciones;
  while (true){
    printf("\n1. Conocimientos generales\n");
    printf("2. Turnos\n");
    printf("0. Volver al menu principal\n");
    scanf("%d", &opcionInstrucciones);
    switch (opcionInstrucciones)
    {
      case 0:
        return;
      case 1:
        system("cls");
        printf("+-----------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("|Catan es un juego de estrategia que consiste en conseguir 10 puntos a traves de la construccion de edificios y la recoleccion de materiales    |\n");
        printf("|Los materiales se consiguen a traves de los hexagonos que conforman el tablero                                                                 |\n");
        printf("|Cada hexagono tiene un numero y un terreno                                                                                                     |\n");
        printf("|Los numeros del hexagono seran dados a traves de un dado                                                                                       |\n");
        printf("|Los terrenos son: 4 bosques (maderas), 3 colinas (ladrillos), 4 praderas (ovejas), 4 cultivos (trigos), 3 canteras (rocas) y 1 desierto (nada) |\n");
        printf("|Los edificios que se pueden construir son: caminos, pueblos y ciudades                                                                         |\n");
        printf("|Los caminos se construyen con 1 ladrillo y 1 madera                                                                                            |\n");
        printf("|Los pueblos se construyen con 1 ladrillo, 1 madera, 1 oveja y 1 trigo                                                                          |\n");
        printf("|Las ciudades se construyen con 2 trigos y 3 rocas                                                                                              |\n");
        printf("|Los pueblos generan 1 punto y las ciudades 2 puntos                                                                                            |\n");
        printf("|Los caminos no generan puntos                                                                                                                  |\n");
        printf("|Los pueblos generan 1 material por turno y las ciudades 2 materiales por turno                                                                 |\n");
        printf("|Los caminos no generan materiales                                                                                                              |\n");
        printf("|Los pueblos deben estar a 2 caminos de distancia entre si                                                                                      |\n");
        printf("+-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        break;

      case 2:
        system("cls");
        printf("+-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("|Para comenzar la partida:                                                                                                                  |\n");
        printf("|1. Lanzar el dado para decidir el orden de los jugadores                                                                                   |\n");
        printf("|2. El orden para colocar los primeros edificios es el siguiente: jugador 1, jugador 2, jugador 3 y jugador 4                               |\n");
        printf("|Y luego: jugador 4, jugador 3, jugador 2 y jugador 1                                                                                       |\n");
        printf("|3. Cada jugador debe de haber colocado 2 pueblos y 2 caminos en total en la posicion que desee                                             |\n");
        printf("|4. Luego de que todos los jugadores hayan colocado sus edificios, se procede a lanzar el dado                                              |\n");
        printf("|5. El ultimo jugador que haya construido su edificio sera el primero en lanzar el dado                                                     |\n");
        printf("|6. Todos los jugadores obtendran los materiales correspondientes dependiendo del numero que haya salido en el dado                         |\n");
        printf("+-------------------------------------------------------------------------------------------------------------------------------------------+\n");

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
  printf("UTILIZAR ESTE PROGRAMA EN PANTALLA COMPLETA!!\n\n");
  srand(time(NULL));
  int opcionMenuPrincipal;

  while (true){
    do{
      printf(" ------------------------\n");
      printf("|1. Crear nueva partida  |\n");
      printf("|2. Instrucciones        |\n");
      printf("|0. Salir                |\n");
      printf(" ------------------------\n");
      printf("Ingrese una opcion: ");
      scanf("%d", &opcionMenuPrincipal);
      if (opcionMenuPrincipal < 0 || opcionMenuPrincipal > 3)
        printf("Ingrese una opcion valida\n");
      printf("\n__________________________________________________________________________________________\n");
    }while (opcionMenuPrincipal < 0 || opcionMenuPrincipal > 3);

    switch (opcionMenuPrincipal)
    {
    case 0:
      printf("\nGracias por jugar\n");
      exit(EXIT_SUCCESS);
    case 1:
      system("cls");
      crearNuevaPartida();
      break;
    case 2:
      system("cls");
      instrucciones();
      break;
    case 3:
      printf("Development\n");
      
      //Vector *vector = generarNumeros();
      crearTableroDeJuego();
      //comprobarRecorridoEntreHexagonosYCaminos();
      break;
    }
  }
  return EXIT_SUCCESS;
}