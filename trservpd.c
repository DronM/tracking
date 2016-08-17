#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#include "tracker_report_syst.h"

//Unix daemonization
#ifndef WIN32
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <errno.h>
	#include <syslog.h>
	#include <string.h>
	#include <assert.h>
	#include <signal.h>	
#define DAEMON_NAME "trservd"
#define PID_FILE "/var/run/trservd.pid"
	
#endif

#include "server.h"

#define DEBUG 1

/* db connection variables */
char *server= NULL;
char *user=NULL;
char *password=NULL;
char *database=NULL;
char *port=NULL;
/*
char *server= "localhost";
char *user="root";
char *password="iamthemotherfucker";
char *database="tracking";
char *port="52020";
*/

/**************************************************************************
    Function: signal_handler
 
    Description:
        This function handles select signals that the daemon may
        receive.  This gives the daemon a chance to properly shut
        down in emergency situations.  This function is installed
        as a signal handler in the 'main()' function.
 
    Params:
        @sig - The signal received
 
    Returns:
        returns void always
**************************************************************************/
#ifndef WIN32
void signal_handler(int sig) {
    switch(sig) {
        case SIGHUP:
            syslog(LOG_WARNING, "Received SIGHUP signal.");
            break;
        case SIGTERM:
            syslog(LOG_WARNING, "Received SIGTERM signal.");
            break;
        default:
            syslog(LOG_WARNING, "Unhandled signal (%d) %s", strsignal(sig));
            break;
    }
}
#endif

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
	
//*** UNIX Demonization	 **************************************

    // Setup signal handling before we start
#ifndef WIN32
		signal(SIGHUP, signal_handler);
		signal(SIGTERM, signal_handler);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		
    syslog(LOG_INFO, "%s daemon starting up", DAEMON_NAME);
 
    // Setup syslog logging - see SETLOGMASK(3)
#if defined(DEBUG)
    setlogmask(LOG_UPTO(LOG_DEBUG));
    openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
#else
    setlogmask(LOG_UPTO(LOG_INFO));
    openlog(DAEMON_NAME, LOG_CONS, LOG_USER);
#endif
		
    /* Our process ID and Session ID */
    pid_t pid, sid;
		
	syslog(LOG_INFO, "starting the daemonizing process");

	/* Fork off the parent process */
	pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	/* If we got a good PID, then
	   we can exit the parent process. */
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	/* Change the file mode mask */
	umask(0);

	/* Create a new SID for the child process */
	sid = setsid();
	if (sid < 0) {
		/* Log the failure */
		exit(EXIT_FAILURE);
	}

	/* Change the current working directory */
	if ((chdir("/")) < 0) {
		/* Log the failure */
		exit(EXIT_FAILURE);
	}

	/* Close out the standard file descriptors */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
		
#endif
//*** UNIX Demonization	 **************************************

	//main programm
	start_server();

#ifndef WIN32	
	syslog(LOG_INFO, "%s daemon exiting", DAEMON_NAME);
#endif

	exit(0);
}
