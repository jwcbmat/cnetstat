#include "server/server.h"
#include "storage/storage.h"

#include <stdio.h>

int main() {

    server_start();
    storage_start();

    printf("hello, world!");
    return 0;
}