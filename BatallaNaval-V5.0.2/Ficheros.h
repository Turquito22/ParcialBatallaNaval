#ifndef FICHEROS_H
#define FICHEROS_H
#include <iostream>
#include <fstream>
#ifndef barcos 
#define barcos
#define idPlayers "/home/roman/Documentos/BatallaNaval/players.txt"
#define barcos1 "/home/roman/Documentos/BatallaNaval/BarcosPlayer1.txt"
#define barcos2 "/home/roman/Documentos/BatallaNaval/BarcosPlayer2.txt"
#define barcos3 "/home/roman/Documentos/BatallaNaval/BarcosPlayer3.txt"
#define disparos11 "/home/roman/Documentos/BatallaNaval/Disparos1Player1.txt"
#define disparos21 "/home/roman/Documentos/BatallaNaval/Disparos1Player2.txt"
#define disparos31 "/home/roman/Documentos/BatallaNaval/Disparos1Player3.txt"
#define disparos12 "/home/roman/Documentos/BatallaNaval/Disparos2Player1.txt"
#define disparos22 "/home/roman/Documentos/BatallaNaval/Disparos2Player2.txt"
#define disparos32 "/home/roman/Documentos/BatallaNaval/Disparos2Player3.txt"
#define fpuntos    "/home/roman/Documentos/BatallaNaval/puntos.txt"
#endif
using namespace std;

class Ficheros {
private:
protected:
public:
	fstream fBarcosP1,fBarcosP2,fBarcosP3;
	fstream fDisp11,fDisp12,fDisp21,fDisp22,fDisp31,fDisp32;
	fstream IDS,Puntos;	
	int ID;

	 Ficheros(int&);
	~Ficheros();
	
	void inicio_ficheros();
	void cierro_ficheros();
	void id_jugador();
	void guardo_puntos(int);
	void leo_puntos();
	int creo_id();
	

};

#endif

