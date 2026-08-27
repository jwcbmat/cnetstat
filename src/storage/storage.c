#include "storage.h"
#include "../server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

#define LOG(s) fputs(s, stderr)

char storagef[PATH_MAX];
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
    LOG("Starting storage... \n");
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("getcwd() error");
        exit(1);
    }

    char backup_path[PATH_MAX];
    snprintf(backup_path, sizeof(backup_path), "%s/backup", cwd);
    if (mkdir(backup_path, 0777) == -1)
    {
      if (errno != EEXIST)
      {
        perror("Error creating backup directory");
        free(cwd);
        exit(1);
      }
    }

    snprintf(storagef, sizeof(storagef), "%s/backup/data.txt", cwd);
    free(cwd);

    write_data_on_backup();
    load_to_memory_from_backup();
}
