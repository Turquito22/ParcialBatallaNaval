#include "Jugador.h"

Jugador::Jugador(int id) {
	ID = id;
	switch(id){
	case 1 : 
		this->fBarcos = fstream(barcos1); 
		this->fDisp1  = fstream(disparos11);
		this->fDisp2  = fstream(disparos12);
		this->fEnem1  = fstream(barcos2);
		this->fEnem2  = fstream(barcos3);
		break;
	case 2 : 
		this->fBarcos = fstream(barcos2);
		this->fDisp1  = fstream(disparos21);
		this->fDisp2  = fstream(disparos22);
		this->fEnem1  = fstream(barcos1);
		this->fEnem2  = fstream(barcos3);
		break;	
	case 3 : 
		this->fBarcos = fstream(barcos3);
		this->fDisp1  = fstream(disparos31);
		this->fDisp2  = fstream(disparos32);
		this->fEnem1  = fstream(barcos1);
		this->fEnem2  = fstream(barcos2);
		break;	
	}
}
Jugador::~Jugador() {	
}

/**Ubico Todos los Barcos en los Ficheros
* f: Recibe el Fichero en el que Debe Guardar los Barcos
*/
void Jugador::Ubicar_Barcos(){
	int barcoActual = 0;
	int x,y,subI,subX,subY,pos;
	bool fin = false;
	bool posicion,disponible;
	char cad[2];
	char barco;
	
	while(true){
		if(fin){
			
			break;
		}
		do{				/*Mientras las Coordenadas no sean Correctas*/
			
			cout<< "Indique Posicion Inicial de "<< nombre_barco(barcoActual)<< "  ["<<cantidad(barcoActual)<<"] Celdas :"<<endl;
			
		}while(!seleccionar_celda(&x,&y));
		
		cout<<"Indique si el : "<<nombre_barco(barcoActual)<< "Se ubica Horizontalmente o Verticalmente (h/v)"<<endl; 
		posicion = seleccionar_posicion();
		
		/*Verificamos que el Barco Entre en el Tablero*/
		if(  ( posicion && (x+cantidad(barcoActual)-1 <= 9 ) ) || ( !posicion && (y+cantidad(barcoActual)-1 <= 9) ) ){
			/*Verificamos que todas las posiciones sean validas*/	
			for(subI=1,subX=x,subY=y,disponible=true;subI<=cantidad(barcoActual)&&disponible;subI++){
				if(!celda_disponible(subX,subY,fBarcos)) {disponible=false;}
				if(posicion){
					subX++;
				}else{
					subY++;
				}					
			}
			/*Si todas las posiciones son Validas Colocamos los barcos*/
			if(disponible){
				pos = ((y*11)+x);	 //Convierte las coordendas X Y en la posicion en el fichero	
				
				cad[0] = (barcoActual+1)+'0';
				//			cout<<"Barco Actual : "<<cad[0]<<endl;
				for(subI=1;subI<=cantidad(barcoActual);subI++){
					//					cout<<"Guardo "<< cad[0]<<" en Posicion "<<pos<<salto;
					fBarcos.seekp(pos); //Posiciono el puntero del fichero para escribir en el
					fBarcos.write(cad,1);//Escribo el Barco en el fichero
					
					if(posicion){
						pos++;
					}else{
						pos=pos+11;
					}
				}
				barcoActual=barcoActual+1; //Variable usada para obtener nombre y tamaño
				limpiar
				
					dibujar_tableros(false,false);	
				cout<<"Barco Guardado con Exito..."<<endl;
				sleep(1);

				
				if(barcoActual >= 5){fin = true;}
			}else{
				cout<<"El espacio Seleccionado Para "<<nombre_barco(barcoActual)<<" no esta disponible."<<endl;
			}
		}else{
			cout<<"El "<<nombre_barco(barcoActual)<<" No entra en el Tablero"<<endl;
		}
		
	}	
}
/**Si esta Dentro del Tablero [A-J] Y [1-10]
*x , y = Coordenadas del Disparo.
*/
bool Jugador::seleccionar_celda(int *x,int *y){
	char c;
	int n;
	cout<<"Ingrese Letra : "; cin>>c; 
	cout<<"Ingrese Numero : "; cin>>n;
	fflush(stdin);
	if(islower(c)) c=toupper(c);
	if(c < 'A' || c > 'J' || n < 1 || n > 10){
		cout<<"La Celda Ingresada No existe. Intente Otra Vez"<<endl; 
		return false;
	}
	*x = n-1;
	*y = ((int)c)-65; //Letra al int A = 0 B = 1 C = 2...
	return true;
	
}
/**Si es Vertical o Horizontal*/
bool Jugador::seleccionar_posicion(){
	char c;
	do{
		cin>>c;	
		
		if((c != 'h') && (c != 'H') && (c != 'v') && (c != 'V')){
			cout<<"Posicion Invalida. Intente Otra vez :"<<endl;	
		}
	}while((c != 'h') && (c != 'H') && (c != 'v') && (c != 'V'));	
	if((c == 'h') || (c == 'H')) return true;
	return false;
}
/**Devuelve el Nombre del Barco Actual
*num=Numero del Barco Actual
*/
const char* Jugador::nombre_barco(int num){
	switch(num){
		case 0: return ("Portavion");
	case 1: return ("Acorazado");
	case 2: return ("Crucero");
	case 3: return ("Submarino");
	case 4: return ("Destructor");
	}
}

/**Devuelve la cantidad de Celdas que Ocupa el barco Actual
*num:Numero del Barco Actual
*/
int Jugador::cantidad(int num){
	switch(num){
		case 0: return(5);
	case 1: return(4);
	case 2:
		case 3:			
		return(3);
	case 4: return(2);
	}
}
/**Verificamos que no  hay ningun barco alrededor
*x,y : Coordenadas a Buscar
*f : Fichero Donde buscar si hay barcos alrededor. 
*/
bool Jugador::celda_disponible(int x,int y,fstream &f){
	
	char centro[2];
	char abajo[2];
	char arriba[2];
	char derecha[2];
	char izquierda[2];	
	int pos = ((y*11)+x);
	//cout<<"Posicion en Ficheros :"<<pos<<endl;
	
	if((pos < 11)){		
		//cout<<"Si esta en la Primer Linea"<<endl;
		f.seekg(pos);
		f.read(centro,1);	
		f.seekg((pos+11));
		f.read(abajo,1);
		
		if(pos!=0){
			//cout<<"izquierda va"<<endl;
			f.seekg(pos-1);
			f.read(izquierda,1);
		}
		if(pos<9){	
			//cout<<"Derecha va"<<endl;
			f.seekg(pos+1);
			f.read(derecha,1);
		}
	}
	if((pos >= 11) && (pos < 99)){
		//cout<<"Todas las lineas menos Primera y Ultima"<<endl;	
		f.seekg(pos);
		f.read(centro,1);	
		f.seekg((pos+11));
		f.read(abajo,1);
		f.seekg((pos-11));
		f.read(arriba,1);	
		if((pos%11 != 0)){
			
			//cout<<"izquierda va"<<endl;
			f.seekg(pos-1);
			f.read(izquierda,1);
		}
		if((pos != 20) || (pos != 31) || (pos != 42) || (pos != 53) || (pos != 64) || (pos != 75) || (pos != 86) || (pos != 97)){	
			
			//cout<<"derecha va"<<endl;
			f.seekg(pos+1);
			f.read(derecha,1);
		}
	}
	
	if((pos>=99)){
		//cout<<"Ultima Linea"<<endl;
		f.seekg(pos);
		f.read(centro,1);
		f.seekg((pos-11));
		f.read(arriba,1);
		if((pos%11 != 0)){
			//cout<<"Izquierda Va"<<endl;	
			f.seekg(pos-1);
			f.read(izquierda,1);
		}
		if(pos != 108){	
			//cout<<"derecha va"<<endl;	
			f.seekg(pos+1);
			f.read(derecha,1);
		}
	}
	bool d = false;
	if((pos != 9) && (pos != 20) && (pos != 31) && (pos != 42) && (pos != 53) && (pos != 64) && (pos != 75) && (pos != 86) && (pos != 97) && (pos != 108)){d = true;}
	
	if((centro[0] != '0') || ((pos>=11)&& arriba[0] !='0') || ((d) && derecha[0]!='0' ) || ((pos>0 && pos%11 !=0 ) && izquierda[0] !='0') ){
		//	cout<<"Ocupado"<<endl;
		return false;
	}else{
		//	cout<<"Libre"<<endl;
		return true;}
	
} 


/**Dibuja los Tableros del Juego
*disparos : Si es Verdadero Dibuja Ambos Tableros.
*xEnemigos si es verdad Dibuja los dos tableros de disparos
*/
void Jugador::dibujar_tableros(bool ConDisparos,bool xEnemigos){
fstream f1,f2;

if(!xEnemigos){
f1 = fstream(segun_id(1));
f2 = fstream(segun_id(2));
}else{
f1 = fstream(segun_id(2));
f2 = fstream(segun_id(3));
}
	int i,pos=0,subI,subJ;
	char j;
	char tBarcos[1],tDisparos[1];
	int flota[10][10],disparos[10][10];
	for(subI=0;subI<=(10-1);subI++){
		for(subJ=0;subJ<=(10-1);subJ++){
	f1.seekg(pos);
	f1.read(tBarcos,1);
	f2.seekg(pos);
	f2.read(tDisparos,1);
	flota[subI][subJ]=(int)tBarcos[0]-'0';
	disparos[subI][subJ]=(int)tDisparos[0]-'0';
	pos++;
//	cout<<tBarcos[0];
//	cout<<flota[subI][subJ];
	}
		pos++;	
	}
		
	if(!xEnemigos)	{cout << setiosflags(ios::left) << "Tu flota";}else{cout << setiosflags(ios::left) << "Tu Disparos";}
	if(ConDisparos){
		cout << "\t\t\t\t";
	cout << "Tus Disparos";
	}
		resetiosflags(ios::left);
	cout << endl << endl;
	//Dibuja la primera línea de numeros separados con |
	cout << "  |";
	for(i=1;i<=10;i++){
		if(i == 10)cout << i << "|";
		else cout << i << " |";
		
	}
		//Si hay que dibujar el otro tablero se hace lo mismo al lado
		if(ConDisparos){

		cout << "\t";
	    cout << "  |";
	
	for(i=1;i<=10;i++){
		if(i == 10) cout << i << "|";
		else	cout << i << " |";
	}
	
	}
		//Se dibuja linea de separación
		cout<< endl;
	for(i=1;i<=33;i++) cout << "=";
	//Si hay que dibujar el otro tablero se hace lo mismo al lado
	if(ConDisparos){
		cout << "\t";
	for(i=1;i<=33;i++) cout << "=";
	}
	
		cout << endl;
	//Se dibujan las celdas del juego
	for(j='A';j<='J';j++){
		//Letra para identificar la fila
		cout << j << " |";
	if(!xEnemigos){	
		for(i=0;i<=9;i++){
			//Se verifica la celda actual para poner un valo
			
			switch(flota[((int)j)-65][i]){
			case 0: cout << "  |"; break;
			case 1: cout << "PA|"; break;
			case 2: cout << "AC|"; break;
			case 3: cout << "CR|"; break;
			case 4: cout << "SB|"; break;
			case 5: cout << "DS|"; break;
			case 6: cout << "XX|"; break;
			}
		}
	}else 	
	if(xEnemigos){
		for(i=0;i<=9;i++){
			switch(flota[((int)j)-65][i]){
			case 0: cout << "  |"; break;
			case 1: cout << "AG|"; break;
			case 2: cout << "TK|"; break;
			}
		}
	}
				//Si hay que dibujar el otro tablero se hace lo mismo al lado
				if(ConDisparos){
				cout << "\t";
				cout << j << " |";
			for(i=0;i<=9;i++){
				switch(disparos[((int)j)-65][i]){
				case 0: cout << "  |"; break;
				case 1: cout << "AG|"; break;
				case 2: cout << "TK|"; break;
				}
					}
	}
					//Se dibuja linea de separación
					cout << endl;
				for(i=1;i<=33;i++) cout << "=";
				//Si hay que dibujar el otro tablero se hace lo mismo al lado
				if(ConDisparos){
					cout << "\t";
				for(i=1;i<=33;i++) cout << "=";
				}
					cout << endl;
	}	
	
}

/**
*FUncion que devuelve Segun el ID algun Directorio de Fichero
*Case 1 Mis barcos
*Case 2 Fichero Disparos 1 Case 3 Fichero disparos2
*Case 4 Ficheros barcosEnemigos1 case 5 Ficheros BarcosEnemigos2
*/

const char* Jugador::segun_id(int f){
	switch(f){
	case 1: 
		switch(ID){ /*Mis barcos*/
		case 1: return barcos1; break;
		case 2: return barcos2; break;
		case 3: return barcos3; break;
		}
		break;
	case 2:
		switch(ID){/*Disparos 1*/
		case 1: return disparos11; break;
		case 2: return disparos21; break;
		case 3: return disparos21; break;
		}		
		break;
	case 3: /*Disparos 2*/
		switch(ID){
		case 1: return disparos12; break;
		case 2: return disparos22; break;
		case 3: return disparos32; break;
		}		
		break;
	case 4: /*ENEMIGOS 1*/
		switch(ID){
		case 1: return barcos2; break;
		case 2: return barcos1; break;
		case 3: return barcos1; break;
		}		
		break;
	case 5:/*ENEMIGOS 2*/
		switch(ID){
		case 1: return barcos3; break;
		case 2: return barcos3; break;
		case 3: return barcos2; break;
		}		
		break;	
	}
}



/**
*Funcion Que reliza los disparos
*/
void Jugador::realizo_disparo(){
int x,y;
int disparo,enemigo;
int pos;
bool disponible;
bool hundido = false;
bool quedan = false;
char barco[1];
char disparos[1]; 
fstream f;
fstream BarcosEnemigos;
cout<<"Desea Disparar al Enemigo 1 o Enemigo 2 :"; cin>>enemigo;
fflush(stdin);
if(enemigo == 1) {f = fstream(segun_id(2)); BarcosEnemigos = fstream(segun_id(4));}
else {f = fstream(segun_id(3)); BarcosEnemigos = fstream(segun_id(5));}

do{
	cout<< "Indique Coordenadas del Disparo :"<<endl;
	disponible = seleccionar_celda(&x,&y);
	if(!disparo_disponible(x,y,f)){disponible=false;}else{disponible = true;}
	if(!disponible){cout<<"Ya ha realizado un disparo a esas Coordenadas"<<endl;}
	
	
}while(!disponible);

pos = ((y*11)+x);	
enemigo = coordenada_disparo(pos,BarcosEnemigos);

if(enemigo != 0 && enemigo != 6){
	barco[0] = '6';	
	BarcosEnemigos.seekg(pos);
	BarcosEnemigos.write(barco,1);
	disparos[0] = '2';
	f.seekg(pos);
	f.write(disparos,1);
	fflush(stdout); 
	hundido = barco_hundido(enemigo,BarcosEnemigos);

	
	if(hundido){
	cout<<"Has hundido el "<<nombre_barco(enemigo-1)<<" Enemigo"<<endl;	
	cout<<"Puntos Obtenidos"<<puntos(enemigo-1)<<"."<<endl;
	pts = pts + puntos(enemigo-1);
	cout<<"Puntos totales :"<<pts<<endl;
		quedan = ningun_barco(BarcosEnemigos);
		if(quedan){
			cout<<"Has hundido todos los Barcos del enemigo"<<endl;
		}
	
	}else{
		cout<<"Has tocado un Barco Enemigo"<<endl;	
	}
	
}else{
	if(enemigo == 0){
	disparos[0] = '1';
	f.seekg(pos);
	f.write(disparos,1);
	fflush(stdout);
	cout<<"No has dado con ningun Objetivo"<<endl;
	}
	if(enemigo == 6){
		cout<<"Otro Jugador ya disparo a esas coordenadas"<<endl;
		disparos[0] = '2';
		f.seekg(pos);
		f.write(disparos,1);
		fflush(stdout); 
	}
}

hundido = false;
}

/**
*Devuelve lo que haya en las coordenadas del disparo
*si hay algun barco o aga
*/
int Jugador::coordenada_disparo(int pos,fstream &f){
char disparos[1]; 	
	f.seekg(pos);
	f.read(disparos,1);
	
			
	 return ((int)(disparos[0]-'0'));
	
}

/**
*/
bool Jugador::disparo_disponible(int x,int y,fstream &f){
	int pos = ((y*11)+x);
	char disparos[1];	
	f.seekg(pos);
	f.read(disparos,1);
	
	if(disparos[0] != '0') return false;
	else return true;
} 

bool Jugador::barco_hundido(int enemigo,fstream &f){	
	int subI,subJ;
	char barco[1];
	char objetivo[1];
	objetivo[0] =(char)(enemigo+'0');
	int lee = 0;
//	cout<<"EL BARCO a BUSCAR : "<<objetivo<<endl;
	for(subI=0;subI<10;subI++){
		for(subJ=0;subJ<10;subJ++){
			f.seekg(lee);
			f.read(barco,1);
			lee++;
		if(barco[0] == objetivo[0]) {

			return false;
		}
		
		}
		lee++;
	}

	return true;
}


int Jugador::puntos(int num){
	switch(num){
	case 0: return(40);
	case 1: return(20);
	case 2:
	case 3:			
		return(15);
	case 4: return(10);
	}
}
bool Jugador::ningun_barco(fstream &f){
	int subI,subJ;
	char barco[1];
	char objetivo[5];
	objetivo[0] =(char)(1+'0');
	objetivo[1] =(char)(2+'0');
	objetivo[2] =(char)(3+'0');
	objetivo[3] =(char)(4+'0');
	objetivo[4] =(char)(5+'0');
	int lee = 0;
	
	for(subI=0;subI<10;subI++){
		for(subJ=0;subJ<10;subJ++){
			f.seekg(lee);
			f.read(barco,1);
			lee++;
			if( (barco[0] == objetivo[0]) || (barco[0] == objetivo[1]) 
			   || (barco[0] == objetivo[2]) || (barco[0] == objetivo[3]) || (barco[0] == objetivo[4])) {
				
				return false;
			}
			
		}
		lee++;
	}
	
	return true;
	
}
