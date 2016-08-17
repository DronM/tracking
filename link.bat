#!/bin/sh
gcc trservd.o db_manager_my_sql.o server.o tracker_report_syst.o common.o $(mysql_config --cflags) $(mysql_config --libs) -o trservd
