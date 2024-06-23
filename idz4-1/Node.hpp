#ifndef NODE
#define NODE
#include <iostream>
#include <vector>
#include <string>

struct TimeKey {
    short int h;
    short int m;
    short int s;

    bool operator < (const TimeKey& time) const;
    bool operator > (const TimeKey& time) const;
    bool operator == (const TimeKey& time) const;
    bool operator != (const TimeKey& time) const;

};

struct Car
{
    std::string brand = "";
    std::string model = "";
};
struct Node {
    std::string fio = "";
    TimeKey time;
    Car car;
    int ch;
};

















#endif