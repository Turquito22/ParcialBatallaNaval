#include "Ficheros.h"

/*Constructor 
Crea Todos los Ficheros . Le Asigno un ID
Y si Es el Primero Inicio los Ficheros
*/
Ficheros::Ficheros(int &id) {	
	this->IDS		= fstream (idPlayers);  // fstream IDS = IDS.open(idPlayers);
	this->Puntos    = fstream(fpuntos);
	id_jugador();
	this->fBarcosP1 = fstream (barcos1);
	this->fBarcosP2 = fstream (barcos2);
	this->fBarcosP3 = fstream (barcos3);
	this->fDisp11   = fstream (disparos11);	
	this->fDisp21   = fstream (disparos21);	
	this->fDisp31   = fstream (disparos31);	
	this->fDisp12   = fstream (disparos12);	
	this->fDisp22   = fstream (disparos22);	
	this->fDisp32   = fstream (disparos32);	
	id = ID;
	if(ID == 1){
		inicio_ficheros();	
	}
}
/*Destrcutor
Cierra Todos los Ficheros
*/
Ficheros::~Ficheros() {
	fstream jugador,puntos;
	jugador.open(idPlayers);
	puntos.open(fpuntos);
	int subI,subJ,pos=0;
	
	for(subI=0;subI<11;subI++){
		jugador.seekg(subI);
		jugador.write("0",1);
	}
	for(subI=0;subI<=3;subI++){
		for(subJ=0;subJ<=3;subJ++){
			puntos.seekg(pos);
			puntos.write("0",1);
			pos++;
			}
		pos++;
		}
	cierro_ficheros();
}

/*Pone Todos los Ficheros en Cero
*/
void Ficheros::inicio_ficheros(){
	int subI,subJ;	
	
	if(!fBarcosP1.is_open() || !fBarcosP2.is_open() || !fBarcosP3.is_open() || !fDisp11.is_open() || !fDisp21.is_open() || !fDisp31.is_open()){
		cout<<"ERROR al abrir Ficheros"<<endl;
	}else{
		
		for(subI=0;subI<=(9);subI++)	{
			//Lleno las Lineas de 0(CEROS)
			for(subJ=0;subJ<=(9);subJ++)	{		
				fBarcosP1<<0;fDisp11<<0;fDisp12<<0;
				fBarcosP2<<0;fDisp21<<0;fDisp22<<0;
				fBarcosP3<<0;fDisp31<<0;fDisp32<<0;
			}//Hago el Salto de LINEA.		
			fBarcosP1<<endl;fDisp11<<endl;fDisp12<<endl;
			fBarcosP2<<endl;fDisp21<<endl;fDisp22<<endl;
			fBarcosP3<<endl;fDisp31<<endl;fDisp32<<endl;
			
		}
		
		for(subI=0;subI<3;subI++){
			for(subJ=0;subJ<3;subJ++){
			Puntos<<0;	
			}
			Puntos<<endl;
		}
		cout<<"Ficheros Abiertos"<<endl;
	}
	
}
/*Cierra los Ficheros
*/
void Ficheros::cierro_ficheros(){
	this->fBarcosP1.close();
	this->fBarcosP2.close();
	this->fBarcosP3.close();
	this->fDisp11.close();
	this->fDisp21.close();
	this->fDisp31.close();	
	this->fDisp12.close();
	this->fDisp22.close();	
	this->fDisp32.close();
	this->Puntos.close();
	this->IDS.close();
}
/*Elijo el ID del Jugador
*/
void Ficheros::id_jugador(){
	int subI,pos=0;
	char cad[20];
	int ide;
	fstream jugador;
	jugador.open(idPlayers);
	for(subI=0;subI<=10;subI++){
		
		jugador.seekg(pos);
		jugador.read(cad,1);
		
		ide=(int)cad[0]-'0';
		
		if(cad[0] == '0'){
			cad[0]= (pos+1)+'0';
			jugador.seekp(pos);
			jugador.write(cad,1);
			ID = (pos+1);
			break;
		}	
		pos++;
	}		
}


/*Guardo los puntos obtenidos en el fichero
*/
void Ficheros::guardo_puntos(int pts){
	fstream fPuntos;
	fPuntos.open(fpuntos);
	if(!fPuntos.is_open()){
		cout<<"No se puede Abrir Fichero para Guardar Puntos"<<endl;
	}
	char cA[1];
	char cB[1];
	char cC[1];
	int subI;
	int a = (pts / 100), b = (pts % 100) / 10 , c = pts % 10;
	cA[0] = (char) (a+'0'); 
	cB[0] = (char) (b+'0'); 
	cC[0] = (char) (c+'0'); 
//	cout<<"GUARDO "<<cA[0]<<cB[0]<<cC[0]<<" DE PUNTOS AL ID"<<ID;
	switch(ID){
	case 1:

		fPuntos.seekg(0);
		fPuntos.write(cA,1);
		fPuntos.seekg(1);
		fPuntos.write(cB,1);
		fPuntos.seekg(2);
		fPuntos.write(cC,1);
	
		
		break;
	case 2:
		fPuntos.seekg(4);
		fPuntos.write(cA,1);
		fPuntos.seekg(5);
		fPuntos.write(cB,1);
		fPuntos.seekg(6);
		fPuntos.write(cC,1);
		break;
	case 3:
		fPuntos.seekg(8);
		fPuntos.write(cA,1);
		fPuntos.seekg(9);
		fPuntos.write(cB,1);
		fPuntos.seekg(10);
		fPuntos.write(cC,1);
		break;
	}
	
}

/*Muestro todos los puntos de los jugadores
*/
void Ficheros::leo_puntos(){
	fstream fPuntos;
	fPuntos.open(fpuntos);

int todos[9];
char cad[1];
int subI,subJ;
int pos=0,arreglo=0;
int pts1,pts2,pts3;
	for(subI=0;subI<3;subI++){
		for(subJ=0;subJ<3;subJ++){
			fPuntos.seekg(pos);
			fPuntos.read(cad,1);
			todos[arreglo] = (int) (cad[0]-'0');
			pos++;
			arreglo++;
		}
		pos++;
	}
	pts1 = (todos[0]*100) + (todos[1]*10) + (todos[2]*1);
	pts2 = (todos[3]*100) + (todos[4]*10) + (todos[5]*1);
	pts3 = (todos[6]*100) + (todos[7]*10) + (todos[8]*1);
	
	switch(ID){
	case 1 :
		cout<<"Sus puntos : "<<pts1<<endl;
		cout<<"Puntos Enemigo1 :"<<pts2<<endl;
		cout<<"Puntos Enemigo2 :"<<pts3<<endl;
		break;
	case 2 :
		cout<<"Sus puntos : "<<pts2<<endl;
		cout<<"Puntos Enemigo1 :"<<pts1<<endl;
		cout<<"Puntos Enemigo2 :"<<pts3<<endl;
		break;
	case 3 :
		cout<<"Sus puntos : "<<pts3<<endl;
		cout<<"Puntos Enemigo1 :"<<pts1<<endl;
		cout<<"Puntos Enemigo2 :"<<pts2<<endl;
		break;	
	}
		
}
