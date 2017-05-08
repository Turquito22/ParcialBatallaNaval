
#include "program1.h"
#include "Jugador.h"
//SEGUN S.O
#define FLOTA_TOTAL 17




principal
	Jugador jugadores[2];
	logico done=FALSO;
	logico gameend,tocado,perdio,valido;
	entero i,jugadoractual,x,y,donei;
	
	mientras(!done)
		jugadoractual=0;
		gameend=FALSO;
		variar(i,0,1,1)
			jugadores[i].Inicializar();
			mostrar << "Turno del jugador " << i+1 << " de colocar su flota";
			espera
			jugadores[i].UbicarBarcos();
			limpiar
		finVariar
			
		mientras(!gameend)
			valido=FALSO;
			limpiar
			mostrar << "Turno del jugador " << jugadoractual+1 << " de disparar";
			espera
			limpiarBuffer
			mientras(!valido)
				tocado=FALSO;
				perdio=VERDADERO;
				limpiar
				mostrar << "Turno del jugador " << jugadoractual+1 << salto<< salto;
				jugadores[jugadoractual].DibujarTablero(true);
				mostrar << salto;
				mostrar << "Indique a que celda disparar: ";
				si(!jugadores[jugadoractual].SeleccionarCelda(&x,&y)) mostrar << "La celda indicada no es valida";
				Sino
					si(jugadores[jugadoractual].disparos[y][x])entonces
						mostrar << "Ya disparaste a esa celda";
					finSi
					Sino
						si(jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].flota[y][x])entonces
							tocado=VERDADERO;
							jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].barcos[(jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].flota[y][x])-1]--;
							jugadores[jugadoractual].disparos[y][x]=2;
							
							si(!jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].barcos[(jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].flota[y][x])-1])entonces
								mostrar << "Hundiste el " << jugadores[jugadoractual].NombreBarco(jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].flota[y][x]-1) << " enemigo";
								espera
							finSi
							Sino
								jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].flota[y][x]=6;
								mostrar << "Tocado";
								espera
							finSino
							jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].flota[y][x]=0;
						finSi
						Sino
							jugadores[jugadoractual].disparos[y][x]=1;
							mostrar << "Agua";
							espera
						finSino
						valido=VERDADERO;
					finSino
				finSino
				variar(i,0,4,1)
					si(jugadores[jugadores[jugadoractual].Oponente(jugadoractual)].barcos[i]>0)entonces
						perdio=FALSO;
						sale;
					finSi
				finVariar
				si(perdio)entonces
					limpiar
					mostrar<<salto << "El Jugador " << jugadoractual+1 << " ha ganado la batalla";
					gameend=VERDADERO;
					limpiarBuffer
					espera
						
					leerM(donei,"Desea Seguir Jugando? 1-Si 2-NO   :");
					si(donei ES 2)entonces
						
					done = VERDADERO;	
					finSi	
					sale;
				finSi //Finsi(Perdio) 
				limpiarBuffer
				espera
			finMientras	//Fin minetras !valido
			jugadoractual=jugadores[jugadoractual].Oponente(jugadoractual);
		finMientras //Fin mientras !gameend
	finMientras		//Fin mientras !done
	regresa (0);
finPrincipal
