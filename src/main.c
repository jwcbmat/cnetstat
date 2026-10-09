#include "storage/storage.h"
#include "data_queries/get.h"
#include "data_queries/post.h"

#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

char option[10];

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection (void *cls, struct MHD_Connection *connection,
    const char *url,
    const char *method, const char *version,
    const char *upload_data,
    size_t *upload_data_size, void **req_cls)
{
    const char *page  = "<html><body>Hello, browser!</body></html>";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer (strlen (page),
        (void*) page, MHD_RESPMEM_PERSISTENT);

    ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    MHD_destroy_response (response);

    return ret;
}

int main()
{
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
        &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar ();
    MHD_stop_daemon (daemon);
    storage_start();

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
