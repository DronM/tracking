#include "tracker_report_syst.h"

int on_get_data_rep_syst(unsigned char *buf, int buflen){	
	// checking the header	
	if (buflen>2 && (buf[0]!=TRACKER_DATA_PREF_0 || buf[1]!=TRACKER_DATA_PREF_1)){
		return RET_TYPE_WRONG_HEADER;//not this type tracker data
	}
	
	if (connect_to_db(server, user, password, database)==0){
		perror(UNABLE_TO_CONNECT_TO_DB);
		return RET_TYPE_ERROR;
	}
	
	//SQL data struc
	POSITION_DATA data;
	
	unsigned char *c;
	for (c=&buf[DATA_REMOVAL_START];c<&buf[buflen-DATA_REMOVAL_STOP];c++){
		*c -= DATA_REMOVAL_CHAR;
	}
	
	if (buf[2]==CADR_RS909_NO_BACK_REP || buf[2]==CADR_RS909_BACK_REP){
		//printf("Tracker 909 siganl...");
		//tracker data struc
		PRS909_DATA tracker_data = (PRS909_DATA) buf;
		
		//id
		unsigned int id = tracker_data->id[0]*100000000+tracker_data->id[1]*1000000+tracker_data->id[2]*10000+tracker_data->id[3]*100;
		sprintf(data.id,"%u",id);
		
		//date time
		struct tm tm_str;
		tm_str.tm_year = tracker_data->time_year+2000-1900;
		tm_str.tm_mon = tracker_data->date_month-1;
		tm_str.tm_mday = tracker_data->date_day;
		tm_str.tm_hour = tracker_data->time_hour+GMT_TIME_DIFF;
		tm_str.tm_min = tracker_data->time_minute;
		tm_str.tm_sec = tracker_data->time_sec;
		tm_str.tm_isdst = 0;
		data.dt = mktime(&tm_str);
		if (data.dt==-1){
			perror(ERROR_DATETIME_VAL);
			return RET_TYPE_ERROR;
		}
			
		//lat
		sprintf(data.lat,"%d%02d.%d",tracker_data->lat_deg,tracker_data->lat_min,(tracker_data->lat_dec[0]*100+tracker_data->lat_dec[1]));
		
		//lon
		sprintf(data.lon,"%03d%02d.%d",tracker_data->lon_deg[0]*100+tracker_data->lon_deg[1],
			tracker_data->lon_min,(tracker_data->lon_dec[0]*100+tracker_data->lon_dec[1]));
			
		//gps Status
		data.gpsStatus = (strlen(data.lat)==VALID_LAT_LEN
						&& strlen(data.lon)==VALID_LON_LEN)? 1:0;
		
		//ns ew
		switch (tracker_data->coord_Status){
			case COORD_STATUS_NE:
				data.ns = (char)DIR_N;
				data.ew = (char)DIR_E;
				break;
			case COORD_STATUS_SE:
				data.ns = (char)DIR_S;
				data.ew = (char)DIR_E;
				break;
			case COORD_STATUS_NW:
				data.ns = (char)DIR_N;
				data.ew = (char)DIR_W;
				break;
			case COORD_STATUS_SW:
				data.ns = (char)DIR_S;
				data.ew = (char)DIR_W;
				break;
			default :	
				data.ns = (char)DIR_S;
				data.ew = (char)DIR_W;			
		}
		
		//speed
		data.speed = (tracker_data->speed[0]*100 + tracker_data->speed[1])/10;
		//heading
		data.heading = tracker_data->heading[0]*100 + tracker_data->heading[1];
		//from memory
		data.fromMemory = (tracker_data->cadr_type==99)? 1:0;
		//odometer
		data.odometer = tracker_data->odometer[0]*1000000 + tracker_data->odometer[1]*10000+
							  tracker_data->odometer[2]*100 + tracker_data->odometer[3];
		
		//sensors
		data.sensor1 = tracker_data->analog_sensor1[0] + (float)tracker_data->analog_sensor1[1]/100;
		data.sensor2 = tracker_data->analog_sensor2[0] + (float)tracker_data->analog_sensor2[1]/100;
		data.sensorsIn = tracker_data->sensors_in_out[0];
		data.sensorsOut = tracker_data->sensors_in_out[1];
		data.voltage = tracker_data->voltage[0] + (float)tracker_data->voltage[1]/100;
		data.engine= ((tracker_data->sensors_in_out[0] && (1 << 1)) != 0)? 1:0;
		
		//lon lat degree
		data.lat_deg = NMEAStrToDegree(data.lat);
		data.lon_deg = NMEAStrToDegree(data.lon);
		
	}
	else if (buf[2]==CADR_RS1102_NO_BACK_REP || buf[2]==CADR_RS1102_BACK_REP){
//syslog(LOG_INFO,"TRACKING got 1102 data\n");
		//tracker data struc
		//printf("Tracker 1102 siganl...\n");
		PRS1102_DATA tracker_data = (PRS1102_DATA) buf;
		
		uint64_t id = (uint64_t)tracker_data->id[0]*100000000+
			tracker_data->id[1]*1000000+
			tracker_data->id[2]*10000+
			tracker_data->id[3]*100+
			tracker_data->id[4];
		#ifndef WIN32
		sprintf(data.id,"%llu",id);
		#else
		sprintf(data.id,"%I64u",id);
		#endif
		
		//date time
		struct tm tm_str;
		tm_str.tm_year = tracker_data->time_year+2000-1900;
		tm_str.tm_mon = tracker_data->date_month-1;
		tm_str.tm_mday = tracker_data->date_day;
		tm_str.tm_hour = tracker_data->time_hour+GMT_TIME_DIFF;
		tm_str.tm_min = tracker_data->time_minute;
		tm_str.tm_sec = tracker_data->time_sec;
		tm_str.tm_isdst = 0;
		data.dt = mktime(&tm_str);
		if (data.dt==-1){
			perror(ERROR_DATETIME_VAL);
			return RET_TYPE_ERROR;
		}
			
		//lat
		sprintf(data.lat,"%d%02d.%d",tracker_data->lat_deg,tracker_data->lat_min,(tracker_data->lat_dec[0]*100+tracker_data->lat_dec[1]));
		
		//lon
		sprintf(data.lon,"%03d%02d.%d",tracker_data->lon_deg[0]*100+tracker_data->lon_deg[1],
			tracker_data->lon_min,(tracker_data->lon_dec[0]*100+tracker_data->lon_dec[1]));
			
		//gps Status
		data.gpsStatus = (strlen(data.lat)==VALID_LAT_LEN
						&& strlen(data.lon)==VALID_LON_LEN)? 1:0;
		
		//ns ew
		switch (tracker_data->coord_Status){
			case COORD_STATUS_NE:
				data.ns = (char)DIR_N;
				data.ew = (char)DIR_E;
				break;
			case COORD_STATUS_SE:
				data.ns = (char)DIR_S;
				data.ew = (char)DIR_E;
				break;
			case COORD_STATUS_NW:
				data.ns = (char)DIR_N;
				data.ew = (char)DIR_W;
				break;
			case COORD_STATUS_SW:
				data.ns = (char)DIR_S;
				data.ew = (char)DIR_W;
				break;
			default :	
				data.ns = (char)DIR_S;
				data.ew = (char)DIR_W;			
		}
		
		//speed
		data.speed = (tracker_data->speed[0]*100 + tracker_data->speed[1])/10;
		//heading
		data.heading = tracker_data->heading[0]*100 + tracker_data->heading[1];
		//from memory
		data.fromMemory = (tracker_data->cadr_type==99)? 1:0;
		//odometer
		data.odometer = tracker_data->odometer[0]*1000000 + tracker_data->odometer[1]*10000+
							  tracker_data->odometer[2]*100 + tracker_data->odometer[3];
		
		//sensors
		data.sensor1 = tracker_data->analog_sensor1[0] + (float)tracker_data->analog_sensor1[1]/100;
		data.sensor2 = tracker_data->analog_sensor2[0] + (float)tracker_data->analog_sensor2[1]/100;
		data.sensorsIn = tracker_data->sensors_in[0];
		data.sensorsOut = tracker_data->sensors_out;
		data.voltage = tracker_data->voltage[0] + (float)tracker_data->voltage[1]/100;
		data.engine= ((tracker_data->sensors_in[0] && (1 << 1)) != 0)? 1:0;
		
		//lon lat degree
		data.lat_deg = NMEAStrToDegree(data.lat);
		data.lon_deg = NMEAStrToDegree(data.lon);
	}
	else{
		perror(UNSUPPORTED_CADR_ID);
		return RET_TYPE_ERROR;		
	}
		
//syslog(LOG_INFO,"TRACKING before writing report");	
	write_position_report(&data);
	
	return RET_TYPE_OK;
}
