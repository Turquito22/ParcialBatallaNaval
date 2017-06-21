#include "Semaforo.h"


Semaforo::Semaforo() {
	
	Clave = ftok ("/bin/ls", 33);
	if (Clave == (key_t)-1)
	{
		cout << "No puedo conseguir clave de semáforo" << endl;
		exit(0);
	}	
	
	Id_Semaforo = semget (Clave, 3, 0600 | IPC_CREAT);
	if (Id_Semaforo == -1)
	{
		cout << "No puedo crear semáforo"<<endl;
		exit (0);
	}
}

void Semaforo::inicio_semaforo(int indice){
	//	Se inicializa el semáforo con un valor conocido. Si lo ponemos a 0,
	//	es semáforo estará "rojo". Si lo ponemos a 1, estará "verde".
	//	El (id-1)de la función semctl es el índice del semáforo que queremos
	//	inicializar dentro del array de 3 que hemos pedido.
	arg.val = 0;
	semctl (Id_Semaforo,indice, SETVAL, 0);	
}

void Semaforo::espero_semaforo(int indice){
	//	Para "pasar" por el semáforo parándonos si está "rojo", debemos rellenar
	//	esta estructura.
	//	sem_num es el indice del semáforo en el array por el que queremos "pasar"
	//	sem_op es -1 para hacer que el proceso espere al semáforo.
	//	sem_flg son flags de operación. De momento nos vale un 0.	
	Operacion.sem_num =indice;
	Operacion.sem_op = -1;
	Operacion.sem_flg = 0;
//	cout<<"Espero Semaforo"<<endl;
	semop (Id_Semaforo, &Operacion, 1) ;
//	cout<<"Recibo Semaforo"<<endl;		
	
}


//
//	Se levanta el semáforo. Para ello se prepara una estructura en la que
//	sem_num indica el indice del semaforo que queremos levantar en el array
//	de semaforos obtenido.
//	El 1 indica que se levanta el semaforo 
//	El sem_flg son banderas para operaciones raras. Con un 0 vale.
void Semaforo::levanto_semaforo(int indice){
	
	
	Operacion.sem_num = (indice);
	Operacion.sem_op = 1;
	Operacion.sem_flg = 0;
	//cout << "Levanto Semáforo" << endl;
	//
	// Se realiza la operación de levantar el semáforo. Se pasa un array
	// de Operacion y el número de elementos en el array de Operacion. En
	// nuestro caso solo 1.
	//
	semop (Id_Semaforo, &Operacion, 1);
	sleep (1);
	
}



Semaforo::~Semaforo() {
	
}

