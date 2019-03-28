#ifndef IPC_TOOLS_H
#define IPC_TOOLS_H
#include <sys/types.h>

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
};

int semalloc(key_t key, int valInit);
void V(int semid);
void P(int semid);
int semfree(int semid);
void *shmalloc(key_t key, int size);
int shmfree(key_t key);

#endif
