#ifndef HOTEL_H
#define HOTEL_H
#include "rezervare.h"
#include <istream>
#include <string>
#include <vector>
using namespace std;

class hotel
{
    string city, name, description;
    double rating;
    int nrVoturi, id, sum, nrCamere;
    vector <rezervare> rezervariFacute;

    public:
    hotel();
    ~hotel();
    void setCity(const string &);
    void setName(const string &);
    void setDescription(const string &);
    void setRating (const double&);
    void setNrVoturi (const int&);
    void setId (const int&);
    void setSum (const int&);
    void setNrCamere(const int&);
    void pushRezervare();
    string getCity() const;
    string getName() const;
    string getDescription() const;
    double getRating() const;
    int getNrVoturi() const;
    int getId() const;
    int getSum() const;
    int getNrCamere() const;
    vector<rezervare> & getRezervariFacute();

    friend istream& operator >> (istream&, hotel&);
    friend ostream& operator << (ostream&, const hotel&);
};

#endif // HOTEL_H
