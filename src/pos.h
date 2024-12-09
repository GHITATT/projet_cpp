#ifndef __POS_H__
#define __POS_H__

#include <iostream>
#include <list>

using namespace std;

class Pos
{
public:
    Pos();
    Pos(long double lat, long double lon, long double alt);  
    ~Pos();

    long double _lat;
    long double _lon;
    long double _alt;

    void transform_glob_loc(long double lat, long double lon, long double alt);

    long double _x;
    long double _y;
    long double _z;

    friend std::ostream& operator<<(std::ostream& stream, const Pos& p);
    friend std::istream& operator>>(std::istream& stream, Pos& p);

};

#endif // __POS_H__
