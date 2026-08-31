#include "storage.h"
#include "../server/server.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <sqlite3.h>

#define LOG(s) fputs(s, stderr)

char storagef[PATH_MAX];
FILE* file;


int write_data_on_backup() {
  //TODO: get data stream and alocate it into a variable to persist it;
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
    //TODO: populate the data from backup into a linked list;
    printf("%s", line);

    fgets(line, sizeof(line), file);
  } while (feof(file) == 0);

  return 0;
}

int wipe_backup() {
  file = fopen(storagef, "w");
  fflush(file);
  return 0;
}

void db_start(const char *cwd) {
  LOG("Creating database... \n");
  printf("%s", cwd);
  sqlite3 *db = NULL;
  char data_path[PATH_MAX];
  snprintf(data_path, sizeof(data_path), "%s/database", cwd);
  sqlite3_open(data_path, &db);
  char query[] = "CREATE TABLE data_test(id INTEGER PRIMARY KEY AUTOINCREMENT, message TEXT)";
  sqlite3_exec(db, query, 0, 0,0);
}

void storage_start() {
    LOG("Starting storage... \n");
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("getcwd() error");
        exit(1);
    }
    db_start(cwd);

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
