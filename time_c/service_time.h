#ifndef __SERVICE_TIME_H__
#define __SERVICE_TIME_H__

#include <stdio.h>  

typedef struct 
{
    int year;
    int mouth;
    int day;
    int week;
    int hour;
    int minute;
    int second;
}service_time_t;

int get_time_local_common(service_time_t *cur_time);
int get_time_local_string(char *time_str, size_t buf_len);
int get_time_utc_common(service_time_t *utc_time);
int get_time_utc_string(char *time_str, size_t buf_len);
int get_timezone();

#endif