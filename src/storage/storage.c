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
char data_path[PATH_MAX];
FILE* file;
sqlite3 *db = NULL;

void db_start() {
  LOG("Creating database... \n");
  char* errMsg =  NULL;
  char query[] = "CREATE TABLE data_test(id INTEGER PRIMARY KEY AUTOINCREMENT, message TEXT)";
  sqlite3_open(data_path, &db);
  int result = sqlite3_exec(db, query, 0, 0,&errMsg);

  if (result != SQLITE_OK && errMsg != NULL) {
    printf("Error starting database. Error: %s\n", errMsg);
    sqlite3_free(errMsg);
  }
}

int file_write_callback(void* data, int argc, char** argv, char** azColName) {
  DataTest* messages = (DataTest*)data;
  snprintf(messages->message, sizeof(messages->message), "%s",argv[1]);
  file = fopen(storagef, "a+");
  if (!file) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  const char* result = messages->message;
  fputs(result, file);
  fclose(file);
  return 0;
}

void write_data_on_backup() {
  char* errMsg =  NULL;
  DataTest message = {0, ""};
  sqlite3_open(data_path, &db);
  int result = sqlite3_exec(db, "SELECT * FROM data_test", file_write_callback, &message, &errMsg);
  if (result != SQLITE_OK && errMsg != NULL) {
    printf("Error retrieving from database. Error: %s", errMsg);
    sqlite3_free(errMsg);
  }
}

void load_to_memory_from_backup() {
  char* errMsg =  NULL;
  file = fopen( storagef, "r");
  char line[256];


  sqlite3_open(data_path, &db);
  const char *delete_query = "DELETE FROM data_test";
  int result = sqlite3_exec(db, delete_query, 0, 0,&errMsg);
  if (result != SQLITE_OK && errMsg != NULL){
    printf("Error reseting database. Error: %s", errMsg);
    sqlite3_free(errMsg);
  }

  fgets(line, sizeof(line), file);
  do {
    char query[PATH_MAX];
    snprintf(query, sizeof(query), "INSERT INTO data_test(message) VALUES('%s')", line);
    result = sqlite3_exec(db, query, 0, 0,&errMsg);
    if (result != SQLITE_OK && errMsg != NULL){
      printf("Error inserting into database. Error: %s", errMsg);
      sqlite3_free(errMsg);
    }
    fgets(line, sizeof(line), file);
  } while (feof(file) == 0);
}

void wipe_backup() {
  file = fopen(storagef, "w");
  fflush(file);
}


void storage_start() {
    LOG("Starting storage... \n");
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("getcwd() error");
        exit(1);
    }
    snprintf(storagef, sizeof(storagef), "%s/backup/data.txt", cwd);
    snprintf(data_path, sizeof(data_path), "%s/database", cwd);

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

    db_start();
    free(cwd);
}
