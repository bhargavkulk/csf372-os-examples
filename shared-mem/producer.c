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
    int *shm;
    key_t key = IPC_PRIVATE;
    int flag = SHM_R | SHM_W; //flags set to Shared memory read and write to allow said operations

    srand(time(0));
    if(argc == 2)
    {
        //setting key to be the command line argument
        key = atoi(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: %s key\n", argv[0]);
        exit(2);
    }
    shmid = shmget(key, 1000, flag); //attempting to access the shared memory corresponding to the key.
    if(shmid < 0) {
        shmid = shmget(key, 1000, flag | IPC_CREAT); //adding the IPC_CREAT flag to indicate that the shared memory needs to be created.
        if (shmid < 0) {
            perror("shmget | IPC_CREAT"); 
            exit(1);
        }
    }
    shm = (int *) shmat(shmid, NULL, 0); //letting the operating system pick the address, stroing the returned pointer in shm.
    if(shm == (int *) -1)
    {
        perror("shmat");
        exit(1);
    }
    *shm = 1;
    for(int i = 0; i < 100; i++)
    {
        if(*shm < 8)
        {
            (*shm)++;
            printf("Producer -> Updated shelf : %d to %d units\n",*shm - 1, *shm);
        }
        else
        {
            printf("Producer -> Already at Max units of %d\n", *shm);
        }
        int slp = (rand() % (3 - 1 + 1)) + 1; //sleeping for a random time between 1 and 3 seconds.
        sleep(slp);
    }
    shmdt(shm); //detaching the shared memory block
    shmctl(shmid, IPC_RMID, 0); //Removing the shared memory object
    
}
