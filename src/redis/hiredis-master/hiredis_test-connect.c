#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hiredis.c"
#include "hiredis.h"


int 
main(void) {
	redisReply *reply;
	long int i;


    clock_t start = clock();

	redisContext *c = redisConnect
                 ("ec2-**-**-***-**.compute-1.amazonaws.com", 6379);

    if (c->err) {
        	printf("Error: %s\n", c->errstr);
    	}else{
        	printf("Connection Made! \n");
    	}


    reply = redisCommand(c, "keys %s", "*");
	if ( reply->type == REDIS_REPLY_ERROR )
  		printf( "Error: %s\n", reply->str );
	else if ( reply->type != REDIS_REPLY_ARRAY )
  		printf( "Unexpected type: %d\n", reply->type );
	else {
  		for ( i=0; i < reply->element; ++i ){
    		   printf( "Result:%lu: %s\n", i,
                      reply->element[i]->str );
  		}
	}
	printf( "Total Number of Results: %lu\n", i );

    printf ( "%f Seconds\n", ( (double)clock() - start ) /
                      CLOCKS_PER_SEC );

    freeReplyObject(reply);
    return 0;

}
