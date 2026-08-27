#include "storage.h"
#include "../server/server.h"
#include <stdio.h>
#include <stdlib.h>

const char* storagef = "storage/backup/data.txt";
FILE* file;


int write_data_on_backup() {
  //TODO: ler os dados aqui e alocar
  char message[] = "Hello, Persistence\n";

  file = fopen(storagef, "a+");
  if (!file) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  fputs(message, file);
  fclose(file);

  return 0;
}

int load_to_memory_from_backup() {
  file = fopen( storagef, "r");
  char line[256];

  fgets(line, sizeof(line), file);
  do {
    //TODO: ao inves de imprimir, popular os dados com uma lista encadeada.
    printf("%s", line);

    fgets(line, sizeof(line), file);
  } while (feof(file) == 0);

  return 0;
}

int wipe_backup() {
  return remove(storagef);
}

void storage_start() {
    printf("starting storage... \n");
    write_data_on_backup();
    load_to_memory_from_backup();
}
