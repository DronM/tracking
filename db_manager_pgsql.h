#ifndef _DB_MANAGER_PGSQL_
#define _DB_MANAGER_PGSQL_

#ifdef  WIN32
#include <windows.h>
#include <winsock.h>
#endif

#include "libpq-fe.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"
/*
	common constants
*/

#define QUERY_BUF_SIZE	500
#define LAT_STR_MAX_LEN 15
#define LON_STR_MAX_LEN 15
#define MAX_TRACKER_ID_SIZE	20

/*
	columns
*/
#define DB_TABLE	"car_tracking"
#define DB_COL_ID	"car_id"
#define DB_COL_PERIOD	"period"
#define DB_COL_LAT	"latitude"
#define DB_COL_LON	"longitude"
#define DB_COL_SPEED	"speed"
#define DB_COL_NS	"ns"
#define DB_COL_EW	"ew"
#define DB_COL_HEADING	"heading"
#define DB_COL_ODOMETER	"odometer"
#define DB_COL_SENSOR1	"p1"
#define DB_COL_SENSOR2	"p2"
#define DB_COL_VALID	"gps_valid"
#define DB_COL_FROM_MEM	"from_memory"
#define DB_COL_RECIEVED	"recieved_dt"
#define DB_COL_SENS_IN	"sensors_in"
#define DB_COL_SENS_OUT	"sensors_out"
#define DB_COL_VOLTAGE	"voltage"
#define DB_COL_ENGINE_ON	"engine_on"
#define DB_COL_LAT_DEG	"lat"
#define DB_COL_LON_DEG	"lon"

#define DEF_PG_PORT = "5432";

typedef struct _POSITION_DATA{
    char id[MAX_TRACKER_ID_SIZE];
    time_t dt;
    char lat[LAT_STR_MAX_LEN];
    char lon[LON_STR_MAX_LEN];
    char ns;
    char ew;
    int gpsStatus;
    float speed;
    float heading;
    int fromMemory;
    float odometer;
    float sensor1;
    float sensor2;
    int sensorsIn;
    int sensorsOut;
    float voltage;
    int engine;
    float lat_deg;
    float lon_deg;	
}
POSITION_DATA, *PPOSITION_DATA;

/* Here is the SQL database time structure which can
be treated as a continuous string.
*/ 
typedef char TIMSTM[20];
/*
	functions
*/
int query(char *qstring);
void DateTimeToSQL(time_t timeval,TIMSTM time_stmp);
time_t GetGMTTime(const time_t *timeval);
int connect_to_db(char *server, char *user, char *password,
					char *database);
int disconnect_from_db();
void write_position_report(PPOSITION_DATA PosRepData);
PGconn *db_connection;

extern char *server;
extern char *user;
extern char *password;
extern char *database;
extern char *port;

/* PGsql functions*/
extern PGconn * STDCALL PQsetdbLogin(const char *pghost,
                     const char *pgport,
                     const char *pgoptions,
                     const char *pgtty,
                     const char *dbName,
                     const char *login,
                     const char *pwd);
extern PGresult	* STDCALL PQexec(PGconn *conn,
			const char *command);
			
extern ExecStatusType STDCALL PQresultStatus(const PGresult *res);

extern void STDCALL PQfinish(PGconn *conn);

extern char * STDCALL PQerrorMessage(PGconn *conn);
/*
extern size_t STDCALL PQescapeStringConn (PGconn *conn,
                           char *to, const char *from, size_t length,
                           int *error);
*/						   
#endif
