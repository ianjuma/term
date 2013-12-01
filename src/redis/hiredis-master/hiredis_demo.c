#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hiredis.h"

int main(int argc, char **argv) {

    redisContext *c;
    redisReply *reply;

    const char *hostname = "127.0.0.1";
    const int port = 6379;

    struct timeval timeout = { 1, 500000 };

    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis Context\n");
        }
        exit(-1);
    }

    reply = redisCommand(c, "PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);

    reply = redisCommand(c, "SET %s %s", "foo", "Ian Juma");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    reply = redisCommand(c, "GET %s", "foo");
    printf("GET: foo -> %s\n", reply->str);
    freeReplyObject(reply);

    reply = redisCommand(c, "SET %b %b", "counter", (size_t) 1);
    printf("SET counter %s\n", reply->str);
    freeReplyObject(reply);

    int count;
    for (count = 0; count < 1000; count++) {

        reply = redisCommand(c, "INCR counter");

    }

    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);

    reply = redisCommand(c, "DEL %s", "foo");
    printf("STRANGE: %s\n", reply->str);
    freeReplyObject(reply);


    redisFree(c);

    return 0;
}
