#include <time.h>
#include <sys/time.h>
#include "../include/aqua/aqua.h"

EXPORT a_string a_GetISOTime(const struct timeval *time)
{
    struct tm btime;
    a_string_builder b;
    a_string s;
    a_string s2;

    gmtime_r(&time->tv_sec, &btime);
    
    b = a_sbldcreate();

    /* year */
    s = a_itoa(btime.tm_year + 1900);
    s2 = a_leftpad(s, 4, '0');
    a_sbldadds(b, s2);
    a_sdestroy(s);
    a_sdestroy(s2);

    a_sbldaddchar(b, '-');

    /* month */
    s = a_itoa(btime.tm_mon + 1);
    s2 = a_leftpad(s, 2, '0');
    a_sbldadds(b, s2);
    a_sdestroy(s);
    a_sdestroy(s2);

    a_sbldaddchar(b, '-');

    /* day */
    s = a_itoa(btime.tm_mday);
    s2 = a_leftpad(s, 2, '0');
    a_sbldadds(b, s2);
    a_sdestroy(s);
    a_sdestroy(s2);

    a_sbldaddchar(b, 'T');

    /* hour */
    s = a_itoa(btime.tm_hour);
    s2 = a_leftpad(s, 2, '0');
    a_sbldadds(b, s2);
    a_sdestroy(s);
    a_sdestroy(s2);

    a_sbldaddchar(b, ':');

    /* minute */
    s = a_itoa(btime.tm_min);
    s2 = a_leftpad(s, 2, '0');
    a_sbldadds(b, s2);
    a_sdestroy(s);
    a_sdestroy(s2);

    a_sbldaddchar(b, ':');

    /* second */
    s = a_itoa(btime.tm_sec);
    s2 = a_leftpad(s, 2, '0');
    a_sbldadds(b, s2);
    a_sdestroy(s);
    a_sdestroy(s2);

    a_sbldaddchar(b, '.');

    /* milliseconds */
    s = a_itoa(time->tv_usec / 1000);
    s2 = a_leftpad(s, 3, '0');
    a_sbldadds(b, s2);
    a_sdestroy(s);
    a_sdestroy(s2);

    a_sbldaddchar(b, 'Z');

    return a_sbld2s(b);
}