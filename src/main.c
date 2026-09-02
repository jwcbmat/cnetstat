#include "server/server.h"
#include "storage/storage.h"
#include "data_queries/get.h"
#include "data_queries/post.h"

#include <linux/limits.h>
#include <stdio.h>

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

    printf("hello, world! \n");
    return 0;
}
