#ifndef JUGADOR_H
#define JUGADOR_H
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
#endif

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <iomanip> //para los resetiosflags y setiosflags
#define limpiar                system("clear");setlocale(LC_ALL, "spanish");
using namespace std;
class Jugador {
private:
protected:
public:
	fstream fBarcos,fDisp1,fDisp2,fEnem1,fEnem2;
	int ID;
	int pts;
	Jugador(int);
	~Jugador();
	
	
	/*Metodos*/
	const char* nombre_barco(int);
	const char* segun_id(int);
	int cantidad(int);
	int puntos(int);
	int coordenada_disparo(int,fstream &);
	bool seleccionar_celda(int*,int*);
	bool seleccionar_posicion();
	bool celda_disponible(int,int,fstream&);
	bool disparo_disponible(int,int,fstream&);
	bool barco_hundido(int,fstream&);
	bool ningun_barco(fstream&);
	void Ubicar_Barcos();
	void dibujar_tableros(bool,bool);
	void realizo_disparo();
	
};

#endif

