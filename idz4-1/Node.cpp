#include "Node.hpp"


bool TimeKey::operator < (const TimeKey& time) const {
    if (h < time.h) return true;
    else if (h == time.h) {
        if (m < time.m) return true;
        else if (m == time.m) {
            if (s < time.s) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}
bool TimeKey::operator > (const TimeKey& time) const {
    if (h > time.h) return true;
    else if (h == time.h) {
        if (m > time.m) return true;
        else if (m == time.m) {
            if (s > time.s) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}
bool TimeKey::operator == (const TimeKey& time) const {
    if (h == time.h && m == time.m && s == time.s) return true;
    else return false;
}

bool TimeKey::operator != (const TimeKey& time) const {
    if (h != time.h || m != time.m || s != time.s) return true;
    else return false;
}