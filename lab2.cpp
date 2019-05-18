#include "lab2.h"
#include <iostream>
#include <cstring> // need this for strerror
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>

#define SLEEP 30
#define NUMT 10

pthread_t tid[NUMT];

pthread_mutex_t lock;  // critical section lock

sem_t *semACB,*semDBC,*semEC,*semEC1,*semFHI,*semFHI1,*semGHI,*semKI,*semKI1;




unsigned int lab2_task_number() 

{

    return (44 + 5) % 20; //лень считать было

}

void *thread_a(void *n)

{

    for (int i = 0; i < 3; ++i)

    {	

	pthread_mutex_lock(&lock);

	std::cout << "a" <<std::flush;

	pthread_mutex_unlock(&lock);

	sleep_ms(SLEEP);

    }

    sem_post(semDBC);

    return n;

}

void *thread_b(void *n)

{

    sem_wait(semACB);

    for (int i = 0; i < 6; ++i)

    {	

	pthread_mutex_lock(&lock);

	std::cout << "b" <<std::flush;

	pthread_mutex_unlock(&lock);

	sleep_ms(SLEEP);

    }

    sem_post(semEC);

    return n;

}

void *thread_c(void *n)

{

	sem_wait(semACB);

	for (int i = 0; i < 9; ++i)

	{

		pthread_mutex_lock(&lock);

		std::cout << "c" << std::flush;

		pthread_mutex_unlock(&lock);

		sleep_ms(SLEEP);

	}

	sem_post(semFHI);
	sem_post(semFHI);
	sem_post(semFHI);
	return n;

}
void *thread_d(void * n)

{

	sem_wait(semDBC);

	for (int i = 0; i < 3; ++i)

	{

		pthread_mutex_lock(&lock);

		std::cout << "d" << std::flush;

		pthread_mutex_unlock(&lock);

		sleep_ms(SLEEP);

	}

	sem_post(semEC1);

	return n;

}
void *thread_e(void * n)

{

	sem_wait(semEC);
	sem_wait(semEC1);
	for (int i = 0; i < 3; ++i)

	{

		pthread_mutex_lock(&lock);

		std::cout << "e" << std::flush;

		pthread_mutex_unlock(&lock);

		sleep_ms(SLEEP);

	}

	sem_post(semFHI1);

	sem_post(semFHI1);

	sem_post(semFHI1);

	return n;

}

void *thread_f(void *n)

{

    sem_wait(semFHI);

    sem_wait(semFHI1);


    for (int i = 0; i < 3; ++i)

    {	

	pthread_mutex_lock(&lock);

	std::cout << "f" <<std::flush;

	pthread_mutex_unlock(&lock);

	sleep_ms(SLEEP);

    }

    sem_post(semGHI);

    return n;

}



void *thread_g(void *n)

{

    sem_wait(semGHI);

    for (int i = 0; i < 3; ++i)

    {	

	pthread_mutex_lock(&lock);

	std::cout << "g" <<std::flush;

	pthread_mutex_unlock(&lock);

	sleep_ms(SLEEP);

    }

    sem_post(semKI1);

    return n;

}




void *thread_i(void *n)

{

    sem_wait(semFHI);

    sem_wait(semFHI1);


    for (int i = 0; i < 9; ++i)

    {	

	pthread_mutex_lock(&lock);

	std::cout << "i" <<std::flush;

	pthread_mutex_unlock(&lock);

	sleep_ms(SLEEP);

    }

    

    return n;

}




void *thread_h(void *n)

{

    sem_wait(semFHI);

    sem_wait(semFHI1);

    for (int i = 0; i < 6; ++i)

    {	

	pthread_mutex_lock(&lock);

	std::cout << "h" <<std::flush;

	pthread_mutex_unlock(&lock);

	sleep_ms(SLEEP);

    }

    sem_post(semKI);

    return n;

}

 void *thread_k(void *n)

 {

    sem_wait(semKI);

    sem_wait(semKI1);

    for (int i = 0; i < 3; ++i)

    {	

	pthread_mutex_lock(&lock);

	std::cout << "k" <<std::flush;

	pthread_mutex_unlock(&lock);

	sleep_ms(SLEEP);

    }

    return n;

}

int lab2_init()

{

    int err;

    // инициализация мьютекса

    if (pthread_mutex_init(&lock, NULL) != 0) 

    {

	std::cerr << "Mutex init failed" << std::endl;

	return 1;

    }

    

    if ( (semACB = sem_open("/my_semaphoreACB", O_CREAT, 0777, 2)) == SEM_FAILED ) 

    {

    	std::cerr << "ACB sem init failed" << std::endl;

    	return 1;

	}




	if ( (semDBC = sem_open("/my_semaphoreDBC", O_CREAT, 0777, 0)) == SEM_FAILED ) 

    {

	std::cerr << "dbc sem init failed" << std::endl;

	return 1;

    }

    

    

	if ( (semEC = sem_open("/my_semaphoreEC", O_CREAT, 0777, 0)) == SEM_FAILED ) 

    {

	std::cerr << "ec sem init failed" << std::endl;

	return 1;

    }

if ( (semEC1 = sem_open("/my_semaphoreEC1", O_CREAT, 0777, 0)) == SEM_FAILED ) 

    {

	std::cerr << "ec 1 init failed" << std::endl;

	return 1;

    }
 if ( (semFHI = sem_open("/my_semaphoreFHI", O_CREAT, 0777, 0)) == SEM_FAILED ) 

    {

	std::cerr << "sem fhi init failed" << std::endl;

	return 1;

    }

if ( (semFHI1 = sem_open("/my_semaphoreFHI1", O_CREAT, 0777, 0)) == SEM_FAILED ) 

    {

	std::cerr << "fhi1 sem init failed" << std::endl;

	return 1;

    }

if ( (semGHI = sem_open("/my_semaphoreGHI", O_CREAT, 0777, 0)) == SEM_FAILED ) 

    {

	std::cerr << "ghi sem init failed" << std::endl;

	return 1;

    }

if ( (semKI = sem_open("/my_semaphoreKI", O_CREAT, 0777, 0)) == SEM_FAILED ) 

    {

	std::cerr << "sem ki init failed" << std::endl;

	return 1;

    }
 if ( (semKI1 = sem_open("/my_semaphoreKI1", O_CREAT, 0777, 0)) == SEM_FAILED ) 

    {

	std::cerr << "sem ki init failed" << std::endl;

	return 1;

    }

unsigned int thread_count = 0;

    err = pthread_create(&tid[thread_count], NULL, thread_a, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

err = pthread_create(&tid[thread_count], NULL, thread_b, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

err = pthread_create(&tid[thread_count], NULL, thread_c, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

err = pthread_create(&tid[thread_count], NULL, thread_d, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

err = pthread_create(&tid[thread_count], NULL, thread_f, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

 err = pthread_create(&tid[thread_count], NULL, thread_h, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

err = pthread_create(&tid[thread_count], NULL, thread_i, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

err = pthread_create(&tid[thread_count], NULL, thread_k, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

 err = pthread_create(&tid[thread_count], NULL, thread_g, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

 err = pthread_create(&tid[thread_count], NULL, thread_e, (void *) 1);

        if (err != 0)

	std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    else

	++thread_count;

     for (int i = 0; i < thread_count; ++i) {

    pthread_join(tid[i], NULL);

    }

    pthread_mutex_destroy(&lock);

    sem_close(semACB);

    sem_close(semDBC);

    sem_close(semEC);

    sem_close(semEC1);

    sem_close(semFHI);

    sem_close(semFHI1);

    sem_close(semGHI);

    sem_close(semKI);

    sem_close(semKI1);

    sem_unlink("/my_semaphoreACB");

    sem_unlink("/my_semaphoreDBC");

    sem_unlink("/my_semaphoreEC");

    sem_unlink("/my_semaphoreEC1");

    sem_unlink("/my_semaphoreFHI");

    sem_unlink("/my_semaphoreFHI1");

    sem_unlink("/my_semaphoreGHI");

    sem_unlink("/my_semaphoreKI");

    sem_unlink("/my_semaphoreKI1");

    std::cout << std::endl;

    return 0;

}

