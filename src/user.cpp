#include "user.h"

string user::getNume() const
{
    return nume;
}

string user::getPrenume() const
{
    return prenume;
}

string user::getCnp() const
{
    return cnp;
}

int user::getId() const
{
    return id;
}

void user::setNume (const string &s)
{
    nume=s;
}

void user::setPrenume (const string &s)
{
    prenume=s;
}

void user::setCnp (const string &s)
{
    cnp=s;
}

void user::setId (const int &val)
{
    id=val;
}

istream& operator >> (istream &in, user &ob)
{
    getline(in, ob.nume);
    getline(in, ob.prenume);
    getline(in, ob.cnp);
    in>>ob.id;
    return in;
}

ostream& operator << (ostream &out, const user &ob)
{
    out<<ob.nume<<" "<<ob.prenume<<"\n";
    out<<ob.cnp<<"\n";
    out<<ob.id;
    return out;
}

