#include "server/server.h"
#include "storage/storage.h"

#include <stdio.h>
#include <sys/socket.h>

int main()
{
    server_start();
    storage_start();

    printf("hello, world! \n");
    return 0;
}
