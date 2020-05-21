#include <ctime>

struct Date
{
    time_t secondsSinceEpoch;
    unsigned int year, month, day, hour, minute, second;

    Date() {
        secondsSinceEpoch = time(0);

        tm now;
        gmtime_s(&now, &secondsSinceEpoch);
        year = 1900 + now.tm_year;
        month = now.tm_mon + 1;
        day = now.tm_mday;
        hour = now.tm_hour;
        minute = now.tm_min;
        second = now.tm_sec;
    }

    Date(time_t& t) {
        secondsSinceEpoch = t;

        tm now;
        gmtime_s(&now, &secondsSinceEpoch);
        year = 1900 + now.tm_year;
        month = now.tm_mon + 1;
        day = now.tm_mday;
        hour = now.tm_hour;
        minute = now.tm_min;
        second = now.tm_sec;
    }
};