#include <ctype.h>
#include <stdio.h>
#include <linux/limits.h>
#include "../storage/storage.h"


void post_new_message(char* nmessage) {
  char *errMsg = NULL;
  char query[PATH_MAX];
  if ((isblank(*nmessage)) != 0) {
    return;
  };
  snprintf(query, sizeof(query), "INSERT INTO data_test(message) VALUES('%s')", nmessage);
  int result = sqlite3_exec(db, query, 0, 0, &errMsg);
  if (result != SQLITE_OK && errMsg != NULL) {
    printf("Error posting data. Error: %s\n", errMsg);
    sqlite3_free(errMsg);
  }
}
