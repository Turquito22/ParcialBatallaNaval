#include<iostream>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include"Ficheros.h"
#include"Jugador.h"
#include"Semaforo.h"
using namespace std;

int id = 0;

void mostrar_reglas();

int main (int argc, char *argv[]) {
	

int nPlayers = 1;//Utilizada por el Host (id = 1)
int inicio; //Utilizada para definir si empieza o no la partida
int	subI,turnosMax=5,turnoActual,continua;
int nPartidas = 1;
Ficheros f(id); //Ficheros f = new Fichero(id);
Jugador j(id);
Semaforo sem;

bool inicioPartida = false;
bool partidaTermina = false;
bool juegoTermina = false;

sem.inicio_semaforo(id-1);

mostrar_reglas();

sleep(3);

while(!juegoTermina){
if(id==1){
	
	if(nPartidas>1){
		f.inicio_ficheros();
	}
	
	while(!inicioPartida){
		
		cout<<"Numero de Jugadores En SERVIDOR :"<<nPlayers<<endl; 
		cout<<"Esperando otros Jugadores..."<<endl;	
		sem.espero_semaforo(nPlayers);	
		nPlayers ++;
		cout<<"Se a conectado un Jugador  N° de Jugadores: "<<nPlayers<<endl;	
		cout<<"Desea Esperar Otro ? 1.Si    2.NO "<<endl;cin>>inicio;
		if(inicio == 2){inicioPartida = true;}
	}

	for(subI=0;subI<(nPlayers-1);subI++){
		  sem.levanto_semaforo(id-1);
	}

}else if(id>1){

	sem.levanto_semaforo(id-1);
	cout<<"Esperando a que el host Inicie la Partida.."<<endl;	
	sem.espero_semaforo(0);	
	cout<<"Empieza la Partida"<<endl;
	
}

while(!partidaTermina){
	

if(id ==1){
	cout<<"Su Turno de Ubicar los Barcos"<<endl;
	j.dibujar_tableros(false,false);
	j.Ubicar_Barcos();
	sem.levanto_semaforo(id-1);
}else if(id>1){
	cout<<"Espero Turno"<<endl;
	sem.espero_semaforo(id-2);
	cout<<"Su Turno de Ubicar los Barcos"<<endl;
	j.dibujar_tableros(false,false);
	j.Ubicar_Barcos();
	sem.levanto_semaforo(id-1);
}

while(turnosMax>=turnoActual){
	
	if(id == 1){
		
	cout<<"Esperando Turno para Disparar..."<<endl;
	sem.espero_semaforo(2); //
	
	cout<<"Turno Actual : "<<turnoActual<<endl;
	sleep(1);
	j.realizo_disparo();
	j.dibujar_tableros(false,false); //Tablero Flota
	j.dibujar_tableros(true,true); //Tablero Disparos 1 Disparos 2
	cout<<"Disparo Realizado con exito"<<endl;
	if(turnoActual < turnosMax) sem.levanto_semaforo(id-1);
	}else if(id>1){
	cout<<"Esperando Turno para disparar..."<<endl;
		sem.espero_semaforo(id-2);	
		cout<<"Turno Actual :"<<turnoActual<<endl;
		sleep(1);
		j.realizo_disparo();
		j.dibujar_tableros(false,false);
		j.dibujar_tableros(true,true);
		cout<<"Disparo Realizado con exito"<<endl;
	if(turnoActual < turnosMax) sem.levanto_semaforo(id-1);	
	}
	turnoActual=turnoActual+3;
}
f.guardo_puntos(j.pts);
cout<<"Partida Terminada."<<endl;
f.leo_puntos();


partidaTermina=true;
}

cout<<"Desea Seguir Jugando ? 1Si. 2No.";cin>>continua;cout<<endl;
if(continua == 1){
	if(id == 1){
		nPartidas++;
	}else if(id>0){
		
	}
}else if(continua == 2){
	cout<<"Ha terminado el Juego"<<endl;
	juegoTermina=true;
}

}
limpiar;



	return 0;
}


void mostrar_reglas(){
	
	cout<<endl<<endl;
	cout<<"***********************************************************************"<<endl;
	cout<<"*****BATALLA NAVAL*****"<<endl<<endl;
	cout<<"Su ID en el Juego : "<<id<<endl<<endl;
	cout<<"***Reglas***"<<endl;
	cout<<"Tablero de 10x10 de [A-J] y [1-10]"<<endl;
	cout<<"Minimo de Jugadores para Empezar partida : 2"<<endl;
	cout<<"La partida consta de 25 Turnos"<<endl;
	cout<<"Cada Jugador Posee 5 Barcos con las Siguientes Caracteristicas"<<endl;
	cout<<"PortaAviones [5] Celdas"<<" Puntos Por Hundir 40"<<endl; 
	cout<<"Acorazados   [4] Celdas"<<" Puntos por Hundir 20"<<endl;
	cout<<"Cruzero      [3] Celdas"<<" Puntos por Hundir 15"<<endl;
	cout<<"Submarino    [3] Celdas"<<" Puntos por Hundir 15"<<endl;
	cout<<"Destructor   [2] Celdas"<<" Puntos por Hundir 10"<<endl;
	cout<<"Gana el Primero en Destruir Todos los Barcos de los demas"<<endl;
	cout<<"O El que obtenga la mayor cantidad de Puntos."<<endl;
	cout<<"Con un Disparo por Turno"<<endl;
	cout<<"Cada Disparo Puede Caer en : "<<endl;
	cout<<"AGUA : Si no hay ningun Barco Enemigo en las coordenadas de Disparo"<<endl;
	cout<<"Tocado : Si el disparo da a un barco Enemigo"<<endl;
	cout<<"Hundido : Si el el disparo da con un Barco y lo Hunde"<<endl;
	cout<<"***********************************************************************"<<endl;
	cout<<"Continuar..."<<endl;
	
}	
