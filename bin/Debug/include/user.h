#ifndef USER_H
#define USER_H
#include <string>
#include <istream>
using namespace std;


class user
{
    string nume, prenume, cnp;
    int id;

    public:
    string getNume() const;
    string getPrenume() const;
    string getCnp() const;
    int getId() const;

    void setNume (const string &);
    void setPrenume (const string &);
    void setCnp (const string &);
    void setId (const int &);

    friend istream& operator >> (istream&, user &);
    friend ostream& operator << (ostream&, const user &);
};

#endif // USER_H
