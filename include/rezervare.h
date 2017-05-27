#ifndef REZERVARE_H
#define REZERVARE_H
#include "user.h"
#include <string>
#include <istream>
using namespace std;

class rezervare
{
    string checkIn, checkOut;
    int hotelId;
    user persoana;

    public:
    void setCheckIn (const string &);
    void setCheckOut (const string &);
    void setHotelId (const int &);
    void setUser (const user &);
    string getCheckIn () const;
    string getCheckOut () const;
    int getHotelId () const;
    user getUser () const;

    friend istream& operator >> (istream&, rezervare&);
    friend ostream& operator << (ostream&, const rezervare&);
};

#endif // REZERVARE_H
