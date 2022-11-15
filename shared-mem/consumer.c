#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int shmid;
    key_t key = IPC_PRIVATE;
    int flag = SHM_R | SHM_W; //flags to allow read and write in shared memory
    int * shm;
    
    srand(time(0));
    if(argc == 2)
    {
        key = atoi(argv[1]); //setting key to be the command line argument
    }
    else
    {
        fprintf(stderr, "Usagee: %s key\n", argv[0]);
        exit(2);
    }
    printf("Trying shared memory with key : %d\n", key);
    shmid = shmget(key, 1000, flag); //creating access to the shared memory block using the key. No IPC_CREAT as this program should only connect to the producer which will make the shared memory.
    if(shmid < 0)
    {
        perror("shmget");
        exit(1);
    }
    else
    {
        printf("Shared memory: %d\n", shmid);
    }
    shm = (int *)shmat(shmid, NULL, 0); //using shmat to attach to the shared memory block. Returns pointer to shm that can be used to access it.
    if(shm == (int *)-1)
    {
        perror("shmat");
        exit(1);
    }
    for(int i = 0; i < 20; i++)
    {
        if(*shm > 0)
        {
            (*shm)--;
            printf("Consumer -> Updated shelf : %d to %d units\n",*shm + 1, *shm);
        }
        else
        {
            printf("Consumer -> No units to consume (%d)!\n", *shm);
        }
        int slp = (rand() % (7 - 3 + 1)) + 3; //sleeping for a random time in between 3 an 7 seconds
        sleep(slp);
    }
    shmdt((void *)shm); //detaching from the shared memory
}
