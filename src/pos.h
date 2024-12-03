#ifndef __POS_H__
#define __POS_H__

#include <iostream>
#include <list>

using namespace std;

class Pos
{
public:
    Pos();
    Pos(double lat, double lon, double alt);  
    ~Pos();

    double _lat;
    double _lon;
    double _alt;

    void transform_glob_loc(double lat, double lon, double alt);

    double _x;
    double _y;
    double _z;
/*
    list<Edge*> _edges;

    void link_to(Pos* p);
*/


    friend std::ostream& operator<<(std::ostream& stream, const Pos& p);
    friend std::istream& operator>>(std::istream& stream, Pos& p);
  

};


#endif // __POS_H__