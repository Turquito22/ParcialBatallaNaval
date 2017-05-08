#ifndef JUGADOR_H
#define JUGADOR_H
#include "program1.h"
clase Jugador {
privado:
	logico CeldaDisponible(entero x,entero y);	
publico:
//Almacena los disparos 	
	entero disparos[10][10];
	//Valores:
	//0: No se disparo en ese casillero
	//1: Se disparo pero hay agua
	//2: Se disparo y golpeo un Barco,
//Almacena la flota	
	entero flota[10][10];
	//Valores:
	//0: Vacio
	//1: Portaviones
	//2: Acorazado
	//3: Crucero
	//4: Submarino
	//5: Destructor
	entero barcos[5];
	
	//Constructor
	Jugador() { esto->Inicializar(); }
	//Inicializa las variables
	procedimiento Inicializar();
	//Dibuja el tablero Flota y el de Disparos si ConDisparos ES verdadero
	procedimiento DibujarTablero(logico ConDisparos);
	procedimiento UbicarBarcos();
	procedimiento Disparar(entero x,entero y,Jugador *oponente);
	constante caracter deref NombreBarco(entero num);									//Devuelve el nombre de un barco
	entero Cantidad(entero num);													//Devuelve la cantidad de celdas de una barco
	entero Oponente(entero num);													//Devuelve el oponente
	logico SeleccionarCelda(entero deref x,entero deref y);									//Obtiene una celda del teclado siempre y cuando este bien escrita
	logico SeleccionarPosicion();													//Selecciona Horizontal(true) o Vertical(false)
	
	
};

#endif

