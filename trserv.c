#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "server.h"

/* db connection variables */
char *server= NULL;
char *user=NULL;
char *password=NULL;
char *database=NULL;
char *port=NULL;

/*
*/
int main(int argc, char *argv[]){
	int c;
	while ((c = getopt (argc, argv, "u:h:p:P:d:")) != -1)		
         switch (c)
           {
           case 'u':
             user = optarg;
             break;
           case 'h':
             server = optarg;
             break;
           case 'p':
             password = optarg;
             break;
           case 'd':
             database = optarg;
             break;
           case 'P':
             port = optarg;
             break;
           case '?':
             if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
             return 1;
           default:
             abort ();
           }

	int error_mark = 0;
	if(!server) {
		printf("Server is not defined.\n");
		error_mark = 1;
	}
	if(!user) {
		printf("User name is not defined.\n");
		error_mark = 1;
	}
	if(!password) {
		printf("Password is not defined.\n");
		error_mark = 1;
	}
	if(!database) {
		printf("Database name is not defined.\n");
		error_mark = 1;
	}
	if(!port) {
		printf("Port is not defined.\n");
		error_mark = 1;
	}
	if(error_mark) {
		printf("Programm is terminated due to errors.\n");
		exit(1);
	}
	
	printf("Server is started with following params:\n");
	printf ("host=%s, user=%s, password=%s, database=%s, port=%s\n",
               server, user, password,database,port);
			   
	//Data for testing
	/*
	unsigned char buf[]={175,132,39,32,50,49,59,37,42,42,37,89,40,63,122,32,97,64,130,45,32,32,33,43,82,70,56,101,90,34,32,43,51,32,33,
		32,33,32, 32, 32, 32, 32, 33, 43, 47, 60, 32, 82, 63};
		
	on_get_data(buf, sizeof(buf));
	*/
	
	//main programm
	start_server();

	exit(0);
}
