#include "hotel.h"


hotel::hotel()
{

}

hotel::~hotel()
{

}

string hotel::getCity() const
{
    return city;
}

string hotel::getName() const
{
    return name;
}

string hotel::getDescription() const
{
    return description;
}

void hotel::setCity(const string &sir)
{
    city=sir;
}

void hotel::setName(const string &sir)
{
    name=sir;
}

void hotel::setDescription(const string &sir)
{
    description=sir;
}

istream& operator >> (istream &in, hotel &ob)
{
    getline(in, ob.city);
    getline(in, ob.name);
    getline(in, ob.description);
    in>>ob.rating; in>>ob.sum; in>>ob.nrVoturi;
    in>>ob.nrCamere;
    in>>ob.id;
    return in;
}

ostream& operator << (ostream &out, const hotel &ob)
{
    out<<ob.city<<"\n"<<ob.name<<"\n"<<ob.description<<"\n";
    out<<ob.rating<<" "<<ob.sum<<" "<<ob.nrVoturi<<"\n";
    out<<ob.nrCamere<<"\n";
    out<<ob.id;
    return out;
}

double hotel::getRating() const
{
    return rating;
}

int hotel::getNrVoturi() const
{
    return nrVoturi;
}

int hotel::getId() const
{
    return id;
}

int hotel::getSum() const
{
    return sum;
}

int hotel::getNrCamere() const
{
    return nrCamere;
}

vector<rezervare> & hotel::getRezervariFacute()
{
    return rezervariFacute;
}

void hotel::setRating (const double &val)
{
    rating=val;
}

void hotel::setNrVoturi (const int &val)
{
    nrVoturi=val;
}

void hotel::setId (const int &val)
{
    id=val;
}

void hotel::setSum (const int &val)
{
    sum=val;
}

void hotel::setNrCamere (const int &val)
{
    nrCamere=val;
}

