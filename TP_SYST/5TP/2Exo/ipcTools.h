#ifndef IPC_TOOLS_H
#define IPC_TOOLS_H
#include <sys/types.h>

int semalloc(key_t key, int valInit);
void V(int semid);
void P(int semid);
int semfree(int semid);
void *shmalloc(key_t key, int size);
int shmfree(key_t key);

#endif
