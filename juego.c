#include "escape_laboratorio.h"
#include "detector_personajes.h"
#include <time.h>

/*
* Imprime la bienvenida al juego y explica las reglas
*/
void bienvenida();

/*
 *Mostrará por pantalla el bonus que obtiene el personaje que elijio el usuario.
 *Pre: El char que ingresa debe ser alguno de los siguientes: 
 	Coraje -> 'C', Blue -> 'B', Bellota -> 'S', 
 	Puro Hueso -> 'H', Pollito -> 'P' o Johnny Bravo -> 'J'.
*/
void mostrar_bonus(char personaje_elejido);

/* 
 * Función principal que se encarga de desarollar el juego.
 *Pre: El char que ingresa debe ser alguno de los siguientes: 
 	Coraje -> 'C', Blue -> 'B', Bellota -> 'S', 
 	Puro Hueso -> 'H', Pollito -> 'P' o Johnny Bravo -> 'J'.
*/
void jugar(juego_t* ptr_juego,char personaje_elejido, int nivel_inicial);

int main(){
	srand((unsigned)time(NULL));// Semilla para generar numeros aleatorios

    system("clear");
	char personaje_elegido;
	juego_t juego;

	bienvenida();
	detectar_personaje(&personaje_elegido);
	mostrar_bonus(personaje_elegido);

	inicializar_juego(&juego, personaje_elegido);
	jugar(&juego, personaje_elegido, 1);

	return 0;
}