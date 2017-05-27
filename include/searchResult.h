#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H
#include "hotel.h"
#include "textbox.h"

class searchResult: public hotel, public textBox
{
    int posInHoteluri;
    int counter;

    public:
    searchResult();
    void setPosInHoteluri (const int &);
    void setCounter (const int &);
    int getPosInHoteluri () const;
    int getCounter() const;
    void checkHover();

    searchResult& operator = (const hotel &);
};

#endif // SEARCHRESULT_H
