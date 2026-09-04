#include "server/server.h"
#include "storage/storage.h"
#include "data_queries/get.h"
#include "data_queries/post.h"

#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

char option[10];

int main()
{
    storage_start();
  /* 
    * TESTING NEW FUNCTIONS ON MAIN:
    server_start();
    char* result = get_data_by_id(120);
    printf("Message: %s\n", result);
    char* nmessage = "John is the best\n";
    post_new_message(nmessage);
    restore_from_backup();
    backup_data();
   */
    do {
      printf("Would you like to add a new message? [y/n]: ");
      if (fgets(option, sizeof(option), stdin) != NULL) {
        option[strcspn(option, "\n")] = 0;
        if (strcmp(option, "y") == 0) {
          char nmessage[256];
          printf("What message would you like to add: ");
          if (fgets(nmessage, sizeof(nmessage), stdin) != NULL){
            post_new_message(nmessage);
          }
        };
      }
    } while (strcmp(option, "n") != 0);

    printf("hello, world! \n");
    return 0;
}
