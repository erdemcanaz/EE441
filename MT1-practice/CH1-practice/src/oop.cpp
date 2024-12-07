#include <iostream>
#include <string>

class Time
{
private:
    int mHour;
    int mMinute;

public:
    Time(int hour = 0, int minute = 0);
    Time(const Time &otherTime);
    void IncrementMinutes();
    void DecrementMinutes();
    void SetMinute(int minute);
    void SetHour(int hour);
    int GetMinute() const;
    int GetHour() const;
    void DisplayTime() const;
};

class TimeZone : public Time
{
private:
    int mTimeZone;

public:
    TimeZone(int hour = 0, int minute = 0, int timezone = 0);
    TimeZone(const TimeZone &otherTimezone);
    void setTimeZone(int timezone);
    int getTimeZone() const;
    void DisplayTimeZone() const;
};

int main()
{

    // Time myTime(0, 50);
    // myTime.DisplayTime();
    // myTime.IncrementMinutes();
    // myTime.DisplayTime();

    // Time newTime(myTime);
    // myTime.DecrementMinutes();
    // newTime.DisplayTime();
    // myTime.DisplayTime();

    int erdem_clock;
    std::cout << "Erdem hour:";
    std::cin >> erdem_clock;

    std::cout << "Erdem -> ";
    TimeZone erdem = TimeZone(erdem_clock, 0, 3);
    erdem.DisplayTimeZone();

    std::cout << "Tuna  -> ";
    TimeZone tuna(erdem);
    tuna.setTimeZone(0);
    tuna.DisplayTimeZone();

    std::cout << "Humo  -> ";
    TimeZone humo(erdem);
    humo.setTimeZone(1);
    humo.DisplayTimeZone();

    return 0;
}

/////////////////////////
Time::Time(int hour, int minute) : mHour(hour), mMinute(minute) {};
Time::Time(const Time &otherTime) : mHour(otherTime.mHour), mMinute(otherTime.mMinute) {};
void Time::IncrementMinutes()
{
    mMinute = mMinute + 1;
    if (mMinute == 60)
    {
        mMinute = 0;
        mHour = mHour + 1;
        if (mHour > 23)
        {
            mHour = 0;
        }
    }
};

void Time::DecrementMinutes()
{
    mMinute = mMinute - 1;
    if (mMinute == -1)
    {
        mMinute = 59;
        mHour = mHour - 1;
        if (mHour == -1)
        {
            mHour = 23;
        }
    }
};

void Time::DisplayTime() const
{
    if (mHour < 10 && mMinute < 10)
    {
        std::cout << "0" << mHour << ":0" << mMinute << std::endl;
    }
    else if (mHour < 10 && mMinute >= 10)
    {
        std::cout << "0" << mHour << ":" << mMinute << std::endl;
    }
    else if (mHour >= 10 && mMinute < 10)
    {
        std::cout << mHour << ":0" << mMinute << std::endl;
    }
    else
    {
        std::cout << mHour << ":" << mMinute << std::endl;
    }
};

void Time::SetMinute(int minute)
{
    if (minute < 0 || minute > 59)
    {
        throw std::logic_error("Minute must be between [0,59] int");
    };
    mMinute = minute;
}

void Time::SetHour(int hour)
{
    if (hour < 0 || hour > 23)
    {
        throw std::logic_error("Hour must be between [0,23] int");
    }
    mHour = hour;
};

int Time::GetMinute() const
{
    return mMinute;
};

int Time::GetHour() const
{
    return mHour;
};

/////////////////////////

TimeZone::TimeZone(int hour, int minute, int timezone) : Time(hour, minute), mTimeZone(timezone) {};
TimeZone::TimeZone(const TimeZone &otherTimezone) : Time(otherTimezone.GetHour(), otherTimezone.GetMinute()), mTimeZone(otherTimezone.getTimeZone()) {};
void TimeZone::setTimeZone(int timezone)
{
    if (timezone < -11 || timezone > 12)
    {
        throw std::logic_error("Timezone must be an integer number between -11 and 12 (both included)");
    }

    // Convert current time to GMT+0
    int gmt_hour = GetHour() - mTimeZone;
    int new_hour = gmt_hour + timezone;

    if (new_hour > 23)
    {
        new_hour = new_hour - 24;
    }
    else if (new_hour < 0)
    {
        new_hour = new_hour + 24;
    }
    SetHour(new_hour);
    mTimeZone = timezone;
};

int TimeZone::getTimeZone() const
{
    return mTimeZone;
};

void TimeZone::DisplayTimeZone() const
{
    if (mTimeZone < 0)
    {
        std::cout << "GMT" << mTimeZone << " ";
    }
    else
    {
        std::cout << "GMT+" << mTimeZone << " ";
    }

    DisplayTime();
};
