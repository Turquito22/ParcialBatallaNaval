#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

// Esta union hay que definirla o no según el valor de los defines aqui
// indicados.
//        
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
// La union ya está definida en sys/sem.h
#else
// Tenemos que definir la union
union semun 
{ 
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};
#endif
class Semaforo {
private:
	key_t Clave;
	int Id_Semaforo;
	struct sembuf Operacion;
	struct sembuf Operacion1;
	union semun arg;
	int i=0;
	sem_t *semaforo;
	char *nombre;	
	
protected:
public:
	Semaforo();
	~Semaforo();
	void creo_semaforo();
	void inicio_semaforo(int);
	void espero_semaforo(int);
	void levanto_semaforo(int);

};

#endif
