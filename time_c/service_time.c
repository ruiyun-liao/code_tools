#include "service_time.h"
#include <time.h> 

int get_time_local_common(service_time_t *cur_time)
{
    time_t t;
    struct tm *tp;
    if((0 < time(&t)) && (NULL != (tp = localtime(&t))))
    {
        cur_time->year = tp->tm_year + 1900;
        cur_time->mouth = tp->tm_mon + 1;
        cur_time->week = tp->tm_wday;
        cur_time->day = tp->tm_mday;
        cur_time->hour = tp->tm_hour;
        cur_time->minute = tp->tm_min;
        cur_time->second = tp->tm_sec;
    }
    else
    {
        return -1;
    }
    return 0;
}

int get_time_local_string(char *time_str, size_t buf_len)
{
    time_t t;
    struct tm *tp;
    if((0 < time(&t)) && (NULL != (tp = localtime(&t))))
    {
        snprintf(time_str, buf_len, "%d/%02d/%02d %02d:%02d:%02d", 
            tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
    }
    else
    {
        return -1;
    }
    return 0;
}


int get_time_utc_common(service_time_t *utc_time)
{
    time_t t;
    struct tm *tp;
    if((0 < time(&t)) && (NULL != (tp = gmtime(&t))))
    {
        utc_time->year = tp->tm_year + 1900;
        utc_time->mouth = tp->tm_mon + 1;
        utc_time->week = tp->tm_wday;
        utc_time->day = tp->tm_mday;
        utc_time->hour = tp->tm_hour;
        utc_time->minute = tp->tm_min;
        utc_time->second = tp->tm_sec;
    }
    else
    {
        return -1;
    }
    return 0;
}

int get_time_utc_string(char *time_str, size_t buf_len)
{
    time_t t;
    struct tm *tp;
    if((0 < time(&t)) && (NULL != (tp = gmtime(&t))))
    {
         snprintf(time_str, buf_len, "%d/%02d/%02d %02d:%02d:%02d", 
            tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
    }
    else
    {
        return -1;
    }
    return 0;
}


int g_timezone = -100;
int get_timezone()
{
    if(-100 == g_timezone)
    {
        time_t t;
        struct tm *tp;
        if(0 < time(&t))
        {
            int second_utc = t % (24 * 60 * 60);
            if(NULL != (tp = localtime(&t)))
            {
                int second_local = tp->tm_hour * 3600 + tp->tm_min * 60 + tp->tm_sec;
                g_timezone = (second_local - second_utc) / (60 * 60);
                if(12 < g_timezone)
                {
                    g_timezone = 24 - timezone;
                }
            }
        }

    }
    return g_timezone; 
}


/*
int main()
{
    service_time_t time;
    printf("timezone = %d\n", get_timezone());

    if(0 <= get_time_local_common(&time))
    {
        printf("local time : %d/%d/%d week:%d  %d:%d:%d\n", time.year, time.mouth, time.day,
            time.week, time.hour, time.minute, time.second);
    }
    if(0 <= get_time_utc_common(&time))
    {
        printf("  utc time : %d/%d/%d week:%d  %d:%d:%d\n", time.year, time.mouth, time.day,
            time.week, time.hour, time.minute, time.second);
    }

    char time_str[30];
    if(0 <= get_time_local_string(time_str, sizeof(time_str)))
    {
        printf("local time string : %s\n", time_str);
    }

    if(0 <= get_time_utc_string(time_str, sizeof(time_str)))
    {
        printf("  utc time string : %s\n", time_str);
    }
    
    return 0;
}
*/
