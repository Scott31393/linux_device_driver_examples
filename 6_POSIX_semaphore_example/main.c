#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>



sem_t sem;
static int sem_value;
static int count = 1;

void *thread(void *arg){

    /*Switch to 0 sem*/
    sem_wait(&sem); 

    /*Get the value of int pointed by sem and printf*/
    sem_getvalue(&sem, &sem_value);
    printf("Thread %d esecution, Semaphore value switched to %d (Occupied resource)\n",count, sem_value);

    sleep(4);

    /*Switch to 1 sem again*/
    sem_post(&sem);
    sem_getvalue(&sem, &sem_value);

    /*Get the value of int pointed by sem and printf*/
    printf("Exit, Semaphore switched to  %d (Resource freed) \n",sem_value);
    count++;
}

int main(){
    /*Initialized semaphore with value 1, 0 means that this semaphore is shared between threads*/
    sem_init(&sem,0, 1); 
    pthread_t t1,t2;    
    
    /* Thread 1 is create and execute the thread() function (sem = 0, resource occupied, with function "sem_wait")
    after the complete execution and in the exit (sem = 1, resource free, with function "sem_post")*/
    pthread_create(&t1, NULL, thread,NULL); 
    sleep(2);

    /* Thread 2 is create and execute (the thread() function) (sem = 0, resource occupied, with function "sem_wait")
    after the complete execution and in the exit (sem = 1, resource free, with function "sem_post")*/
    pthread_create(&t2, NULL, thread, NULL);
    
    /* Master thread wait the end of the slave threads*/
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    /*Destroy semaphore */
    sem_destroy(&sem);
    
    
    }



























////Binario a decimale
//     int bit;
//     int n_bit = 8;
//     int N_bin[n_bit];
//     int len = sizeof(N_bin)/sizeof(int);

//     int *head = &(N_bin[0]);
//     int *tail = &(N_bin[len]);
//     int i = 0;

//     int decimale;

//     printf("Inserisci quanti bit ha il tuo numero binario = ");
//     scanf("%i", &n_bit);
//     N_bin[n_bit];

//     printf("Inserisci il tuo numero binario = ");
//     while(i < n_bit){
//         scanf("%i", &(N_bin[i]));
//         i++;
//         if( i == n_bit){
//             break;
//         }
//     }

//     printf("Il tuo numero binario è = ");
//     for(int i = 0; i < n_bit; i++){
//         printf("%d", N_bin[i]);
//     }
//     printf("\n");    
    
//     double esp=0;
//     double pot_2 = 0;
    
//     for(int i = n_bit-1; i >= 0; i--){
//         pot_2 = pow(2.0, esp);
//         printf("%i\n", (int) pot_2);
//         decimale += N_bin[i]*pot_2;
//         printf("%i\n", decimale); 
//         esp = esp +1;
        
//     }

//     printf("In decimale è uguale a = %d", decimale);






// ////inverso di una stringa

//     void invstr( char frase[]){
//     int len = strlen(frase);
//     char str[len];
//     strcpy(str, frase);
    
    
//     char *head, *tail;
//     head = &str[0];
//     tail = &str[len];

//     while(tail != head){
//         if( *tail == ' ' ){
//             *tail = '\0';
//             printf("%s", tail + 1);
//         }
//         tail--;
//     }
//     printf("%s",head);
//     }