#include "rezervare.h"

void rezervare::setCheckIn (const string &sir)
{
    checkIn=sir;
}

void rezervare::setCheckOut (const string &sir)
{
    checkOut=sir;
}

void rezervare::setHotelId (const int &val)
{
    hotelId=val;
}

string rezervare::getCheckIn () const
{
    return checkIn;
}

string rezervare::getCheckOut () const
{
    return checkOut;
}

int rezervare::getHotelId () const
{
    return hotelId;
}

istream& operator >> (istream &in, rezervare &ob)
{
    getline(in, ob.checkIn);
    getline(in, ob.checkOut);
    in>>ob.hotelId;
    in.get();//newline
    in>>ob.persoana;
    return in;
}

ostream& operator << (ostream &out, const rezervare &ob)
{
    out<<ob.checkIn<<"\n"<<ob.checkOut<<"\n"<<ob.hotelId<<"\n";
    out<<ob.persoana;
    return out;
}

void rezervare::setUser (const user &ob)
{
    persoana.setNume (ob.getNume());
    persoana.setPrenume (ob.getPrenume());
    persoana.setCnp (ob.getCnp());
    persoana.setId (ob.getId());
}

user rezervare::getUser () const
{
    return persoana;
}
