#include <linux/limits.h>
#include <sqlite3.h>
#include <stdlib.h>

void storage_start();
void wipe_backup();
void backup_data();
void restore_from_backup();

extern sqlite3 *db;
extern char data_path[PATH_MAX];


typedef struct {
  int id;
  char message[PATH_MAX];
} DataTest;
