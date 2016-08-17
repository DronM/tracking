#include "common.h"

float NMEAStrToDegree(char *str){
	if (strlen(str)>3){
		if (*str=='0'){
			str++;
		}		
		char deg_str[3];
		deg_str[0] = *str;
		str++;
		deg_str[1] = *str;
		deg_str[2] = '\0';		
		str++;
		float deg,min;
		deg = atof(deg_str);
		min = atof(str);
		return deg + (float)min/60.0;
	}
}