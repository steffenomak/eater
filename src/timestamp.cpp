#include "eater/timestamp.hpp"
#include <ctime>

namespace eater
{
time_stamp_t::time_stamp_t() : date(), time()
{}

time_stamp_t::time_stamp_t(const date_t &d, const time_t &t) : date(d), time(t)
{}

time_stamp_t::time_stamp_t(u32 d, u32 t) : date(d), time(t)
{}

time_stamp_t::time_stamp_t(u64 ts)
{
    set(ts);
}

void time_stamp_t::now()
{
    date.now();
    time.now();
}


void time_stamp_t::set(u64 ts)
{
    u32 t = 0x00000000FFFFFFFF & ts;
    u32 d = ts >> 32;
    date.set(d);
    time.set(t);
}

void time_stamp_t::set(const time_stamp_t &ts)
{
    date = ts.date;
    time = ts.time;
}

void time_stamp_t::set(u32 d, u32 t)
{
    date.set(d);
    time.set(t);
}


u64 time_stamp_t::get() const
{
    u64 ts = date.get();
    ts = ts << 32;
    ts += time.get();
    return ts;
}

str time_stamp_t::to_str() const
{
    return date.to_str() + " " + time.to_str();
}

time_stamp_t time_stamp_t::from_str(const str &s)
{
    size_t space_at;
    for (space_at = 0; space_at < s.length(); space_at++) {
        if (s[space_at] == ' ')
            break;
    }

    if (space_at == s.length() - 1) {
        throw std::invalid_argument("Malformed time stamp: " + s + ".");
    }

    str d = s.substr(0, space_at);
    str t = s.substr(space_at + 1, s.length() - space_at - 1);

    return time_stamp_t(date_t::from_str(d),
                        time_t::from_str(t));
}

bool time_stamp_t::operator<(const time_stamp_t &ts) const
{
    if (date < ts.date) {
        return true;
    } else if (date == ts.date && time < ts.time) {
        return true;
    }

    return false;
}

bool time_stamp_t::operator<=(const time_stamp_t &ts) const
{
    if (date <= ts.date) {
        return true;
    } else if (date == ts.date && time <= ts.time) {
        return true;
    }

    return false;
}

bool time_stamp_t::operator>(const time_stamp_t &ts) const
{
    if (date > ts.date) {
        return true;
    } else if (date == ts.date && time > ts.time) {
        return true;
    }

    return false;
}

bool time_stamp_t::operator>=(const time_stamp_t &ts) const
{
    if (date >= ts.date) {
        return true;
    } else if (date == ts.date && time >= ts.time) {
        return true;
    }

    return false;
}

bool time_stamp_t::operator==(const time_stamp_t &ts) const
{
    if (date == ts.date && time == ts.time) {
        return true;
    }

    return false;
}

bool time_stamp_t::operator!=(const time_stamp_t &ts) const
{
    if (date != ts.date || time != ts.time) {
        return true;
    }

    return false;
}
}

std::ostream &operator<<(std::ostream &os, const eater::time_stamp_t &ts)
{
    return os << ts.date << " " << ts.time;
}

std::istream &operator>>(std::istream &is, eater::time_stamp_t &ts)
{
    return is >> ts.date >> ts.time;
}
