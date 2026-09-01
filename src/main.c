#include "server/server.h"
#include "storage/storage.h"
#include "data_queries/get.h"

#include <stdio.h>

int main()
{
    server_start();
    storage_start();
    char* result = get_data_by_id(2341234);
    if (result != NULL) {
      printf("Message: %s\n", result);
    }else {
      perror("Message not found");
    }

    printf("hello, world! \n");
    return 0;
}
