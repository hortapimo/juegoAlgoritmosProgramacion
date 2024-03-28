#include <stdio.h>
#include <stdlib.h>
// Constantes del programa
#define CORAJE 'C'
#define BLUE 'B'
#define BELLOTA 'S'
#define PURO_HUESO 'H'
#define POLLITO 'P'
#define JHONNY_BRAVO 'J'

const char VERDADERO = 0;
const char FALSO = 1;

const char SALADO = 'S';
const char DULCE = 'D';
const char AMARGO = 'A';

const char AMARILLO = 'Y';
const char AZUL = 'A';
const char ROSA = 'R';
const char NEGRO = 'N';
const char BLANCO = 'B';
const char VERDE = 'V';



// Firma de las funciones

int pedir_nacimiento(); //Le pregunta al usuario la fecha de nacimiento de su personaje y lo devuelve.
/*
pre: --
post: el año que devulve debe ser un numero entero entre 1988 y 2008
*/

char pedir_gusto(); //Le pregunta al usuario el gusto preferido de su personaje y lo devuelve.
/*
pre: --
post: Deb devolver 'D' o 'S' o 'A', correspondiente a dulce, salado y amargo.
*/

int pedir_talla(); //Le pregunta al usuario la talla de su personaje y la devuelve.
/*
pre: --
post: el entero que devulve debe esta entre 33 y 47 o 0 sino usa zapatos
*/

char pedir_color(); //Le pregunta al usuario el color preferido y lo devuelve.
/*
pre: --
post: Debe devolver los colores Azul ('A'), Amarillo ('Y'), Verde ('V'), Negro ('N'), 
Blanco ('B'), Rosa ('R').
*/

int validar_color(char color); // Determina si el valor de color ingresado es valido
/*
pre: --
post: Solo debe devolver FALSO (1) o VERDADERO (1)
*/

int pedir_altura(); //Le pregunta al usuario la altura del personaje y la devuelve.
/*
pre: --
post: Debe ser un entero entre 10 y 250.
*/

char determinar_personaje(int anio,int talla,int altura,char gusto,char color,int* puntaje); // Analisa las respuestas del usario y devuelve el personaje elejio
/*
pre: Deben cumplir las postcondiciones ya mecionadas, de las funciones que devuelven los valores.
post: Debe devolver, PURO_HUESO -> 'P', CORAJE -> 'C', POLLITO -> 'L', JHONNY_BRAVO -> 'J',
 BELLOTA -> 'V', BLUE -> 'B'.
*/

int calcular_puntaje(int anio,int talla,int altura,char gusto,char color);// Calcula el puntaje correspondiente segun las respuesta del usuario y lo devuelve
/*
pre: Deben cumplir las postcondiciones ya mecionadas, de las funciones que devuelven los valores. 
post: --
*/

char comparar_alturas(int puntaje, int altura); //compara las alturas de los personajes con el puntaje y devuelve el personaje mas cercano
/*
pre: --
post:  Debe devolver, PURO_HUESO -> 'P', CORAJE -> 'C', POLLITO -> 'L', JHONNY_BRAVO -> 'J',
 BELLOTA -> 'V', BLUE -> 'B', segun la comparaciòn que realizo.
*/

void mostrar_resultado(char personaje, int puntaje); //muestra por pantallas el personaje correspondiente segun las respuestas del usuario.
/*
pre: Debe cumplir con las postcondiciones de la funciòn que genera a personaje.
post: --
*/

void detectar_personaje(char* personaje_detectado){

	int anio;
	int talla;
	int altura;
	char gusto;
	char color;

	int puntaje = 0;

	printf("\n \t\t*************Bienvenido*************\n");
	
	anio = pedir_nacimiento();
	gusto = pedir_gusto();
	talla = pedir_talla();
	color = pedir_color();
	altura = pedir_altura();
	
	*personaje_detectado = determinar_personaje(anio, talla, altura, gusto, color, &puntaje);
	
	mostrar_resultado(*personaje_detectado, puntaje);


}



char determinar_personaje(int anio,int talla,int altura,char gusto,char color,int* puntaje){
	
	char personaje;

	*puntaje = calcular_puntaje(anio, talla, altura, gusto, color);

	personaje = comparar_alturas(*puntaje,altura);

	return personaje;
}

char comparar_alturas(int puntaje, int altura){

	char personaje;

	int diferencia_aux1;
	int diferencia_aux2;

	int altura_jhonny = 180;
	int altura_bellota = 120;
	int altura_pollito = 50;
	int altura_blue = 140;
	int altura_puro_hueso = 200;
	int altura_coraje =30;

	if (puntaje <= 240 && puntaje >= 161){
		diferencia_aux1 = abs(altura - altura_blue);
		diferencia_aux2 = abs(altura - altura_bellota);
		if (diferencia_aux1 > diferencia_aux2) personaje = BELLOTA;
		else personaje =BLUE;
	}

	else if (puntaje <= 160 && puntaje >= 81){
		diferencia_aux1 = abs(altura - altura_puro_hueso);
		diferencia_aux2 = abs(altura - altura_pollito);

		if (diferencia_aux1 > diferencia_aux2) personaje = POLLITO;
		else personaje = PURO_HUESO;
	}
	else {
		diferencia_aux1 = abs(altura - altura_jhonny);
		diferencia_aux2 = abs(altura - altura_coraje);

		if (diferencia_aux1 > diferencia_aux2) personaje = CORAJE;
		else personaje = JHONNY_BRAVO;
	}

	return personaje;
}
int calcular_puntaje(int anio,int talla,int altura,char gusto,char color){
	
	int puntaje = 0;

	// puntaje año
	puntaje += (anio % 20) + 1 ;
	
	//puntaje sabor
	if (gusto == SALADO) puntaje += 5;
	else if (gusto == DULCE) puntaje += 15;
	else puntaje += 20;
	
	 //puntaje color
	 if (color == AMARILLO || color == ROSA) puntaje += 5;
	 else if (color == NEGRO || color == BLANCO) puntaje += 15;
	 else puntaje += 20;
	 
	 //puntaje talla 
	 if (talla >= 33 && talla <= 37) puntaje *= 2;
	 else if (talla >= 38 && talla <= 42) puntaje *= 3;
	 else if (talla >= 43 && talla <= 47) puntaje *= 4;
	 else ;

	 return puntaje;
}

int pedir_nacimiento(){
	int precondicion = FALSO;
	int anio;

	while (precondicion == FALSO){
			printf("\t\t¿En que año nacio su personaje?\n");
			printf("\t\t(el año debe estar entre 1988 y 2008)\n");
			scanf("%i",&anio);
			if (anio >= 1988 && anio <= 2008) precondicion = VERDADERO;
			else printf("\n\t\tEl año no cumple con las condiciones pedidas, intente de nuevo \n\n");		 
		}
	return anio; 
}

int pedir_talla(){
	int precondicion = FALSO;
	int talla;

	while (precondicion == FALSO){
			printf("\t\t¿Cual es la talla de zapato de tu personaje?\n");
			printf("\t\t(La talla debe estar entre 33 y 47, sino usa zapatos ingresar 0.)\n");
			scanf("%i",&talla);
			if ((talla >= 33 && talla <= 47) || talla ==0) precondicion = VERDADERO;
			else printf("\n\t\tLa talla no cumple con las condiciones pedidas, intente de nuevo \n\n");		 
		}
	return talla; 
}

int pedir_altura(){
	int precondicion = FALSO;
	int altura;
	int altura_maxima = 250;
	int altura_minima = 10;

	while (precondicion == FALSO){
			printf("\t\t¿Cual es la altura de tu personaje?\n");
			printf("\t\t(La talla debe estar entre %i y %i cm)\n", altura_minima, altura_maxima);
			scanf("%i",&altura);
			if ((altura >= altura_minima && altura <= altura_maxima) || altura ==0) precondicion = VERDADERO;
			else printf("\n\t\tLa altura no cumple con las condiciones pedidas, intente de nuevo \n\n");		 
		}
	return altura; 
}

char pedir_gusto(){
	int precondicion = FALSO;
	char gusto;

	while (precondicion == FALSO){
			printf("\t\t¿Que sabor prefiere tu personaje?\n");
			printf("\t\t(Selccionar entre dulce -> D, salado -> S, amargo -> A)\n");
			scanf(" %c",&gusto);
			if ((gusto == DULCE || gusto == SALADO) || gusto == AMARGO) precondicion = VERDADERO;
			else printf("\n\t\tEl gusto no cumple con las condiciones pedidas, intente de nuevo \n\n");		 
		}
	return gusto; 
}

char pedir_color(){
	int precondicion = FALSO;
	char color;

	while (precondicion == FALSO){
			printf("\t\t¿Que color prefiere tu personaje?\n");
			printf("\t\t(Selccionar entre azul -> A, amarillo -> Y, verde -> V, negro -> N, blanco -> B, rosa -> R)\n");
			scanf(" %c",&color);

			if (validar_color(color)==VERDADERO) precondicion = VERDADERO;
			else printf("\n\t\tEl color no cumple con las condiciones pedidas, intente de nuevo \n\n");
				 
		}
	return color; 
}

int validar_color(char color){
	if ((color == AZUL || color == AMARILLO) || color == VERDE || color == NEGRO || color == BLANCO || color == ROSA) return VERDADERO;
			else return FALSO;

}

void mostrar_resultado(char personaje, int puntaje){
	switch(personaje){
		case JHONNY_BRAVO:
		printf("\t\tCon un puntaje de %i, el personaje que eljiste es - Johnny Bravo -. \n", puntaje);
		break;

		case BELLOTA:
		printf("\t\tCon un puntaje de %i, el personaje que eljiste es - Bellota -. \n", puntaje);
		break;

		case BLUE:
		printf("\t\tCon un puntaje de %i, el personaje que eljiste es - Blue -. \n", puntaje);
		break;

		case PURO_HUESO:
		printf("\t\tCon un puntaje de %i, el personaje que eljiste es - Puro Hueso -. \n", puntaje);
		break;

		case POLLITO:
		printf("\t\tCon un puntaje de %i, el personaje que eljiste es - Pollito -. \n", puntaje);
		break;

		case CORAJE:
		printf("\t\tCon un puntaje de %i, el personaje que eljiste es - Coraje -. \n", puntaje);
		break;
	}
}
