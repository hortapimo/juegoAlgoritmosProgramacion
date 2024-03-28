#include "escape_laboratorio.h"
#include "utiles.h"
#include <time.h>
#include <string.h>

#define CORAJE   'C'
#define BLUE   'B'
#define BELLOTA  'S'
#define PURO_HUESO  'H'
#define POLLITO  'P'
#define JOHNNY_BRAVO  'J'

#define MAX_FRASE 100

#define NOMBRE_CORAJE  "Coraje el perro cobarde"
#define NOMBRE_BLUE  "Blue, de mansion foster"
#define NOMBRE_BELLOTA "Bellota, de las chicas superpoderosas"
#define NOMBRE_PURO_HUESO "Puro Hueso, de Billy y Mandy"
#define NOMBRE_POLLITO "Pollito, de la vaca y el pollito"
#define NOMBRE_JOHNNY_BRAVO "Johnny Bravo"

#define BONUS_CORAJE "Sos tan tierno que lo guardias no te atrapan!"
#define BONUS_BLUE "Por ser imaginario tendrás una segunda oportunidad si moris"
#define BONUS_BELLOTA "Por tener superpoderes tendrás una segunda oportunidad si moris"
#define BONUS_PURO_HUESO "Por no tener carne no serás afectado por las baldosas pinche"
#define BONUS_POLLITO "Por ser finito no serás afectado por las baldosas pinche"
#define BONUS_JOHNNY_BRAVO "Gracias a tu encanto los guardias no te haran daño"

const int MOVIMIENTOS_INICIALES = 15;

//Herramientas
#define MONEDA 'M'
#define LLAVE 'L'
#define INTERRUPTOR 'I'
#define BALDOSA_TRANSPORTADORA 'T'

// Obstaculo
#define BALDOSAS_PINCHE 'P'
#define BOMBA 'B'
#define GUARDIA 'G'

#define ENTRADA 'E'
#define SALIDA 'S'
#define PARED '.'
#define VACIO ' '

const int CANTIDAD_BALDOSAS_PINCHE_NIVEL_1 = 4;
const int CANTIDAD_BALDOSAS_PINCHE_NIVEL_2 = 6;
const int CANTIDAD_BALDOSAS_PINCHE_NIVEL_3 = 6;
const int CANTIDAD_BALDOSAS_PINCHE_NIVEL_4 = 10;

const int CANTIDAD_GUARDIAS_NIVEL_1 = 2;
const int CANTIDAD_GUARDIAS_NIVEL_2 = 3;
const int CANTIDAD_GUARDIAS_NIVEL_3 = 3;
const int CANTIDAD_GUARDIAS_NIVEL_4 = 4;

const bool HAY_BOMBA_NIVEL_1 = false;
const bool HAY_BOMBA_NIVEL_2 = false;
const bool HAY_BOMBA_NIVEL_3 = true;
const bool HAY_BOMBA_NIVEL_4 = true;

const bool HAY_INTERUPTOR_NIVEL_1 = false;
const bool HAY_INTERUPTOR_NIVEL_2 = false;
const bool HAY_INTERUPTOR_NIVEL_3 = true;
const bool HAY_INTERUPTOR_NIVEL_4 = true;

const int DIMENSION_NIVEL_1 = 12;
const int DIMENSION_NIVEL_2 = 17;
const int DIMENSION_NIVEL_3 = 12;
const int DIMENSION_NIVEL_4 = 17;
const int DIMENSION_MAXIMA = 17;

const int NIVEL_INICIAL = 1;		
const int ULTIMO_NIVEL = 4;

#define PERSONAJE ')'

//Colores
#define ROJO "\e[31m"
#define FGRIS "\e[47m"
#define FNEGRO "\e[40m"
#define FBLANCO "\e[107m"
#define BLANCO "\e[37m"
#define VERDE "\e[32;1m"
#define AMARILLO "\e[33m"
#define CNORMAL "\e[0m"
#define TURQUESA "\e[36;1m"
#define AZUL "\e[34m"
#define FAZUL "\e[44m"
#define VIOLETA "\e[35m"
#define SUBRAYADO "\e[4m"
#define NEGRO "\e[30m"

//movientos
#define DERECHA 'd'
#define ABAJO 's'
#define ARRIBA 'w'
#define IZQUIERDA 'a'

const static double VELOCIDAD_JUGADOR = 0.1;
const float UNIDAD_TIEMPO = 2.0;

#define JUGANDO 0
#define PERDIDO -1
#define GANADO 1

#define PERDIO_POR_BOMBA 3
#define PERDIO_POR_GUARDIA 2
#define PERDIO_POR_MOVIMIENTOS 1

void cargar_mapa(nivel_t nivel, char mapa[][DIMENSION_MAXIMA], int tope_mapa,  personaje_t personaje, int numero_nivel);

void mostrar_mapa(char mapa[DIMENSION_MAXIMA][DIMENSION_MAXIMA], int tope_mapa);

bool hay_vacio(char mapa[][DIMENSION_MAXIMA], int tope_mapa, coordenada_t posicion_nueva);

void inicializar_personaje(juego_t* ptr_juego, char tipo_personaje, int nivel_actual);

void inicializar_niveles(juego_t* ptr_juego);

bool nivel_tiene_interruptor(int nivel);

void inicializar_obstaculos(int dimension_nivel,nivel_t* ptr_nivel,int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba);

void inicializar_herramientas(int dimension_nivel, nivel_t* ptr_nivel,int cantidad_monedas,int cantidad_baldosas_tranportadoras,bool hay_interruptor);

void inicializar_SalidaYEntrada(int dimension_nivel, nivel_t* ptr_nivel);

void inicializar_baldosas_pinche(int dimension_nivel, nivel_t* ptr_nivel, int cantidad_baldosas_pinches);

void inicializar_guardias(int dimension_nivel, nivel_t* ptr_nivel, int cantidad_guardia);

void choca_llave(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento);

void choca_baldosa_pinche(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento);

void inicializar_bomba(int dimension_nivel, nivel_t* ptr_nivel, bool hay_bomba);

void inicializar_monedas(int dimension_nivel, nivel_t* ptr_nivel, int cantidad_monedas);

void inicializar_baldosas_trasportadoras( int dimension_nivel, nivel_t* ptr_nivel, int cantidad_baldosas_tranportadoras);

void inicializar_interruptor(int dimension_nivel, nivel_t* ptr_nivel, bool hay_interruptor);

void inicializar_llave(int dimension_nivel,nivel_t* ptr_nivel);

bool no_hay_lugar(nivel_t* ptr_nivel, int coordenada_columna, int coordenada_fila );

int tamanio_mapa(int nivel);

void cordenada_aleatoria(int* coordenada_fila, int* coordenada_columna, int dimension_nivel);

char recibir_movimiento();

void cambiar_posicion(personaje_t* personaje, char movimiento);

bool no_choca(juego_t juego, char moviento);

bool caracter_valido(char movimiento);

void inicializar_posicion(personaje_t personaje, char movimiento, coordenada_t* posicion_nueva);

void buscar_posicion(elemento_t vector[], int tope, int* posicion, coordenada_t posicion_nueva);

void eliminar_elemento(elemento_t vector[], int posicion, int* tope);

void reaccionar_choque(juego_t* ptr_juego, char movimiento);

void teletransportar(juego_t* ptr_juego, elemento_t vector[], int tope, coordenada_t posicion_nueva);

void mostrar_fin(juego_t juego, char estado);

bool esta_en_salida(juego_t juego);

bool esta_muerto(juego_t juego);

bool obtener_cordenada(juego_t juego, coordenada_t*  ptr_coordenada, char tipo_elemento);

void pasar_de_nivel(juego_t* ptr_juego);

bool hay_adyasentes(nivel_t nivel, int coordenada_fila ,int coordenada_columna);

bool es_primera_ves(elemento_t obstaculos[], int tope );

bool es_adyasente(coordenada_t cordenada_incognita,int coordenada_fila,int coordenada_columna);

bool nivel_tiene_bomba(int nivel);

int cantidad_guardias_mapa(juego_t juego);

int cantidad_guardias_nivel (int nivel);

int perdio_por(juego_t juego);

void choca_moneda(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento);

void choca_entrada(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento);

void choca_guardia(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento);

void mover_guardias(juego_t* ptr_juego);

void choca_bomba(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento);

void mover_guardia(elemento_t* ptr_guardia, nivel_t* ptr_nivel, int nivel, personaje_t personaje );

bool esta_personaje(int cordenada_fila, int cordernada_columna, personaje_t personaje);

void choca_salida(juego_t* ptr_juego, coordenada_t posicion_nueva);

void info_personeje(char tipo_personaje, char bonus_personaje[], char nombre_personaje[]);

bool puede_revivir(juego_t juego);

void revivir(juego_t* ptr_juego, int diferencia_movimientos);

void avisar_revivio(char tipo_personaje);

void mensaje_siguiente_nivel(int siguiente_nivel);

/* -------------------------------------------------*/

void mostrar_bonus(char personaje_elejido){
	char aux;

	char bonus_personaje[MAX_FRASE];
	char nombre_personaje[MAX_FRASE];
	info_personeje(personaje_elejido, bonus_personaje, nombre_personaje);

	system("clear");

			printf("\n");
			printf("\n");
			printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""       El Personaje que elegiste fue %s.                                          ""\t \t""\n", nombre_personaje);
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""               BONUS:                                                             ""\t \t""\n");
			printf("\t \t""       %s                                                                         ""\t \t""\n", bonus_personaje);
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""         Presione una letra mas enter para iniciar el juego.  Good luck!!         ""\t \t""\n");
			printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
			printf("\n");
			printf("\n");

			detener_el_tiempo(UNIDAD_TIEMPO);
			scanf(" %c", &aux);

	
}

void jugar(juego_t* ptr_juego,char personaje_elejido, int nivel_inicial){

	(*ptr_juego).nivel_actual = nivel_inicial;
	mostrar_juego((*ptr_juego));
	char movimiento;

	while(estado_juego(*ptr_juego) == JUGANDO){
		mover_guardias(ptr_juego);
		movimiento = recibir_movimiento();
		mover_personaje(ptr_juego, movimiento);

	}

	if (estado_juego(*ptr_juego) == GANADO) mostrar_fin(*ptr_juego, GANADO);
	else mostrar_fin(*ptr_juego, PERDIDO);

}

/*
* Verifica si el persinaje puede revivir, segun sus bonus y si ya murio
*/
bool puede_revivir(juego_t juego){
	if( ( (juego.personaje.tipo == BLUE) || (juego.personaje.tipo == BELLOTA) )  
           && (juego.personaje.murio == true ) ){
		return true;
	}

	return false;
}

/*
* Revive al personaje haciendo que vuelva a jugar de nuevo el nivel
*/
void revivir(juego_t* ptr_juego, int diferencia_movimientos){
	int nivel_actual = (*ptr_juego).nivel_actual;

	(*ptr_juego).personaje.movimientos = MOVIMIENTOS_INICIALES + diferencia_movimientos;
	(*ptr_juego).personaje.posicion.fil = (*ptr_juego).niveles[nivel_actual - 1].entrada.fil;
	(*ptr_juego).personaje.posicion.col = (*ptr_juego).niveles[nivel_actual - 1].entrada.col;
	(*ptr_juego).personaje.murio = true;

	avisar_revivio((*ptr_juego).personaje.tipo);

}

/*
* Inicializa nuevamente las posiciones de todos los guardias de modo que se muevan a alguna posición vacia
* aleatoriamente
*/
void mover_guardias(juego_t* ptr_juego){
	int nivel = (*ptr_juego).nivel_actual;

	for (int i = 0; i < (*ptr_juego).niveles[nivel-1].tope_obstaculos; i++){
		if((*ptr_juego).niveles[nivel-1].obstaculos[i].tipo == GUARDIA){
			mover_guardia(&(*ptr_juego).niveles[nivel-1].obstaculos[i], &(*ptr_juego).niveles[nivel-1], 
							nivel, (*ptr_juego).personaje);
		}
	}
	system("clear");
	mostrar_juego((*ptr_juego));
}

/*
* Inicializa la posición de una guardia en particular a una posiciñon vacia de forma aleatoria
*/
void mover_guardia(elemento_t* ptr_guardia, nivel_t* ptr_nivel, int nivel, personaje_t personaje ){
	
	int coordenada_fila, coordenada_columna;
	int dimension_nivel = tamanio_mapa(nivel);
	cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
			
	while((no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila)) 
		|| (esta_personaje(coordenada_fila, coordenada_columna, personaje)) ) {

		cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
	}
			
	coordenada_t cordenada;
	cordenada.col = coordenada_columna;
	cordenada.fil = coordenada_fila;
			
	(*ptr_guardia).posicion = cordenada;

}

/*
* Verifica si la coordenada pasada es la misma que la posición del personaje
*/
bool esta_personaje(int coordenada_fila, int coordernada_columna, personaje_t personaje){
	return((personaje.posicion.fil == coordenada_fila) && (personaje.posicion.col == coordernada_columna));

}

int estado_juego(juego_t juego){
	int retorno = JUGANDO;

	if((juego.personaje.movimientos <= 0 ) || (esta_muerto(juego)) ){
		retorno = PERDIDO;
	}
	else if (esta_en_salida(juego) && juego.nivel_actual == ULTIMO_NIVEL)
		retorno = GANADO;
	else ;

	return retorno;
}

/*
* Verifica si el personaje esta en una situación donde se lo considera muerto. Esto sucede si
* se choco a la bomba . 
*/
bool esta_muerto(juego_t juego){

	if((juego.personaje.tipo != BLUE) && (juego.personaje.tipo != BELLOTA)){
		return (juego.personaje.murio);
	}
	else if(juego.personaje.murio == true && (juego.personaje.movimientos <= 0)){
			return false;
	}

	return false;
	
}

/*
* Devuelve la cantidad de guardias que hay en ese instante en el mapa. Sirve para ver si el personaje
* esta parado arriba de un guardia, ya que en ese caso habria menos guardias de los que corresponden
* a ese nivel.
*/
int cantidad_guardias_mapa(juego_t juego){
	
	int cantidad_guardias = 0;

	int nivel = juego.nivel_actual;
	char mapa[DIMENSION_MAXIMA][DIMENSION_MAXIMA];
	int tope_mapa = tamanio_mapa(nivel);

	cargar_mapa(juego.niveles[nivel-1], mapa, tope_mapa,juego.personaje, nivel);

	for (int i = 0; i < tope_mapa; i++){
		for (int j = 0; j < tope_mapa; j++){
			if(mapa[i][j] == GUARDIA) cantidad_guardias ++;
		}
	}
	
	return cantidad_guardias;
	
}

/*
*  Devuelve la cantidad de guardias que corresponde al nivel.
*/
int cantidad_guardias_nivel (int nivel){
	int retorno;

	switch(nivel){
		case 1:
			retorno = CANTIDAD_GUARDIAS_NIVEL_1;
		break;

		case 2:
			retorno = CANTIDAD_GUARDIAS_NIVEL_2;
		break;

		case 3:
			retorno = CANTIDAD_GUARDIAS_NIVEL_3;
		break;

		case 4:
			retorno = CANTIDAD_GUARDIAS_NIVEL_4;
		break;
	}

	return retorno;
}

/*
* Verifica si el nivel correspondiente tiene una bomba.
*/
bool nivel_tiene_bomba(int nivel){
	bool retorno;

	switch(nivel){
		case 1:
			retorno = HAY_BOMBA_NIVEL_1;
		break;

		case 2:
			retorno = HAY_BOMBA_NIVEL_2;
		break;

		case 3:
			retorno = HAY_BOMBA_NIVEL_3;
		break;

		case 4:
			retorno = HAY_BOMBA_NIVEL_4;
		break;
	}

	return retorno;
}

/*
* Verifica si el personaje esta sobre la posición de la salida. La salida esta cuando el personaje 
* tiene la llave.
*/
bool esta_en_salida(juego_t juego){

	coordenada_t salida;
	obtener_cordenada(juego, &salida, SALIDA);

	if(salida.fil == juego.personaje.posicion.fil && salida.col == juego.personaje.posicion.col){
		return true;
	}
	return false;
}

/*
* Enseña por pantalla la razón por la que finalizo el juego y agradese por jugar.
*/
void mostrar_fin(juego_t juego, char estado){
	
	if (estado == GANADO){
		detener_el_tiempo(UNIDAD_TIEMPO);
			system("clear");
			printf("\n");
			printf("\n");
			printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                         !!!!!!!!!!!!GANASTESSS!!!!!!!!!!!                        ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""    Felicitaciones, te ganaste un viaje a plaza italia. Para solicitar el         ""\t \t""\n");
			printf("\t \t""    precio dirijirse a las oficinas de dubai.                                     ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
			printf("\n");
			printf("\n");
			detener_el_tiempo(UNIDAD_TIEMPO);
			detener_el_tiempo(UNIDAD_TIEMPO);
			detener_el_tiempo(UNIDAD_TIEMPO);
	}
	else{
		switch(perdio_por(juego)){
			
			case PERDIO_POR_BOMBA:
				detener_el_tiempo(UNIDAD_TIEMPO);
				system("clear");
				printf("\n");
				printf("\n");
				printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""            !!!BOOOOOOOOMMMMMMMMMMM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                 ""\t \t""\n");
				printf("\t \t""                    (ruido imaginario de bomba)                                   ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""            Te exploto la bomba y volaste en pedasitos                            ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                             GAME OVER :¬(                                        ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
				printf("\n");
				printf("\n");
				detener_el_tiempo(UNIDAD_TIEMPO);
				detener_el_tiempo(UNIDAD_TIEMPO);
				detener_el_tiempo(UNIDAD_TIEMPO);
			break;
			
			case PERDIO_POR_GUARDIA:
				detener_el_tiempo(UNIDAD_TIEMPO);
				system("clear");
				printf("\n");
				printf("\n");
				printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""        Caminabas mirando el celular y te chocaste un guardia. FuisteS!           ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                 GAME OVER :¬(                                    ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
				printf("\n");
				printf("\n");
				detener_el_tiempo(UNIDAD_TIEMPO);
				detener_el_tiempo(UNIDAD_TIEMPO);
				detener_el_tiempo(UNIDAD_TIEMPO);
			break;
		
			default:
			    system("clear");
				printf("\n");
				printf("\n");
				printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                TE QUEDASTES SIN MOVIMIENTOS!!...                                 ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                    La proxima veni mas entrenado                                 ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t""                                 GAME OVER :¬(                                    ""\t \t""\n");
				printf("\t \t""                                                                                  ""\t \t""\n");
				printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
				printf("\n");
				printf("\n");
				detener_el_tiempo(UNIDAD_TIEMPO);
				detener_el_tiempo(UNIDAD_TIEMPO);
				detener_el_tiempo(UNIDAD_TIEMPO);
		}
	}
	
	system("clear");
	printf("\n");
			printf("\n");
			printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                      Juego Finalizado!                                           ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""               Muchas gracias por probar nuestro programa!                        ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t""                                                                                  ""\t \t""\n");
			printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
			printf("\n");
			printf("\n");
}

/*
* Analiza por que perdio el personaje. 
* Devuelve PERDIO_POR_BOMBA, PERDIO_POR_GUARDIA o PERDIO_POR_MOVIENTOS 
*/
int perdio_por(juego_t juego){
	
	if(juego.personaje.murio){
		if(cantidad_guardias_nivel(juego.nivel_actual) > cantidad_guardias_mapa(juego) ){
			return PERDIO_POR_GUARDIA;
		}
		else{
			return PERDIO_POR_BOMBA;
		} 
	}

	return PERDIO_POR_MOVIMIENTOS;
}


void mover_personaje(juego_t* ptr_juego , char movimiento){

	float aux;
	system("clear");
	mostrar_juego((*ptr_juego));

	(*ptr_juego).personaje.movimientos --; //resto movimiento

	while(no_choca((*ptr_juego), movimiento)){ 
		cambiar_posicion(&(*ptr_juego).personaje, movimiento);

		system("clear");
		mostrar_juego((*ptr_juego));
		aux = (float) VELOCIDAD_JUGADOR;
		detener_el_tiempo(aux);
	}
	
	reaccionar_choque(ptr_juego, movimiento);
	
	coordenada_t salida;
	obtener_cordenada((*ptr_juego), &salida, SALIDA);
	if(estado_nivel((*ptr_juego).personaje, salida) == GANADO) pasar_de_nivel(ptr_juego);

}

/*
* Recorre la matriz que representa el mapa y busca el caracter que corresponde al tipo elemento pasado,
* la bomba por ejemplo, cuando lo encuentra inicializa la coordenada pasada por referencia con esa posicion.
* En caso de no encontrar nada devuelve false.
* Esta implementada de modo que recorre la matriz desde el 0,0 de isquierda a derecha y de arriba abajo. Al
* primer tipo de elemento que encuentra deja de buscar. 
*/
bool obtener_cordenada(juego_t juego, coordenada_t* ptr_coordenada, char tipo_elemento){
	bool encontro = false;

	int nivel = juego.nivel_actual;
	char mapa[DIMENSION_MAXIMA][DIMENSION_MAXIMA];
	int tope_mapa = tamanio_mapa(nivel);

	cargar_mapa(juego.niveles[nivel-1], mapa, tope_mapa,juego.personaje, nivel);

	for (int i = 0; (i < tope_mapa) && !encontro ; i++){
		for(int j = 0; (j < tope_mapa) &&  !encontro ; j++){
			if(mapa[i][j] == tipo_elemento){
				(*ptr_coordenada).fil = i;
				(*ptr_coordenada).col = j;
				encontro = true;
			}
		}
	}

	return encontro;
}


int estado_nivel(personaje_t personaje, coordenada_t salida){
	int retorno = JUGANDO;

	if ((personaje.posicion.fil == salida.fil) && (personaje.posicion.col == salida.col)){
		retorno = GANADO;
	}

	return retorno;
}

/*
* Se encarga de inicializar la posicion del personaje en la coordenada de entrada la siguiente nivel,
* recargar los movimientos y pasar de nivel en el juego. 
*/
void pasar_de_nivel(juego_t* ptr_juego){

	if((*ptr_juego).nivel_actual != ULTIMO_NIVEL){
		(*ptr_juego).nivel_actual ++;
		mensaje_siguiente_nivel((*ptr_juego).nivel_actual);
		inicializar_personaje (ptr_juego, (*ptr_juego).personaje.tipo ,(*ptr_juego).nivel_actual);		
		system("clear");
		mostrar_juego((*ptr_juego));
	}
}

/*
* Muestra por pantalla que paso al siguinete nivel
*/
void mensaje_siguiente_nivel(int siguiente_nivel){
		system("clear");
		printf("\n");
		printf("\n");
		printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                      Siguente nivel                              ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
		printf("\n");
		printf("\n");
		detener_el_tiempo(UNIDAD_TIEMPO);

		system("clear");
		printf("\n");
		printf("\n");
		printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                      Nivel %i.                                    ""\t \t""\n", siguiente_nivel);
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t""                                                                                  ""\t \t""\n");
		printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
		printf("\n");
		printf("\n");
		detener_el_tiempo(UNIDAD_TIEMPO);
}

/*
* Si el jugador se topa con algo que sea distinto se vacio digo que el jugador choco. Esto es lo que
* verifica esta función.
*/
bool no_choca(juego_t juego, char movimiento){
	bool retorno = true;

	int nivel = juego.nivel_actual;
	char mapa[DIMENSION_MAXIMA][DIMENSION_MAXIMA];
	int tope_mapa = tamanio_mapa(nivel);

	cargar_mapa(juego.niveles[nivel-1], mapa, tope_mapa,juego.personaje, nivel);

	coordenada_t posicion_nueva;
	inicializar_posicion(juego.personaje, movimiento, &posicion_nueva);

	retorno = hay_vacio(mapa, tope_mapa,posicion_nueva);

	return retorno;
}

/*
* realiza la acción que corresponde cunado el personaje se choca la moneda
*/
void choca_moneda(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento){
	int posicion=0;
	(*ptr_juego).personaje.movimientos ++;
	(*ptr_juego).personaje.posicion = posicion_nueva;
			
	buscar_posicion((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].herramientas,
			(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_herramientas, &posicion, posicion_nueva);

	eliminar_elemento((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].herramientas, 
			posicion, &(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_herramientas);
			
	(*ptr_juego).personaje.movimientos ++;// Compenso el movimiento que se resta al llamar mover_personaje
	mover_personaje(ptr_juego, movimiento);
}

/*
* realiza la acción que corresponde cunado el personaje se choca la llave
*/
void choca_llave(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento){
	int posicion=0;
	(*ptr_juego).personaje.tiene_llave = true;
	(*ptr_juego).personaje.posicion = posicion_nueva;
			
	buscar_posicion((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].herramientas,
				(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_herramientas, &posicion, posicion_nueva);

	eliminar_elemento((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].herramientas, 
				posicion, &(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_herramientas);

	(*ptr_juego).personaje.movimientos ++;// Compenso el movimiento que se resta al llamar mover_personaje
	mover_personaje(ptr_juego, movimiento);
}

/*
* realiza la acción que corresponde cuanado el personaje se choca el interruptor
*/
void choca_interruptor(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento){
	int posicion=0;
	(*ptr_juego).personaje.presiono_interruptor = true;
	(*ptr_juego).personaje.posicion = posicion_nueva;
			
	buscar_posicion((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].herramientas,
			(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_herramientas, &posicion, posicion_nueva);

	eliminar_elemento((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].herramientas, 
				posicion, &(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_herramientas);

	(*ptr_juego).personaje.movimientos ++;// Compenso el movimiento que se resta al llamar mover_personaje
	mover_personaje(ptr_juego, movimiento);
}

/*
* realiza la acción que corresponde cunado el personaje se choca la baldosa pinche
*/
void choca_baldosa_pinche(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento){
	if ( ((*ptr_juego).personaje.tipo != PURO_HUESO) && ((*ptr_juego).personaje.tipo != POLLITO) ){
		(*ptr_juego).personaje.movimientos -= 2;
	}

	(*ptr_juego).personaje.posicion = posicion_nueva;

	(*ptr_juego).personaje.movimientos ++;// Compenso el movimiento que se resta al llamar mover_personaje
	mover_personaje(ptr_juego, movimiento);
}

/*
* realiza la acción que corresponde cunado el personaje se choca la entrada
*/
void choca_entrada(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento){
	(*ptr_juego).personaje.posicion = posicion_nueva;
	(*ptr_juego).personaje.movimientos ++;// Compenso el movimiento que se resta al llamar mover_personaje
	mover_personaje(ptr_juego, movimiento);
}

/*
* realiza la acción que corresponde cunado el personaje se choca el guardia
*/
void choca_guardia(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento){
	int diferencia_movimientos = 0;
	
	if( ((*ptr_juego).personaje.tipo == JOHNNY_BRAVO) || ((*ptr_juego).personaje.tipo == CORAJE )){
		(*ptr_juego).personaje.posicion = posicion_nueva;
		(*ptr_juego).personaje.movimientos ++;// Compenso el movimiento que se resta al llamar mover_personaje
		mover_personaje(ptr_juego, movimiento);
	}
	else if( ( (*ptr_juego).personaje.murio == false ) && 
		(  (*ptr_juego).personaje.tipo == BLUE  || (*ptr_juego).personaje.tipo == BELLOTA ) ){

		revivir(ptr_juego, diferencia_movimientos);
	}
	else{
		(*ptr_juego).personaje.posicion = posicion_nueva;
		(*ptr_juego).personaje.movimientos = 0; //le saco los movimientos
		(*ptr_juego).personaje.murio = true; 
		system("clear");
		mostrar_juego(*ptr_juego);
	}

}

/*
* realiza la acción que corresponde cunado el personaje se choca la bomba
*/
void choca_bomba(juego_t* ptr_juego, coordenada_t posicion_nueva, char movimiento){
	int diferencia_movimientos = 0;
	int aux;
	
	int posicion=0;
	(*ptr_juego).personaje.posicion = posicion_nueva;
	buscar_posicion((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].obstaculos,
			(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_obstaculos, &posicion, posicion_nueva);

	eliminar_elemento((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].obstaculos, 
			posicion, &(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_obstaculos);

	if( ( (*ptr_juego).personaje.murio == false ) && 
		(  (*ptr_juego).personaje.tipo == BLUE  || (*ptr_juego).personaje.tipo == BELLOTA ) ){
		aux = (*ptr_juego).personaje.movimientos;

		(*ptr_juego).personaje.movimientos ++;// Compenso el movimiento que se resta al llamar mover_personaje
		mover_personaje(ptr_juego, movimiento);
		diferencia_movimientos = (*ptr_juego).personaje.movimientos - aux;
		revivir(ptr_juego, diferencia_movimientos);
	}
	else{
		(*ptr_juego).personaje.murio = true;
		(*ptr_juego).personaje.movimientos = 0;
	}
	system("clear");
	mostrar_juego(*ptr_juego);
}

/*
* realiza la acción que corresponde cunado el personaje se choca la salida
*/
void choca_salida(juego_t* ptr_juego, coordenada_t posicion_nueva){
	(*ptr_juego).personaje.posicion = posicion_nueva;
	system("clear");
	mostrar_juego(*ptr_juego);
	detener_el_tiempo(UNIDAD_TIEMPO);
}
/*
* Cuando el personaje se encuentra con algo distinto a vacio, una pared por ejemplo, debe reaccionar
* segun el efecto del elemento que se choco (frenar en el caso de la pared).
*/
void reaccionar_choque(juego_t* ptr_juego, char movimiento){

	int nivel = (*ptr_juego).nivel_actual;
	char mapa[DIMENSION_MAXIMA][DIMENSION_MAXIMA];
	int tope_mapa = tamanio_mapa(nivel);

	cargar_mapa((*ptr_juego).niveles[nivel-1], mapa, tope_mapa,(*ptr_juego).personaje, nivel);

	coordenada_t posicion_nueva;
	inicializar_posicion((*ptr_juego).personaje, movimiento, &posicion_nueva);

	switch(mapa[posicion_nueva.fil][posicion_nueva.col]){

		case MONEDA:
			choca_moneda(ptr_juego, posicion_nueva, movimiento);
		break;

		case LLAVE:
			choca_llave(ptr_juego, posicion_nueva, movimiento);
		break;

		case INTERRUPTOR:
			choca_interruptor(ptr_juego, posicion_nueva, movimiento);
		break;

		case BALDOSAS_PINCHE:
			choca_baldosa_pinche(ptr_juego, posicion_nueva, movimiento);
		break;

		case ENTRADA:
			choca_entrada(ptr_juego, posicion_nueva, movimiento);
		break;

		case BALDOSA_TRANSPORTADORA:
			teletransportar(ptr_juego, (*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].herramientas,
							(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_herramientas, posicion_nueva);
		break;

		case GUARDIA:
		 	choca_guardia(ptr_juego, posicion_nueva, movimiento);
		break;

		case BOMBA:
			choca_bomba(ptr_juego, posicion_nueva, movimiento);
		break;

		case SALIDA:
			choca_salida(ptr_juego, posicion_nueva);
		break;

		case PARED:
		break;


	}

}

/*
* Mueve el personaje a la posición de la siguiente baldosa transportadora que se encuentre en el 
* vector de herramientas.
*/
void teletransportar(juego_t* ptr_juego, elemento_t vector[], int tope, coordenada_t posicion_nueva){
	coordenada_t posicion_baldosa;

	int posicion;
	bool encontro = false;

	buscar_posicion((*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].herramientas,
			(*ptr_juego).niveles[(*ptr_juego).nivel_actual-1].tope_herramientas, &posicion, posicion_nueva);
//((vector[i].posicion.fil != posicion_nueva.fil) && (vector[i].posicion.col != posicion_nueva.col))
	int i = posicion+1;
	while( (i < tope) && !encontro ){
		if((vector[i].tipo == BALDOSA_TRANSPORTADORA)){
		 	posicion_baldosa.fil =vector[i].posicion.fil;
		 	posicion_baldosa.col =vector[i].posicion.col;
		 	encontro = true;
		}
		i++;
	}

	if(!encontro){
		for(i = 0; !encontro; i++){
		if((vector[i].tipo == BALDOSA_TRANSPORTADORA) && 
			((vector[i].posicion.fil != posicion_nueva.fil) && (vector[i].posicion.col != posicion_nueva.col)) ){
		 	posicion_baldosa.fil =vector[i].posicion.fil;
		 	posicion_baldosa.col =vector[i].posicion.col;
		 	encontro = true;
		}
	}
	}

	(*ptr_juego).personaje.posicion = posicion_baldosa;

	system("clear");
	mostrar_juego(*ptr_juego);
	
}

/*
* Dado un vector de elementos_t, busca el elemento que tenga la misma posición que la posición_nueva
* y devuelve la posición de ese elemento en el vector.
*/
void buscar_posicion(elemento_t vector[], int tope, int* posicion, coordenada_t posicion_nueva){

	for(int i = 0; i < tope; i++){
		if((vector[i].posicion.fil == posicion_nueva.fil && vector[i].posicion.col == posicion_nueva.col)){
		 	(*posicion) = i;
		}
	}
	
}

/*
* Dado un vector de elementos_t, elimina el elemento que se encuentre en la posición pasada. Luego
* modifica el vector de modo que no queden espacios vacios.
*/
void eliminar_elemento(elemento_t vector[], int posicion, int* tope){

	for(int i = posicion; i < *tope-1; i++){
		vector[i]=vector[i+1];
	}
	(*tope)--;
}

/*
* Dado un variable tipo coordenada_t, pasada por referencia, la inicializa segun el movimiento 
* que ingreso el usuario y la posición actual del personaje. Si el personaje esta en la posición 1,1
* y el usuario ingresa w(meverse asia arriba), la nueva posición será 2,1.
*/
void inicializar_posicion(personaje_t personaje, char movimiento, coordenada_t* posicion_nueva){
	switch(movimiento){
		case ARRIBA:
			(*posicion_nueva).fil = (personaje).posicion.fil - 1;
			(*posicion_nueva).col = (personaje).posicion.col;
		break;

		case ABAJO:
			(*posicion_nueva).fil = (personaje).posicion.fil + 1;
			(*posicion_nueva).col = (personaje).posicion.col;
		break;

		case DERECHA:
			(*posicion_nueva).fil = (personaje).posicion.fil;
			(*posicion_nueva).col = (personaje).posicion.col + 1;
		break;

		case IZQUIERDA:
			(*posicion_nueva).fil = (personaje).posicion.fil;
			(*posicion_nueva).col = (personaje).posicion.col - 1;
		break;

	}
}

/*
* Verifica si en la posiciñon en la que esta parado el personaje hay un caracter VACIO.
*/
bool hay_vacio(char mapa[][DIMENSION_MAXIMA], int tope_mapa, coordenada_t posicion_nueva){

	if (mapa[posicion_nueva.fil][posicion_nueva.col] != VACIO)
		return false;
	else return true;
}

/*
* Le pide al usuario el ingreso de un caracter valido para que el personaje pueda moverse
* Pre : el caracter debe ser a,s,d o w. En caso contrario se le pedira nuevamente el ingreso
*/
char recibir_movimiento(){
	char movimiento;
	printf("\t\t Ingresa a (izquirda) ,s (abajo) ,d (derecha) o w (arriba) para moverte \n");
	scanf(" %c", &movimiento);

	while(!caracter_valido(movimiento)){
		printf("\t\tLe erraste de tecla papafrita!, mete a,s,d o w \n");
		scanf(" %c", &movimiento);
	}

	return movimiento;
}


/*
* Verfica si el caracter ingresado por el usuario es uno de los caracteres definidos para moverse (a,s,d o w).
*/

bool caracter_valido(char movimiento){
	return(movimiento == 'a' || movimiento == 's' || movimiento =='d'|| movimiento == 'w');
}

void inicializar_juego(juego_t* ptr_juego , char tipo_personaje){
 
	inicializar_niveles(ptr_juego);
	(*ptr_juego).nivel_actual = NIVEL_INICIAL;
	inicializar_personaje (ptr_juego, tipo_personaje,(*ptr_juego).nivel_actual);

}

/*
* Se encarga de mover la posición del personaje a la nueva posición correspondiente.
*/
void cambiar_posicion(personaje_t* ptr_personaje, char movimiento){
	
	coordenada_t posicion_nueva;
	inicializar_posicion((*ptr_personaje), movimiento, &posicion_nueva);

	(*ptr_personaje).posicion = posicion_nueva;

}

/*
*Dado un juego, completa los campos de su personaje.
*Pre: el tipo_personaje debe ser alguno de los siguientes: 
 	Coraje -> 'C', Blue -> 'B', Bellota -> 'S', 
 	Puro Hueso -> 'H', Pollito -> 'P' o Johnny Bravo -> 'J'.
*/
void inicializar_personaje(juego_t* ptr_juego, char tipo_personaje, int nivel_actual){

	(*ptr_juego).personaje.tipo = tipo_personaje;
	(*ptr_juego).personaje.movimientos = MOVIMIENTOS_INICIALES;

	(*ptr_juego).personaje.tiene_llave = false;

	switch(nivel_actual){
		case 1:
			if(HAY_BOMBA_NIVEL_1) (*ptr_juego).personaje.presiono_interruptor = false;
			else (*ptr_juego).personaje.presiono_interruptor = true;
		break;

		case 2:
			if(HAY_BOMBA_NIVEL_2) (*ptr_juego).personaje.presiono_interruptor = false;
			else (*ptr_juego).personaje.presiono_interruptor = true;
		break;

		case 3:
			if(HAY_BOMBA_NIVEL_3) (*ptr_juego).personaje.presiono_interruptor = false;
			else (*ptr_juego).personaje.presiono_interruptor = true;
		break;

		case 4:
			if(HAY_BOMBA_NIVEL_4) (*ptr_juego).personaje.presiono_interruptor = false;
			else (*ptr_juego).personaje.presiono_interruptor = true;
		break;

	}

	(*ptr_juego).personaje.posicion.fil = (*ptr_juego).niveles[nivel_actual-1].entrada.fil;
	(*ptr_juego).personaje.posicion.col = (*ptr_juego).niveles[nivel_actual-1].entrada.col;

}

/*
*inicializa todos los niveles del juego
*/
void inicializar_niveles(juego_t* ptr_juego){
	int nivel_1 = 1;
	int nivel_2 = 2;
	int nivel_3 = 3;
	int nivel_4 = 4;

	

	inicializar_nivel(&(*ptr_juego).niveles[nivel_1-1], nivel_1,CANTIDAD_BALDOSAS_PINCHE_NIVEL_1 , CANTIDAD_GUARDIAS_NIVEL_1, HAY_BOMBA_NIVEL_1);
	inicializar_nivel(&(*ptr_juego).niveles[nivel_2-1], nivel_2, CANTIDAD_BALDOSAS_PINCHE_NIVEL_2, CANTIDAD_GUARDIAS_NIVEL_2, HAY_BOMBA_NIVEL_2);
	inicializar_nivel(&(*ptr_juego).niveles[nivel_3-1], nivel_3, CANTIDAD_BALDOSAS_PINCHE_NIVEL_3, CANTIDAD_GUARDIAS_NIVEL_3, HAY_BOMBA_NIVEL_3);
	inicializar_nivel(&(*ptr_juego).niveles[nivel_4-1], nivel_4, CANTIDAD_BALDOSAS_PINCHE_NIVEL_4, CANTIDAD_GUARDIAS_NIVEL_4, HAY_BOMBA_NIVEL_4);

}

void inicializar_nivel(nivel_t* ptr_nivel, int numero_nivel, int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba){

	int dimension_nivel = tamanio_mapa(numero_nivel);
	int cantidad_monedas = cantidad_baldosas_pinches / 2;
	int cantidad_baldosas_tranportadoras = cantidad_guardia;
	bool hay_interruptor = hay_bomba;

	(*ptr_nivel).tope_herramientas = 0;
	(*ptr_nivel).tope_obstaculos = 0;

	obtener_paredes(numero_nivel, (*ptr_nivel).paredes, &(*ptr_nivel).tope_paredes);
	inicializar_obstaculos(dimension_nivel, ptr_nivel, cantidad_baldosas_pinches, cantidad_guardia, hay_bomba);
	inicializar_herramientas(dimension_nivel, ptr_nivel, cantidad_monedas, cantidad_baldosas_tranportadoras, hay_interruptor);
	inicializar_SalidaYEntrada(dimension_nivel, ptr_nivel);
}

/*
*Carga el vector de obstaculo de la estructura nivel
*/
void inicializar_obstaculos(int dimension_nivel, nivel_t* ptr_nivel,int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba){
	
	inicializar_baldosas_pinche(dimension_nivel, ptr_nivel ,cantidad_baldosas_pinches);
	inicializar_guardias(dimension_nivel, ptr_nivel ,cantidad_guardia);
	inicializar_bomba(dimension_nivel, ptr_nivel ,hay_bomba);

}

/*
*Carga el vector de oçherramientas de la estructura nivel
*/
void inicializar_herramientas(int dimension_nivel, nivel_t* ptr_nivel,int cantidad_monedas,int cantidad_baldosas_tranportadoras,bool hay_interruptor){

	inicializar_monedas(dimension_nivel,ptr_nivel ,cantidad_monedas);
	inicializar_baldosas_trasportadoras(dimension_nivel,ptr_nivel ,cantidad_baldosas_tranportadoras);
	inicializar_interruptor(dimension_nivel, ptr_nivel ,hay_interruptor);
	inicializar_llave(dimension_nivel, ptr_nivel);

}

/*
*Carga el la salida y entrada de la estructura nivel
*/
void inicializar_SalidaYEntrada(int dimension_nivel, nivel_t* ptr_nivel){

		int coordenada_fila, coordenada_columna;

		cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
	
		while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila)){
			cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
		}
			
		coordenada_t cordenada_salida;
		cordenada_salida.col = coordenada_columna;
		cordenada_salida.fil = coordenada_fila;

		(*ptr_nivel).salida =cordenada_salida;
		
		while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila) ||
		((*ptr_nivel).salida.col == coordenada_columna && (*ptr_nivel).salida.fil == coordenada_fila)){

			cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
		}	
		
		coordenada_t cordenada_entrada;
		cordenada_entrada.col = coordenada_columna;
		cordenada_entrada.fil = coordenada_fila;

		(*ptr_nivel).entrada = cordenada_entrada;
}

/*
*Carga en el vector de elementos obstaculos, las baldosas pinche del nivel que es pasado, de modo que la ubicación de las baldosas
no se superponga con la ubicación de alguna pared u otro elemento. 
*/
void inicializar_baldosas_pinche( int dimension_nivel, nivel_t* ptr_nivel, int cantidad_baldosas_pinches){

		
		int coordenada_fila, coordenada_columna;

		cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
		
		for(int contador = 0; contador < cantidad_baldosas_pinches; contador++){
			elemento_t baldosa_pinche;
			baldosa_pinche.tipo = BALDOSAS_PINCHE;
			
			while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila) || 
				!hay_adyasentes((*ptr_nivel), coordenada_fila, coordenada_columna)){

				cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
			}
	
			coordenada_t cordenada;
			cordenada.col = coordenada_columna;
			cordenada.fil = coordenada_fila;
			baldosa_pinche.posicion = cordenada;

			(*ptr_nivel).obstaculos[(*ptr_nivel).tope_obstaculos] = baldosa_pinche;
			(*ptr_nivel).tope_obstaculos ++;
		}
}

/*
*  Genera una cordenada aleatoria, modificando las cordenadas pasadas por referencia.
*/
void cordenada_aleatoria(int* coordenada_fila, int* coordenada_columna, int dimension_nivel){
	
	*coordenada_columna = (rand()) % dimension_nivel;
	*coordenada_fila = (*coordenada_columna + rand()) % dimension_nivel;
}

/*
* Verifica si hay baldosas pinche adyasentes
*/
bool hay_adyasentes(nivel_t nivel, int coordenada_fila ,int coordenada_columna){
	bool retorno = false;
	bool salir = false;

	if(!es_primera_ves(nivel.obstaculos, nivel.tope_obstaculos)){
		for(int i = 0; i < (nivel).tope_obstaculos && salir == false; i++){
			if( (nivel.obstaculos[i].tipo == BALDOSAS_PINCHE) &&
			 (es_adyasente(nivel.obstaculos[i].posicion, coordenada_fila, coordenada_columna)) ){
				retorno = true;
				salir = true;
			}
		}
	}
	else retorno = true;
	

	return retorno;
}

/*
* Verifica si es el primer elemento de ese tipo que se carga en el vector.
*/
bool es_primera_ves(elemento_t obstaculos[], int tope ){
	bool retorno = true;
	for(int i = 0; i < tope; i++){
		switch(obstaculos[i].tipo){
			case BALDOSAS_PINCHE:
				if(obstaculos[i].tipo == BALDOSAS_PINCHE){
					retorno = false;
				}
			break;

			case BALDOSA_TRANSPORTADORA:
				if(obstaculos[i].tipo == BALDOSA_TRANSPORTADORA){
					retorno = false;
				}
			break;
		}
	}

	return retorno;
}

/*
* Verifica si la cordenada pasada es adyasente a otra dada.
*/
bool es_adyasente(coordenada_t cordenada_incognita,int coordenada_fila,int coordenada_columna){
	bool retorno = false;

	if( (cordenada_incognita.fil == coordenada_fila) && 
	( (cordenada_incognita.col == coordenada_columna +1) || 	(cordenada_incognita.col == coordenada_columna - 1) ) ){
		retorno = true;
	}
	else if ( (cordenada_incognita.col == coordenada_columna) && 
	( (cordenada_incognita.fil == coordenada_fila +1) || 	(cordenada_incognita.fil == coordenada_fila - 1) ) ){
		retorno = true;
	}
	else ;

	return retorno;
}

/*
*Carga en el vector de elementos herrameintas, las monedas del nivel que es pasado, de modo que la ubicación de las monedas
no se superponga con la ubicación de alguna pared u otro elemento. 
*/
void inicializar_monedas(int dimension_nivel, nivel_t* ptr_nivel, int cantidad_monedas){

		
		int coordenada_fila, coordenada_columna;

		cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
		
		for(int contador = 0; contador < cantidad_monedas; contador++){
			elemento_t moneda;
			moneda.tipo = MONEDA;

			while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila)){
				cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
			}
			
			coordenada_t cordenada;
			cordenada.col = coordenada_columna;
			cordenada.fil = coordenada_fila;
			
			moneda.posicion = cordenada;

			(*ptr_nivel).herramientas[(*ptr_nivel).tope_herramientas] = moneda;
			(*ptr_nivel).tope_herramientas ++;
		}
}


void inicializar_guardias( int dimension_nivel, nivel_t* ptr_nivel, int cantidad_guardia){

		
		int coordenada_fila, coordenada_columna;

		cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
		
		for(int contador = 0; contador < cantidad_guardia; contador++){	
			elemento_t guardia;
			guardia.tipo = GUARDIA;

			while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila)){
				cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
			}
			
			coordenada_t cordenada;
			cordenada.col = coordenada_columna;
			cordenada.fil = coordenada_fila;
			
			guardia.posicion = cordenada;

			(*ptr_nivel).obstaculos[(*ptr_nivel).tope_obstaculos] = guardia;
			(*ptr_nivel).tope_obstaculos ++;
		}
}

/*
*Carga en el vector de elementos herrameintas, las baldosas transportadoras del nivel que es pasado, de modo que la ubicación de las baldosas transportadoras
no se superponga con la ubicación de alguna pared u otro elemento. 
*/
void inicializar_baldosas_trasportadoras( int dimension_nivel, nivel_t* ptr_nivel, int cantidad_baldosas_tranportadoras){

		int coordenada_fila, coordenada_columna;

		cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
		
		for(int contador = 0; contador < cantidad_baldosas_tranportadoras; contador++){
			
			elemento_t baldosa_trasportadora;
			baldosa_trasportadora.tipo = BALDOSA_TRANSPORTADORA;

			while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila)){
				cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
			}
			
			coordenada_t cordenada;
			cordenada.col = coordenada_columna;
			cordenada.fil = coordenada_fila;
			
			baldosa_trasportadora.posicion = cordenada;

			(*ptr_nivel).herramientas[(*ptr_nivel).tope_herramientas] = baldosa_trasportadora;
			(*ptr_nivel).tope_herramientas ++;
		}
}

/*
*Carga en el vector de elementos obstaculos, la bomba del nivel que es pasado, de modo que la ubicación de la bomba
no se superponga con la ubicación de alguna pared u otro elemento. 
*/
void inicializar_bomba(int dimension_nivel, nivel_t* ptr_nivel, bool hay_bomba){

		if (hay_bomba){
			int coordenada_fila, coordenada_columna;

			cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
	
			elemento_t bomba;
			bomba.tipo = BOMBA;

			while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila)){
				cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
			}
			
			coordenada_t cordenada;
			cordenada.col = coordenada_columna;
			cordenada.fil = coordenada_fila;
			
			bomba.posicion = cordenada;
			(*ptr_nivel).obstaculos[(*ptr_nivel).tope_obstaculos] = bomba;
			(*ptr_nivel).tope_obstaculos ++;
		}

}

/*
*Carga en el vector de elementos herrameintas, el interruptor del nivel que es pasado, de modo que la ubicación del interruptor
no se superponga con la ubicación de alguna pared u otro elemento. 
*/
void inicializar_interruptor(int dimension_nivel, nivel_t* ptr_nivel, bool hay_interruptor){

		if (hay_interruptor){
			
			int coordenada_fila, coordenada_columna;

			cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
	
			elemento_t interruptor;
			interruptor.tipo = INTERRUPTOR;

			while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila)){
				cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
			}
			
			coordenada_t cordenada;
			cordenada.col = coordenada_columna;
			cordenada.fil = coordenada_fila;
			
			interruptor.posicion = cordenada;
			(*ptr_nivel).herramientas[(*ptr_nivel).tope_herramientas] = interruptor;
			(*ptr_nivel).tope_herramientas ++;
		}

}

/*
*Carga en el vector de elementos herrameintas, la llave del nivel que es pasado, de modo que la ubicación de la llave
no se superponga con la ubicación de alguna pared u otro elemento. 
*/
void inicializar_llave(int dimension_nivel,nivel_t* ptr_nivel){

	int coordenada_fila, coordenada_columna;

	cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
			
	elemento_t llave;
	llave.tipo = LLAVE;

	while(no_hay_lugar(ptr_nivel, coordenada_columna,coordenada_fila)){
		cordenada_aleatoria(&coordenada_fila, &coordenada_columna, dimension_nivel);
		}
			
		coordenada_t cordenada;
		cordenada.col = coordenada_columna;
		cordenada.fil = coordenada_fila;
			
		llave.posicion = cordenada;
		(*ptr_nivel).herramientas[(*ptr_nivel).tope_herramientas] = llave;
		(*ptr_nivel).tope_herramientas ++;
}

/*
*Verifica si en la posición que se pasa por parametro ya hay una pared. 
*/
bool no_hay_lugar(nivel_t* ptr_nivel, int coordenada_columna, int coordenada_fila ){
	bool retorno = false;
	bool salir = false;

	// veo si no hay pared
	for(int i = 0; i < MAX_PAREDES && salir == false; i++){
		if( ((*ptr_nivel).paredes[i].fil == coordenada_fila ) && ((*ptr_nivel).paredes[i].col == coordenada_columna ) ){
			retorno = true;
			salir = true;
		}
	}
	// veo si no hay obstaculo
	
	for(int i = 0; i < (*ptr_nivel).tope_obstaculos && salir == false; i++){
		if( ((*ptr_nivel).obstaculos[i].posicion.fil == coordenada_fila ) && ((*ptr_nivel).obstaculos[i].posicion.col == coordenada_columna ) ){
			retorno = true;
			salir = true;
		}
	}
	// veo si no hay herramienta
	
	for(int i = 0; i < (*ptr_nivel).tope_herramientas && salir == false; i++){
		if( ((*ptr_nivel).herramientas[i].posicion.fil == coordenada_fila ) && ((*ptr_nivel).herramientas[i].posicion.col == coordenada_columna ) ){
			retorno = true;
			salir = true;
		}
	}

	// veo si no hay salida o entrada

	if( ((*ptr_nivel).salida.fil == coordenada_fila) && ((*ptr_nivel).salida.col == coordenada_columna) ) {
		retorno = true;
	}
	else if( ((*ptr_nivel).entrada.fil == coordenada_fila) && ((*ptr_nivel).entrada.col == coordenada_columna)){
		retorno = true;
	}

	return retorno;
}

void mostrar_juego(juego_t juego){
	
	char bonus_personaje[MAX_FRASE];
	char nombre_personaje[MAX_FRASE];
	info_personeje(juego.personaje.tipo, bonus_personaje, nombre_personaje);


	int nivel = juego.nivel_actual;
	char mapa[DIMENSION_MAXIMA][DIMENSION_MAXIMA];
	int tope_mapa = tamanio_mapa(nivel);

	
	printf("\n\t\tPersonaje: %s, \t Bonus : %s \n \t\t Nivel : %i ;\t Cantidad de movimientos: %i \n", nombre_personaje, bonus_personaje, nivel, juego.personaje.movimientos);
	cargar_mapa(juego.niveles[nivel-1], mapa, tope_mapa,juego.personaje, nivel);
	mostrar_mapa(mapa, tope_mapa);

}

/*
* Inicializa los strings bonus_personaje y nombre_personaje segun el tipo de personaje que es pasado.
*/
void info_personeje(char tipo_personaje, char bonus_personaje[], char nombre_personaje[]){
	
	switch(tipo_personaje){
		case CORAJE:
		strcpy(bonus_personaje, BONUS_CORAJE);
		strcpy(nombre_personaje, NOMBRE_CORAJE);
		break;
		
		case JOHNNY_BRAVO:
			strcpy(bonus_personaje, BONUS_JOHNNY_BRAVO);
			strcpy(nombre_personaje, NOMBRE_JOHNNY_BRAVO);
		break;
		
		case PURO_HUESO:
			strcpy(bonus_personaje, BONUS_PURO_HUESO);
			strcpy(nombre_personaje, NOMBRE_PURO_HUESO);
		break;
		
		case POLLITO:
			strcpy(bonus_personaje, BONUS_POLLITO);
			strcpy(nombre_personaje, NOMBRE_POLLITO);;
		break;
		
		case BLUE:
			strcpy(bonus_personaje, BONUS_BLUE);
			strcpy(nombre_personaje, NOMBRE_BLUE);
		break;
		
		case BELLOTA:
			strcpy(bonus_personaje, BONUS_BELLOTA);
			strcpy(nombre_personaje, NOMBRE_BELLOTA);
		break;

	}
}

/*
* Segun el nivel pasado devuelve la dimensión del mapa del nivel correspondiente
* Pre: El nivel debe estar dentro de 1 y 4 inclusives.
*/
int tamanio_mapa(int nivel){
	int retorno;

	switch(nivel){
		case 1:
		retorno = DIMENSION_NIVEL_1;
		break;

		case 2:
		retorno = DIMENSION_NIVEL_2;
		break;

		case 3:
		retorno = DIMENSION_NIVEL_3;
		break;

		case 4:
		retorno = DIMENSION_NIVEL_4;
		break;
	}

	return retorno;
}

/* 
* Verififca si el nivel tiene interrtor
*/
bool nivel_tiene_interruptor(int nivel){
	switch(nivel){
		case 1:
			return HAY_INTERUPTOR_NIVEL_1;
		break;

		case 2:
			return HAY_INTERUPTOR_NIVEL_2;
		break;

		case 3:
			return HAY_INTERUPTOR_NIVEL_3;
		break;

		case 4:
			return HAY_INTERUPTOR_NIVEL_4;
		break;

		default:
			return false;
	}
}

/*
* Se encarga de insertar los caracteres correspondientes a la matriz que representa el mapa.
*/
void cargar_mapa(nivel_t nivel,char mapa[DIMENSION_MAXIMA][DIMENSION_MAXIMA], int tope_mapa, personaje_t personaje, int numero_nivel){
	
	// Cargo con Vacio
	for(int i = 0; i < tope_mapa; i++){
		for(int j = 0; j < tope_mapa; j++){
			mapa[i][j] = VACIO;
		}
	}
	
	// Cargo paredes
	for(int i = 0; i < nivel.tope_paredes; i++){
		mapa[nivel.paredes[i].fil][nivel.paredes[i].col] = PARED;
	}

	//Cargo Herramientas
	for(int i = 0; i < nivel.tope_herramientas; i++){

		if (nivel.herramientas[i].tipo == MONEDA)
			mapa[nivel.herramientas[i].posicion.fil][nivel.herramientas[i].posicion.col] = MONEDA;
		
		else if (nivel.herramientas[i].tipo == BALDOSA_TRANSPORTADORA)
			mapa[nivel.herramientas[i].posicion.fil][nivel.herramientas[i].posicion.col] = BALDOSA_TRANSPORTADORA;
		
		else if (nivel.herramientas[i].tipo == INTERRUPTOR)
			mapa[nivel.herramientas[i].posicion.fil][nivel.herramientas[i].posicion.col] = INTERRUPTOR;

		else if ((nivel.herramientas[i].tipo == LLAVE && personaje.presiono_interruptor) || 
				((nivel.herramientas[i].tipo == LLAVE) && !nivel_tiene_interruptor(numero_nivel)))
			mapa[nivel.herramientas[i].posicion.fil][nivel.herramientas[i].posicion.col] = LLAVE;
		
		else ;
	}

	//Cargo Obstaculos
	for(int i = 0; i < nivel.tope_obstaculos; i++){

		if (nivel.obstaculos[i].tipo == BALDOSAS_PINCHE)
			mapa[nivel.obstaculos[i].posicion.fil][nivel.obstaculos[i].posicion.col] = BALDOSAS_PINCHE;
		
		else if (nivel.obstaculos[i].tipo == GUARDIA)
			mapa[nivel.obstaculos[i].posicion.fil][nivel.obstaculos[i].posicion.col] = GUARDIA;
		
		else{
			mapa[nivel.obstaculos[i].posicion.fil][nivel.obstaculos[i].posicion.col] = BOMBA;
		} 

	}

	//Cargo Entrada y quisas Salida
	mapa[nivel.entrada.fil][nivel.entrada.col] = ENTRADA;

	if (personaje.tiene_llave == true)
	 	mapa[nivel.salida.fil][nivel.salida.col] = SALIDA;
	else ;

	//Cargo Personaje
	if((personaje.posicion.fil == nivel.entrada.fil) && (personaje.posicion.col == nivel.entrada.col)) ;// veo si esta sobre la entrada
	else if ((personaje.posicion.fil == nivel.salida.fil) && (personaje.posicion.col == nivel.salida.col)
				&& (personaje.tiene_llave == true) ); // veo si esta sobre la salida

	else mapa[personaje.posicion.fil][personaje.posicion.col] = PERSONAJE;



}

/*
* Imprime el juego por pantalla, representado por una matriz de caracteres.
*/
void mostrar_mapa(char mapa[][DIMENSION_MAXIMA], int tope_mapa){
	printf("\n					");
	for(int i = 0; i < tope_mapa; i++){
		for(int j = 0; j < tope_mapa; j++){
			switch(mapa[i][j]){

				case PARED:
				printf(FGRIS " %c " CNORMAL,mapa[i][j]);
				break;

				case MONEDA:
				printf(FBLANCO AMARILLO " %c " CNORMAL, mapa[i][j]);
				break;

				case BALDOSA_TRANSPORTADORA:
				printf(FBLANCO TURQUESA " %c " CNORMAL, mapa[i][j]);
				break;

				case GUARDIA:
				printf(FBLANCO AZUL " %c " CNORMAL, mapa[i][j]);
				break;

				case BALDOSAS_PINCHE:
				printf(FBLANCO ROJO " %c " CNORMAL, mapa[i][j]);
				break;

				case SALIDA:
				printf(FAZUL BLANCO " %c " CNORMAL, mapa[i][j]);
				break;

				case ENTRADA:
				printf(FAZUL BLANCO " %c " CNORMAL, mapa[i][j]);
				break;

				case BOMBA:
				printf(FNEGRO BLANCO " %c " CNORMAL, mapa[i][j]);
				break;					

				case LLAVE:
				printf(FBLANCO VERDE " %c " CNORMAL, mapa[i][j]);
				break;

				case INTERRUPTOR:
				printf(FBLANCO AZUL " %c " CNORMAL, mapa[i][j]);
				break;

				case VACIO:
				printf(FBLANCO " %c " CNORMAL, mapa[i][j]);
				break;

				default:
				printf(FBLANCO NEGRO":¬%c" CNORMAL,mapa[i][j]);
			}
		}
		printf("\n					");
	}
	printf("\n");
}

/*
* Muestra por pantalla que tiene unaa chance mas el usuario
*/
void avisar_revivio(char tipo_personaje){
	system("clear");

	printf("\n");
	printf("\n");
	printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                       Safastes, revivis gracias a tu bonus                       ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
	printf("\n");
	printf("\n");

	detener_el_tiempo(UNIDAD_TIEMPO);
}

void bienvenida(){
	char aux;
	system("clear");

	printf("\n");
	printf("\n");
	printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                 ¡¡BIENVENIDO AL MEJOR JUEGO DEL UNIVERSO!!                       ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t"" by:Pedro Rabitti                                                                 ""\t \t""\n");
	printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
	printf("\n");
	printf("\n");

	detener_el_tiempo(UNIDAD_TIEMPO);
	detener_el_tiempo(UNIDAD_TIEMPO);

	system("clear");

	printf("\n");
	printf("\n");
	printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
	printf("\t \t""             INSTRUCCIONES:                                                       ""\t \t""\n");
	printf("\t \t""     El juego consiste en hacer que el personaje, representado por :¬),     ""\t \t""\n");
	printf("\t \t"" llege a la salida (represenetada por "FAZUL BLANCO" %c "CNORMAL "). El jugador parte de la entrada""\t \t""\n", SALIDA);
	printf("\t \t"" represenetada por "FAZUL BLANCO" %c "CNORMAL ". Para llegar que la salida sea visible el personaje""\t \t""\n", ENTRADA);
	printf("\t \t"" debera agarrar la llave, representada por "VERDE "%c"CNORMAL" y para que la llave sea visible,  ""\t\t""\n",LLAVE);
	printf("\t \t"" tendrá que agarrar el interruptor (si es que existe), representada por "AZUL "%c."CNORMAL"""\t \t""\n", INTERRUPTOR);
	printf("\t \t"" El jugador contara con %i movimientos. Debera evitar toparse con los guardias,  ""\t \t""\n",MOVIMIENTOS_INICIALES);
	printf("\t \t"" represntados por "AZUL "%c"CNORMAL "(en cuyo caso el el jugaor pierde la partida) \t \t""\n", GUARDIA);
	printf("\t \t"" y con las baldosas pinches, representadas por "ROJO "%c"CNORMAL ". ""\t \t""\n", BALDOSAS_PINCHE);
	printf("\t \t"" El jugador contara con la ayuda de las baldosas transportadoras, representadas por "TURQUESA "%c"CNORMAL "\t \t""\n", BALDOSA_TRANSPORTADORA);
	printf("\t \t"" , para moverse mas facilmente por el mapa y con las algo-coins, representadas por "AMARILLO"%c"CNORMAL "\t \t""\n", MONEDA);
	printf("\t \t"" , que al agarrarlas provera de un movimiento extra al jugador.                   ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""           -- Presione una letra + enter para continuar ---          ""\t \t""\n");
	printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
	printf("\n");
	printf("\n");
	scanf(" %c", &aux);

	system("clear");
    printf("\n");
	printf("\n");
	printf("\t \t" FBLANCO "                                                                         \n" CNORMAL);
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""      Acontinuación se eligira el personje. Los personajes tienen los siguientes  ""\t \t""\n");
	printf("\t \t""  Bonus:                                                                          ""\t \t""\n");
	printf("\t \t""  * Puro Hueso y Pollito: Puro hueso por no tener carne y Pollito por ser finito, ""\t \t""\n");
	printf("\t \t""   no serán afectados por las baldosas pinche.                                    ""\t \t""\n");
	printf("\t \t""  *Blue y Bellota: Blue por ser imaginario y Bellota por ser Superpoderosa obten- ""\t \t""\n");
	printf("\t \t"" drán una segunda oportunidad con 10 movimientos si es que mueren en alguno de los""\t \t""\n");
	printf("\t \t"" niveles.                                                                         ""\t \t""\n");
	printf("\t \t""  *Johnny Bravo y Coraje: Johnny por enamorarlos con sus encantos y Coraje por da-""\t \t""\n");
	printf("\t \t""  rles tanta ternura, no serán trapados por los guardias robot.                   ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""     Presione un letra y enter para empezar a jugar. Mucha suerte!!               ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t""                                                                                  ""\t \t""\n");
	printf("\t \t "FBLANCO  "                                                                        \n" CNORMAL);
	printf("\n");
	printf("\n");
	scanf(" %c", &aux);
	system("clear");
}