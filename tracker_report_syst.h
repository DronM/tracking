#ifndef _TRACKER_REPORT_SYST_
#define _TRACKER_REPORT_SYST_

#include <time.h>
#include <stdint.h>

#include "common.h"
#include "db_manager_mysql.h"

/*removing value and its starting position*/
#define DATA_REMOVAL_CHAR	0x20
#define DATA_REMOVAL_START	2
#define DATA_REMOVAL_STOP	2

/*data prefix values*/
#define TRACKER_DATA_PREF_0	0xaf
#define TRACKER_DATA_PREF_1	0x84

/*values for cadr field*/
#define CADR_RS909_NO_BACK_REP	7
#define CADR_RS909_BACK_REP	8
//#define CADR_RS906_NO_BACK_REP	5
//#define CADR_RS906_BACK_REP	6
#define CADR_RS1102_NO_BACK_REP	5
#define CADR_RS1102_BACK_REP	6


/*values for status field*/
#define COORD_STATUS_NE	5
#define COORD_STATUS_SE 6
#define COORD_STATUS_NW	7
#define COORD_STATUS_SW	8

#define DIR_N	'n'
#define DIR_S	's'
#define DIR_E	'e'
#define DIR_W	'w'

/*correcrt coord lengths*/
#define VALID_LAT_LEN	9
#define VALID_LON_LEN	10


/*messages*/
#define HEADER_CORRUPT	"Header data is not correct"
#define UNSUPPORTED_CADR_ID "Cadr value is not supported"
#define ERROR_DATETIME_VAL	"Datetime value is incorrect"
#define UNABLE_TO_CONNECT_TO_DB	"Unable to connect to data base"

typedef struct _HEADER_DATA{
	unsigned char byte_0;
	unsigned char byte_1;
}HEADER_DATA,*PHEADER_DATA;

typedef struct _FOOTER_DATA{
	unsigned char byte_0;
	unsigned char byte_1;
}FOOTER_DATA, *PFOOTER_DATA;

typedef struct _RS906_DATA{
	unsigned char header_byte_0;
	unsigned char header_byte_1;
	unsigned char cadr_id;
    unsigned char cadr_type;
    unsigned char time_hour;
    unsigned char time_minute;
    unsigned char time_sec;
    unsigned char date_day;
    unsigned char date_month;
    unsigned char time_year;
    unsigned char coord_Status;
    unsigned char lat_deg;
    unsigned char lat_min;
    unsigned char lat_dec[2];
    unsigned char lon_deg[2];
    unsigned char lon_min;
    unsigned char lon_dec[2];
    unsigned char speed[2];
    unsigned char heading[2];
    unsigned char id[5];
    unsigned char sensors_in_out[2];
    unsigned char voltage[2];
    unsigned char RFID[4];
    unsigned char odometer[4];
    unsigned char analog_sensor1[2];
    unsigned char analog_sensor2[2];
    unsigned char os_version;
    unsigned char CRC[3];
	unsigned char footer_byte_0;
	unsigned char footer_byte_1;
}RS906_DATA, *PRS906_DATA;

typedef struct _RS909_DATA{
	unsigned char header_byte_0;
	unsigned char header_byte_1;
	unsigned char cadr_id;
    unsigned char cadr_type;
    unsigned char time_hour;
    unsigned char time_minute;
    unsigned char time_sec;
    unsigned char date_day;
    unsigned char date_month;
    unsigned char time_year;
    unsigned char coord_Status;
    unsigned char lat_deg;
    unsigned char lat_min;
    unsigned char lat_dec[2];
    unsigned char lon_deg[2];
    unsigned char lon_min;
    unsigned char lon_dec[2];
    unsigned char speed[2];
    unsigned char heading[2];
    unsigned char id[5];
    unsigned char sensors_in_out[2];
    unsigned char voltage[2];
    unsigned char RFID[4];
    unsigned char odometer[4];
    unsigned char analog_sensor1[2];
    unsigned char analog_sensor2[2];
    unsigned char os_version;
    unsigned char CRC[3];
	unsigned char footer_byte_0;
	unsigned char footer_byte_1;
}RS909_DATA, *PRS909_DATA;

typedef struct _RS1102_DATA{
	unsigned char header_byte_0;
	unsigned char header_byte_1;
	unsigned char cadr_id;
    unsigned char cadr_type;
    unsigned char time_hour;
    unsigned char time_minute;
    unsigned char time_sec;
    unsigned char date_day;
    unsigned char date_month;
    unsigned char time_year;
    unsigned char coord_Status;
    unsigned char lat_deg;
    unsigned char lat_min;
    unsigned char lat_dec[2];
    unsigned char lon_deg[2];
    unsigned char lon_min;
    unsigned char lon_dec[2];
    unsigned char speed[2];
    unsigned char heading[2];
    unsigned char id[5];	
	unsigned char sensors_in[3];
	unsigned char sensors_out;
	unsigned char analog_sensor1[2];
	unsigned char analog_sensor2[2];
	unsigned char analog_sensor3[2];
	unsigned char analog_sensor4[2];
	unsigned char analog_sensor5[2];
	unsigned char analog_sensor6[2];
	unsigned char extra_power[2];
	unsigned char voltage[2];
	unsigned char odometer[4];
    unsigned char os_version;
    unsigned char CRC[3];
	unsigned char footer_byte_0;
	unsigned char footer_byte_1;
}RS1102_DATA, *PRS1102_DATA;

/*
	function declaration
*/
int on_get_data_rep_syst(unsigned char *buf, int buflen);

extern char *server;
extern char *user;
extern char *password;
extern char *database;
extern char *port;

extern void write_position_report(PPOSITION_DATA);
#endif
