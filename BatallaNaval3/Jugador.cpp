#include "Jugador.h"
#define scrclr() system("clear");

procedimiento Jugador::Inicializar(){
	entero i,j;
	//Tableros iguales a cero
	variar(i,0,9,1)
		variar(j,0,9,1)
			disparos[i][j]=0;
			flota[i][j]=0;
		finVariar
	finVariar
	for(i=0;i<5;i++) barcos[i]=Cantidad(i);
}

procedimiento Jugador::DibujarTablero(logico ConDisparos){
	entero i;
	caracter j;
	mostrar << setiosflags(ios::left) << setw(33) << "Tu flota";
	si(ConDisparos)entonces
		mostrar << "\t";
		mostrar << "Tus Disparos";
	finSi
	resetiosflags(ios::left);
	mostrar << salto << salto;
	//Dibuja la primera línea de numeros separados con |
	mostrar << "  |";
	variar(i,1,10,1)
		si(i ES 10) mostrar << i << "|";
		siNo mostrar << i << " |";
	finVariar
	//Si hay que dibujar el otro tablero se hace lo mismo al lado
	si(ConDisparos)entonces
		mostrar << "\t";
		mostrar << "  |";
		variar(i,1,10,1)
			si(i ES 10) mostrar << i << "|";
			siNo mostrar << i << " |";
		finVariar
	finSi
	//Se dibuja linea de separación
	mostrar<< salto;
	for(i=1;i<=33;i++) mostrar << "=";
	//Si hay que dibujar el otro tablero se hace lo mismo al lado
	si(ConDisparos)entonces
		mostrar << "\t";
		for(i=1;i<=33;i++) mostrar << "=";
	finSi
	mostrar << salto;
	//Se dibujan las celdas del juego
	for(j='A';j<='J';j++){
		//Letra para identificar la fila
		mostrar << j << " |";
		variar(i,0,9,1)
			//Se verifica la celda actual para poner un valor
			segun(flota[((entero)j)-65][i])
				caso 0: mostrar << "  |"; sale;
				caso 1: mostrar << "PA|"; sale;
				caso 2: mostrar << "AC|"; sale;
				caso 3: mostrar << "CR|"; sale;
				caso 4: mostrar << "SB|"; sale;
				caso 5: mostrar << "DS|"; sale;
				caso 6: mostrar << "XX|"; sale;
			finSegun
		finVariar
		//Si hay que dibujar el otro tablero se hace lo mismo al lado
		si(ConDisparos)entonces
			mostrar << "\t";
			mostrar << j << " |";
			variar(i,0,9,1)
				segun(disparos[((entero)j)-65][i])
					caso 0: mostrar << "  |"; sale;
					caso 1: mostrar << "AG|"; sale;
					caso 2: mostrar << "TK|"; sale;
				finSegun
			finVariar
		finSi
		//Se dibuja linea de separación
		mostrar << salto;
		for(i=1;i<=33;i++) mostrar << "=";
		//Si hay que dibujar el otro tablero se hace lo mismo al lado
		si(ConDisparos)entonces
			mostrar << "\t";
			for(i=1;i<=33;i++) mostrar << "=";
		finSi
		mostrar << salto;
	}
}

procedimiento Jugador::UbicarBarcos(){
	logico terminado=FALSO;
	logico pos,disponible;
	entero actual=0;
	entero x,y,xaux,yaux,i;
	mientras(1)
		limpiarBuffer
		limpiar
		DibujarTablero(FALSO);
		si(terminado)entonces
			limpiarBuffer
			espera
			sale;
		finSi
		mostrar << "Indique la celda donde comienza el " << NombreBarco(actual) << " (" << Cantidad(actual) << " celdas): ";
		mientras(NO SeleccionarCelda(porRef x,porRef y))
			mostrar << "La celda señalada no existe, intente otra vez: ";
		finMientras
		mostrar << "Indique si el " << NombreBarco(actual) << " se ubica horizontalmente o verticalmente (h/v): ";
		pos=SeleccionarPosicion();
		
		//Verificamos si entra en el tablero
		
		si( (pos Y (x+Cantidad(actual)-1) menorIgual 9) O (NO pos Y (y+Cantidad(actual)-1) menorIgual 9) )entonces
			//Verificamos si son posiciones validas
			for(i=1,xaux=x,yaux=y,disponible=true;i<=Cantidad(actual)&&disponible;i++){
				si(NO CeldaDisponible(xaux,yaux) ) disponible=FALSO;
				si(pos) xaux++;
				siNo yaux++;
			finVariar
			//Si esta disponible colocamos las celdas correspondientes a cada barco
			si(disponible)entonces
				variar(i,1,Cantidad(actual),1)
					flota[y][x]=actual+1;
					si(pos) x++;
					siNo y++;
				finVariar
				actual++;
				si(actual mayorIgual 5) terminado=VERDADERO;
			finSi
			Sino
				mostrar << "El espacio seleccionado para el " << NombreBarco(actual) << " no esta disponible";
				Espera
			finSino
		finSi
		Sino
			mostrar << "El " << NombreBarco(actual) << " no entra en el tablero";
			Espera
		finSino
	finMientras
}

logico Jugador::CeldaDisponible(entero x,entero y){
		//Centro		//Arriba				//Derecha			   //Abajo				//Izquierda
	si( (flota[y][x]) O (y>0&&flota[y-1][x]) O (x<9&&flota[y][x+1]) O (y<9&&flota[y+1][x]) O (x>0&&flota[y][x-1])) regresa (FALSO);
	
	regresa(VERDADERO);
}

constante caracter deref Jugador::NombreBarco(entero num){
	segun(num)
		caso 0: regresa ("Portavion");
		caso 1: regresa ("Acorazado");
		caso 2: regresa ("Crucero");
		caso 3: regresa ("Submarino");
		caso 4: regresa ("Destructor");
	finSegun
}

entero Jugador::Cantidad(entero num)
{
	segun(num)
	caso 0: regresa(5);
	caso 1: regresa(4);
	caso 2:
	caso 3:
			regresa(3);
	caso 4: regresa(2);
	}
}

entero Jugador::Oponente(entero num){
	regresa(NO num? 1:0);
}

logico Jugador::SeleccionarCelda(entero deref x,entero deref y){
	caracter c;
	entero n;
	leer c; leer n;
	limpiarBuffer
	si(minusculas(c)) c=mayusculas(c);
	si(c menor 'A' O c mayor 'J' O n menor 1 O n mayor 10) regresa(FALSO);
	*x=n-1;
	*y=((entero)c)-65;
	regresa(VERDADERO);
}

logico Jugador::SeleccionarPosicion(){
	caracter c;
	repetir
		c=getchar();
		limpiarBuffer
	hasta((c NOES 'h') Y (c NOES 'H') Y (c NOES 'v') Y (c NOES 'V'));
	si((c ES 'h') O (c ES'H')) regresa(VERDADERO);
	regresa (FALSO);
}
