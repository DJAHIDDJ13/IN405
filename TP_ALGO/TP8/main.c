#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 200
#define L 16

typedef struct {
	int balance;
} INFO_CLIENT;

typedef struct {
	char* key;
	INFO_CLIENT donne;
	int next;
} HASH_TABLE;

char* generate_bankNo() {
	char* res = malloc(sizeof(char) * (L+1));
	res[L] = 0;
	for(int i=0; i<L; i++)
		res[i] = '0' + rand()%10;
	return res; 
}

char** generate_clients(int n) {
	char** clients = malloc(sizeof(char*) * n);
	for(int i=0; i<n; i++) {
		clients[i] = generate_bankNo();
	}
	return clients;
}

int hash(char* bankNo) {
	int h = 0;
	for(int i=0; i<L; i++) {
		h += (bankNo[i] - '0') * i;
	}
	return h % M;
}

HASH_TABLE* hash_insert(HASH_TABLE t[M], char* elem) {
	while() {
		
	}
}

int main() {
	srand(time(NULL));
	int n = rand()%101+100;
	char** clients = generate_clients(n);
	
	HASH_TABLE hash_table[M];
	for(int i=0; i<n; i++) {
		hash_table = hash_insert(hash_table, clients[i]);
	}
}
