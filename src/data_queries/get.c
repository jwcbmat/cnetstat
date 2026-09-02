#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include "../storage/storage.h"

DataTest messages = {0, ""};

int return_write_callback(void* data, int argc, char** argv, char** azColName) {
  DataTest* result = (DataTest*)data;
  if (argv != NULL) {
    if (argv[0] != NULL) {
      snprintf(messages.message, sizeof(messages.message), "%s", argv[0]);
    }
  }
  return 0;
}

char* get_data_by_id(const int id) {
  char *errMsg = NULL;
  char query[PATH_MAX];
  snprintf(query, sizeof(query), "SELECT message FROM data_test WHERE id = %d", id);
  int result = sqlite3_exec(db, query, return_write_callback, &messages, &errMsg);
  if (result != SQLITE_OK && errMsg != NULL) {
    printf("Error getting data. Error: %s\n", errMsg);
    sqlite3_free(errMsg);
  }else if (strcmp(messages.message, "") == 0) {
    return errMsg;
  }
  return messages.message;
};
