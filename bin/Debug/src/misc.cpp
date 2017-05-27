#include "../include/misc.h"
#include <algorithm>

//<-------------Variabile folosite doar in misc.cpp--------------->

//<----------Generale------->

user utilizator;

imagine logo, goBack;
sf::Vector2i mousePosition;
int currentScreen;
bool unreadFile, dataChange, showRater, unreadRatedHotels, ratedChange, rezervariChange;
bool unreadRezervari;

vector <hotel> hoteluri;
vector <searchResult> results;
vector <int> ratedHotels;

struct pack
{
    unsigned int pos;
    unsigned int relevanta;
};
vector <struct pack> matches;
bool criteriuSortare (const struct pack &, const struct pack &);

//<------------Start Screen------------>
imagine homeCauta, homeAdauga;

//<------------Search Screen------------>
imagine searchButton;
textBox cityBox, nameBox;

//<--------pentru drawHotelPage()------->
imagine rezervaImagine, evalueaza, finalizeazaRezervare, anuleazaRezervare;
textBox header, detalii;
textBox judetHotel, ratingHotel, rater;
int currentPosInHoteluri;
//pentru rezervare
textBox continutRezervare, dataCheckIn, dataCheckOut;
sf::RectangleShape overlayRezervare;
bool rezervareIsActive, areRezervare;

//<---------pentru drawAddScreen()------->
imagine finalizeazaAddHotel;
textBox scrieNume, scrieJudet, scrieDetalii, scrieCamere;



//<------variabile externe------>
sf::RenderWindow window;

//<------SCROLL STUFF--------->
sf::View view;
int CONTENT_WIDTH, CONTENT_HEIGHT;
float dy;

//<--------------Functii folosite doar in main.cpp------------->

void drawStartScreen();
void drawSearchScreen();
void drawHotelScreen();
void drawAddScreen();

void disableAllActives();
void modifyString(const sf::Event&, textBox&);
void beginSearch();
string lowerCase (const string &);
void citire();
void buildSearchResults();
void displaySearchResults();
void setUpHotelPage(const unsigned int&);
void rateHotel();

void citireRatedHotels();
void setUpRezervareProcess();
void makeRezervare();
bool verificaFormat();
bool existaCamera();
int dateToInt (const string&, const string&);
long double transformDateToDouble (const int &, const int &, const int &);
int getDaysInMonth (const int &, const int &);
void citireRezervari();
void resetViewAndPos();
void setUpAddScreen();
void addHotel();
bool checkHotelInformation();

void checkUserData()
{
    int val=0;
    string aux;
    ifstream fin ("userData.in");
    fin>>val;
    if (val==1)//acest utilizator si-a introdus datele in trecut
    {
        fin>>utilizator;
        fin.close();
        return;
    }
    fin.close();

    //altfel, citesc detalii

    cout<<"Inainte de a putea folosi aplicatia, trebuie sa introduceti datele pentru eventualele rezervari realizate:\n\n";

    cout<<"Nume: ";
    cin>>aux;
    utilizator.setNume(aux);
    cout<<"\n\n";

    cout<<"Prenume: ";
    cin>>aux;
    utilizator.setPrenume(aux);
    cout<<"\n\n";

    while (1)
    {
        cout<<"CNP: ";
        cin>>aux;
        cout<<"\n";
        if (aux.size()==10 && (aux[0]=='1' || aux[1]=='2'))
            break;
        cout<<"CNP gresit!!\n";
    }

    utilizator.setCnp(aux);

    utilizator.setId (1);

    //acum scriu in fisier

    ofstream fout ("userData.in");
    fout<<"1\n";
    fout<<utilizator;
    fout.close();
    return;
}

void startApp()
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HPRO", sf::Style::Titlebar | sf::Style::Close);
    currentScreen=1;
    unreadFile=true; dataChange=false; showRater=false; unreadRatedHotels=true; ratedChange=false; rezervareIsActive=false; rezervariChange=false;
    unreadRezervari=true;

    //<--------DIMENSIUNI--------->
    logo.getSprite().setScale(.7f, .7f);
    homeCauta.getSprite().setScale(.5f, .5f);
    homeAdauga.getSprite().setScale(.5f, .5f);
    goBack.getSprite().setScale(.10f, .10f);
    searchButton.getSprite().setScale(.09f, .09f);
    evalueaza.getSprite().setScale(.35f, .35f);
    rezervaImagine.getSprite().setScale(.35f, .35f);
    finalizeazaRezervare.getSprite().setScale(.35f, .35f);
    finalizeazaAddHotel.getSprite().setScale(.35f, .35f);
    anuleazaRezervare.getSprite().setScale(.35f, .35f);

    //<--------START SCREEN--------->
    logo.loadImage("images/logo.png");
    homeCauta.loadImage ("images/homeCauta.png");
    homeAdauga.loadImage ("images/adauga.png");
    logo.setPosition(WINDOW_WIDTH/2-logo.getWidth()/2, WINDOW_HEIGHT/100);
    homeCauta.setPosition (WINDOW_WIDTH/2-homeCauta.getWidth()/2, WINDOW_HEIGHT/3);
    homeAdauga.setPosition (homeCauta.getX(), homeCauta.getY()+homeCauta.getHeight()+DISTANCE*3);
    goBack.setPosition(DISTANCE, DISTANCE);

    //<--------SEARCH SCREEN--------->
    goBack.loadImage("images/goBack.png");
    searchButton.loadImage("images/searchButton.png");
    cityBox.setSize(WINDOW_WIDTH/7, WINDOW_HEIGHT/20);
    cityBox.setPosition(WINDOW_WIDTH/10, WINDOW_HEIGHT/5);
    nameBox.setSize(WINDOW_WIDTH/1.5, WINDOW_HEIGHT/20);
    nameBox.setPosition(cityBox.getX()+cityBox.getWidth()+DISTANCE, WINDOW_HEIGHT/5);
    searchButton.setPosition(nameBox.getX()+nameBox.getWidth()+DISTANCE, WINDOW_HEIGHT/5-DISTANCE/1.5);

    //<--------HOTEL PAGE SCREEN--------->
    rezervaImagine.loadImage("images/rezerva.png");
    evalueaza.loadImage("images/evalueaza.png");
    finalizeazaRezervare.loadImage ("images/finalizeazaRezervare.png");
    anuleazaRezervare.loadImage ("images/anuleaza.png");

    finalizeazaAddHotel.loadImage ("images/finalizeazaRezervare.png");

    //view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    view.setCenter(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);
    CONTENT_WIDTH=WINDOW_WIDTH;
    CONTENT_HEIGHT=WINDOW_HEIGHT;

    setUpAddScreen();
}

void drawScreen()
{
    //background alb
    sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(CONTENT_WIDTH, CONTENT_HEIGHT));
    bg.setFillColor(sf::Color::White);

    window.clear();
    window.draw(bg);
    if (currentScreen==1)
        drawStartScreen();
        else
        if (currentScreen==2)
            drawSearchScreen();
            else
            if (currentScreen==3)
                drawHotelScreen();
                else
                if (currentScreen==10)//incepand cu 10, am procesele pentru adaugare hotel
                    drawAddScreen();
}

void drawStartScreen()
{
    window.draw(logo.getSprite());
    window.draw(homeCauta.getSprite());
    window.draw(homeAdauga.getSprite());
    window.display();
}

void drawSearchScreen()
{
    window.draw(logo.getSprite());
    window.draw(goBack.getSprite());
    window.draw(searchButton.getSprite());
    window.draw(cityBox.getShape()); window.draw(cityBox.getText());
    window.draw(nameBox.getShape()); window.draw(nameBox.getText());

    if (matches.size())
        displaySearchResults();
    window.display();
}

void drawHotelScreen()
{
    window.draw(logo.getSprite());
    window.draw(goBack.getSprite());
    window.draw(header.getShape()); window.draw(header.getText());
    window.draw(judetHotel.getText());
    window.draw(ratingHotel.getText());
    window.draw(detalii.getShape()); window.draw(detalii.getText());
    window.draw(evalueaza.getSprite());

    if (!areRezervare)
        window.draw(rezervaImagine.getSprite());
        else
        window.draw(anuleazaRezervare.getSprite());
    if (showRater)
    {
        window.draw(rater.getShape()); window.draw(rater.getText());
    }

    if (rezervareIsActive)//draw additional stuff
    {
        window.draw (overlayRezervare);
        window.draw (continutRezervare.getShape()); window.draw(continutRezervare.getText());
        window.draw (dataCheckIn.getShape()); window.draw(dataCheckIn.getText());
        window.draw (dataCheckOut.getShape()); window.draw(dataCheckOut.getText());
        window.draw (finalizeazaRezervare.getSprite());
    }

    window.display();
}

void drawAddScreen()
{
    window.draw (logo.getSprite());
    window.draw (goBack.getSprite());
    window.draw (scrieNume.getShape()); window.draw (scrieNume.getText());
    window.draw (scrieJudet.getShape()); window.draw (scrieJudet.getText());
    window.draw (scrieDetalii.getShape()); window.draw (scrieDetalii.getText());
    window.draw (scrieCamere.getShape()); window.draw (scrieCamere.getText());
    window.draw (finalizeazaAddHotel.getSprite());

    window.display();
}

void checkMousePress(const sf::Event &event)
{
    unsigned int i;
    disableAllActives();
    if (event.mouseButton.button != sf::Mouse::Left)
        return;

    mousePosition=sf::Mouse::getPosition(window);
    switch (currentScreen)
    {
        case 1://start screen
        if (mouseIsInside (mousePosition, homeCauta))
        {
            currentScreen=2;
            resetViewAndPos();
        }

        if (mouseIsInside (mousePosition, homeAdauga))
        {
            currentScreen=10;
            resetViewAndPos();
        }

        break;

        case 2://search screen
        if (mouseIsInside (mousePosition, goBack))
        {
            --currentScreen;
            resetViewAndPos();
        }
            else
        if (mouseIsInside (mousePosition, cityBox))
        {
            cityBox.setStatus(true);
            cityBox.setString("");
        }
            else
        if (mouseIsInside (mousePosition, nameBox))
        {
            nameBox.setStatus(true);
            nameBox.setString("");
        }
            else
        if (mouseIsInside (mousePosition, searchButton))
            beginSearch();
            else
        for (i=0; i<results.size(); ++i)
            if (mouseIsInside(mousePosition, results[i]))
                break;
        if (i<results.size())
        {
            ++currentScreen;
            resetViewAndPos();
            currentPosInHoteluri=results[i].getPosInHoteluri();
            setUpHotelPage(i);
        }
        break;

        case 3://hotel screen
        if (mouseIsInside(mousePosition, continutRezervare) && rezervareIsActive)
        {
            rezervareIsActive=true;
            if (mouseIsInside(mousePosition, dataCheckIn))
            {
                dataCheckIn.setStatus(true);
                dataCheckIn.setString("");
            }

            if (mouseIsInside(mousePosition, dataCheckOut))
            {
                dataCheckOut.setStatus(true);
                dataCheckOut.setString("");
            }

            if (mouseIsInside(mousePosition, finalizeazaRezervare))
                makeRezervare();

            break;
        }
            else
            rezervareIsActive=false;

        if (mouseIsInside (mousePosition, goBack))
        {
            --currentScreen;
            resetViewAndPos();
        }
        if (mouseIsInside (mousePosition, rater))
        {
            rater.setStatus(true);
            rater.setString("");
        }
        if (mouseIsInside (mousePosition, evalueaza))
            showRater=!showRater;

        if (mouseIsInside (mousePosition, rezervaImagine) && !areRezervare)
        {
            if (!rezervareIsActive)
            {
                rezervareIsActive=true;
                setUpRezervareProcess();
            }
        }

        if (mouseIsInside (mousePosition, anuleazaRezervare) && areRezervare)
        {
            hoteluri[currentPosInHoteluri].getRezervariFacute().pop_back();
            areRezervare=false;
            rezervariChange=true;
        }
        break;

        case 10://add screen
        if (mouseIsInside (mousePosition, goBack))
        {
            currentScreen=1;
            resetViewAndPos();
        }

         if (mouseIsInside (mousePosition, scrieNume))
        {
            scrieNume.setStatus(true);
            if (scrieNume.getString().compare("Insereaza numele hotelului")==0)
                scrieNume.setString("");
        }

        if (mouseIsInside (mousePosition, scrieJudet))
        {
            scrieJudet.setStatus(true);
            if (scrieJudet.getString().compare("Insereaza judetul hotelului")==0)
                scrieJudet.setString("");
        }

        if (mouseIsInside (mousePosition, scrieDetalii))
        {
            scrieDetalii.setStatus(true);
            if (scrieDetalii.getString().compare("Insereaza detalii despre hotel")==0)
                scrieDetalii.setString("");
        }

        if (mouseIsInside (mousePosition, scrieCamere))
        {
            scrieCamere.setStatus(true);
            if (scrieCamere.getString().compare("Insereaza numarul de camere")==0)
                scrieCamere.setString("");
        }

        if (mouseIsInside (mousePosition, finalizeazaAddHotel))
        {
            addHotel();
        }

        break;
    }
}

void checkKeyPress(const sf::Event &event)
{
    if (currentScreen==2)
    {
        if (cityBox.getStatus())
            modifyString (event, cityBox);
            else
            if (nameBox.getStatus())
                modifyString (event, nameBox);
    }

    if (currentScreen==3)
    {
        if (rater.getStatus())
            modifyString (event, rater);
        if (dataCheckIn.getStatus())
            modifyString (event, dataCheckIn);
        if (dataCheckOut.getStatus())
            modifyString (event, dataCheckOut);
    }

    if (currentScreen==10)
    {
        if (scrieNume.getStatus())
            modifyString (event, scrieNume);
        if (scrieJudet.getStatus())
            modifyString (event, scrieJudet);
        if (scrieDetalii.getStatus())
            modifyString (event, scrieDetalii);
        if (scrieCamere.getStatus())
            modifyString (event, scrieCamere);
    }
}

void disableAllActives()
{
    cityBox.setStatus(false);
    nameBox.setStatus(false);
    if (!cityBox.getString().size())
        cityBox.setString ("Oras");
    if (!nameBox.getString().size())
        nameBox.setString ("Nume hotel");

    rater.setStatus(false);
    rater.setString("Acorda acestui hotel o nota intre 1 si 10 si apasa tasta 'Enter':");
    dataCheckIn.setStatus(false);
    dataCheckOut.setStatus(false);
    if (!dataCheckIn.getString().size())
        dataCheckIn.setString("Data check-in:");
    if (!dataCheckOut.getString().size())
        dataCheckOut.setString("Data check-out:");
    dataCheckIn.setSize(cityBox.getWidth()*2, cityBox.getHeight());
    dataCheckOut.setSize(cityBox.getWidth()*2, cityBox.getHeight());

    scrieNume.setStatus(false);
    scrieJudet.setStatus(false);
    scrieDetalii.setStatus(false);
    scrieCamere.setStatus(false);

    if (!scrieNume.getString().size())
        scrieNume.setString("Insereaza numele hotelului");

    if (!scrieJudet.getString().size())
        scrieJudet.setString("Insereaza judetul hotelului");

    if (!scrieDetalii.getString().size())
        scrieDetalii.setString("Insereaza detalii despre hotel");

    if (!scrieCamere.getString().size())
        scrieCamere.setString("Insereaza numarul de camere");
}

template <typename T>
bool mouseIsInside (const sf::Vector2i &mousePosition, const T &buton)
{
    if (buton.getX()<=mousePosition.x && mousePosition.x<=buton.getX()+buton.getWidth())
        if (buton.getY()<=mousePosition.y+dy && mousePosition.y+dy<=buton.getY()+buton.getHeight())
            return true;

    return false;
}

void modifyString (const sf::Event &event, textBox &ob)
{
    if (event.text.unicode>=32 && event.text.unicode<=126)
    {
        ob.setString(ob.getString()+(char)event.text.unicode);
    }
        else
        if (event.text.unicode==8 && ob.getString().size()>0)//sterge
            ob.sterge();
            else
            if (event.text.unicode==13 || event.text.unicode==10)//a apasat enter
            {
                if (currentScreen==2)
                    beginSearch();
                    else
                    if (currentScreen==3)
                        rateHotel();
            }
}

void beginSearch()
{
    unsigned int minusUnu=-1;

    if (!cityBox.getString().compare("Oras"))
        cityBox.setString("");

    if (!nameBox.getString().compare("Nume hotel"))
        nameBox.setString("");

    citire();

    //compar ce a cautat utilizatorul cu hotelurile pe care le am
    unsigned int i;
    char *auxCity, *auxName, *p;
    char *copieCity, *copieName;
    struct pack temp;

    auxCity=new char [cityBox.getString().size()+1];
    auxName=new char [nameBox.getString().size()+1];
    copieCity=new char [cityBox.getString().size()+1];
    copieName=new char [nameBox.getString().size()+1];

    lowerCase(cityBox.getString()).copy(copieCity, cityBox.getString().size());
    copieCity[cityBox.getString().size()]=0;

    lowerCase(nameBox.getString()).copy(copieName, nameBox.getString().size());
    copieName[nameBox.getString().size()]=0;

    matches.clear();
    for (i=0; i<hoteluri.size(); ++i)
    {
        strcpy(auxCity, copieCity);
        strcpy(auxName, copieName);

        temp.pos=i;
        temp.relevanta=0;

        p=strtok(auxCity, " ");
        while (p)
        {
            if (lowerCase(hoteluri[i].getCity()).find(p)!=minusUnu)//am gasit un match
            {
                temp.relevanta+=strlen(p);
            }
            p=strtok(NULL, " ");
        }

        p=strtok(auxName, " ");
        while (p)
        {
            if (lowerCase(hoteluri[i].getName()).find(p)!=minusUnu)//am gasit un match
            {
                temp.relevanta+=strlen(p);
            }
            p=strtok(NULL, " ");
        }

        if (temp.relevanta)
            matches.push_back(temp);
    }
    if (matches.size())//am gasit rezultate
        sort(matches.begin(), matches.end(), criteriuSortare);
    buildSearchResults();
}

string lowerCase (const string &sir)
{
    unsigned int i;
    string aux=sir;
    if (sir.size()==0)
        return aux;

    for (i=0; i<sir.size(); ++i)
        if ('A'<=sir[i] && sir[i]<='Z')
            aux[i]=sir[i]+('a'-'A');
            else
            aux[i]=sir[i];
    return aux;
}

bool criteriuSortare (const struct pack &a, const struct pack &b)
{
    return a.relevanta>b.relevanta;
}

void citire()
{
    if (!unreadFile) return;

    unreadFile=false;
    int i, n=0;
    hotel ob;
    ifstream fin ("data.in");
    fin>>n; fin.get();
    for (i=1; i<=n; ++i)
    {
        fin>>ob;
        hoteluri.push_back(ob);
        fin.get();//newline
    }
    fin.close();
    return;
}

void buildSearchResults()
{
    results.clear();

    searchResult temp;
    unsigned int i;
    int firstY;
    stringstream aux;

    if (matches.size()>0)
    {
        temp=hoteluri[matches[0].pos];
        temp.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);//fictiv

        aux.str("");
        aux<<((int)(temp.getRating()*100))/100.0;//pun rating-ul intr-un sir
        temp.setString(temp.getName()+"\nJudet: "+temp.getCity()+"\nRating: "+aux.str()+"/10");
        temp.setCounter(1);

        firstY=max(cityBox.getY()+cityBox.getHeight(), nameBox.getY()+nameBox.getHeight());
        firstY+=DISTANCE*3;

        temp.setSize(cityBox.getWidth()+nameBox.getWidth()+DISTANCE, temp.getText().getGlobalBounds().height+DISTANCE);
        temp.setPosition(WINDOW_WIDTH/10, firstY);

        temp.setPosInHoteluri(matches[0].pos);
        results.push_back(temp);
    }

    for (i=1; i<matches.size(); ++i)
    {
        temp=hoteluri[matches[i].pos];
        temp.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);//fictiv

        aux.str("");
        aux<<((int)(temp.getRating()*100))/100.0;//pun rating-ul intr-un sir
        temp.setString(temp.getName()+"\nJudet: "+temp.getCity()+"\nRating: "+aux.str()+"/10");
        temp.setCounter(i+1);

        temp.setSize(cityBox.getWidth()+nameBox.getWidth()+DISTANCE, temp.getText().getGlobalBounds().height+DISTANCE);
        temp.setPosition(WINDOW_WIDTH/10, results[results.size()-1].getY()+results[results.size()-1].getHeight()+DISTANCE/2);

        temp.setPosInHoteluri(matches[i].pos);
        results.push_back(temp);
    }

    if (results.size())
        CONTENT_HEIGHT=max (WINDOW_HEIGHT*2, 2*(results[results.size()-1].getY()+results[results.size()-1].getHeight()));
}

void displaySearchResults()
{
    unsigned int i;
    for (i=0; i<results.size(); ++i)
    {
        results[i].checkHover();
        window.draw(results[i].getShape()); window.draw(results[i].getText());
    }
    return;
}

void setUpHotelPage (const unsigned int &i)
{
    citireRezervari();

    stringstream aux;
    searchResult currentHotel=results[i];
    unsigned int itr;

    header.setSize(cityBox.getWidth()+nameBox.getWidth()+DISTANCE, nameBox.getHeight());//inaltimea urmeaza sa fie schimbata
    header.setPosition(cityBox.getX(), cityBox.getY());
    header.setString(currentHotel.getName());
    header.getText().setPosition((header.getX()+header.getWidth())/2-header.getText().getGlobalBounds().width/2+WINDOW_WIDTH/20, header.getY());
    header.getShape().setFillColor(sf::Color(224, 224, 224));

    judetHotel.getText().setString("Judet: "+currentHotel.getCity());
    judetHotel.getText().setCharacterSize(CHARSIZE);
    judetHotel.getText().setColor(sf::Color::Black);
    judetHotel.getText().setPosition(cityBox.getX()+DISTANCE/2, cityBox.getY()+header.getText().getGlobalBounds().height+DISTANCE);

    aux<<((int)(currentHotel.getRating()*100))/100.0;//pun rating-ul intr-un sir
    ratingHotel.getText().setString("Rating: "+aux.str()+"/10");
    ratingHotel.getText().setCharacterSize(CHARSIZE);
    ratingHotel.getText().setColor(sf::Color::Black);
    ratingHotel.getText().setPosition(cityBox.getX()+header.getWidth()-ratingHotel.getText().getGlobalBounds().width-DISTANCE/2, cityBox.getY()+header.getText().getGlobalBounds().height+DISTANCE);

    if (judetHotel.getText().getGlobalBounds().height>ratingHotel.getText().getGlobalBounds().height)
        header.setSize(header.getWidth(), header.getHeight()+judetHotel.getText().getGlobalBounds().height+DISTANCE);
        else
        header.setSize(header.getWidth(), header.getHeight()+ratingHotel.getText().getGlobalBounds().height+DISTANCE);

    detalii.setPosition(header.getX(), header.getY()+header.getHeight()+DISTANCE*2);
    detalii.getText().setPosition(header.getX()+DISTANCE/2, detalii.getY());
    detalii.setSize(header.getWidth(), nameBox.getHeight());
    detalii.getShape().setFillColor(sf::Color(255, 255, 204));
    //setez string-ul
    detalii.setString("     ");//alineat
    for (itr=0; itr<currentHotel.getDescription().size(); ++itr)
        detalii.setString(detalii.getString()+currentHotel.getDescription()[itr]);

    //butoanele pentru rezervare si evaluare hotel
    evalueaza.setPosition(detalii.getX()-2, detalii.getY()+detalii.getHeight()+DISTANCE*3);
    rezervaImagine.setPosition(detalii.getX()+detalii.getWidth()-rezervaImagine.getWidth(), detalii.getY()+detalii.getHeight()+DISTANCE*3);
    anuleazaRezervare.setPosition(detalii.getX()+detalii.getWidth()-anuleazaRezervare.getWidth(), detalii.getY()+detalii.getHeight()+DISTANCE*3);

    //rater pentru evaluare
    rater.setSize(9999, 9999);
    rater.getText().setCharacterSize(currentHotel.getText().getCharacterSize());
    rater.setString("Acorda acestui hotel o nota intre 1 si 10 si apasa tasta 'Enter':");
    rater.setSize(rater.getText().getGlobalBounds().width+DISTANCE, nameBox.getHeight());
    rater.setPosition(WINDOW_WIDTH/2-rater.getWidth()/2, evalueaza.getY()+evalueaza.getHeight()+DISTANCE/2);
    rater.getText().setPosition(rater.getX()+DISTANCE/2, rater.getY());

    //verific daca hotelul asta are rezervare
    if (hoteluri[currentPosInHoteluri].getRezervariFacute().size())
        areRezervare=true;
        else
        areRezervare=false;

    //header.getShape().setOutlineColor(sf::Color::Red);
    //detalii.getShape().setOutlineColor(sf::Color::Red);
}

void rateHotel()
{
    int nota; int poz;
    unsigned int i;
    stringstream aux;
    searchResult currentHotel;
    currentHotel=hoteluri[currentPosInHoteluri];

    citireRatedHotels();
    for (i=0; i<ratedHotels.size(); ++i)
        if (ratedHotels[i]==currentHotel.getId())
    {
        rater.setString("Ai acordat deja o nota acestui hotel!");
        rater.setSize(rater.getWidth(), nameBox.getHeight());
        return;
    }

    string sir=rater.getString();
    if (sir.size()>2)
    {
        rater.setString("Nota introdusa e prea lunga!");
        rater.setSize(rater.getWidth(), nameBox.getHeight());
        return;
    }

    for (i=0; i<sir.size(); ++i)
        if (!('0'<=sir[i] && sir[i]<='9'))
    {
        rater.setString("Nota trebuie sa contina doar cifre!");
        rater.setSize(rater.getWidth(), nameBox.getHeight());
        return;
    }

    if (sir[0]=='0')
    {
        rater.setString("Nota nu poate incepe cu cifra 0!");
        rater.setSize(rater.getWidth(), nameBox.getHeight());
        return;
    }
    if (sir.size()==2 && (sir[0]!='1' || sir[1]!='0'))
    {
        rater.setString("Nota maxima este 10!");
        rater.setSize(rater.getWidth(), nameBox.getHeight());
        return;
    }

    if (sir.size()==2)
        nota=10;
        else
        nota=sir[0]-'0';

    currentHotel.setPosInHoteluri(currentPosInHoteluri);
    currentHotel.setSum(currentHotel.getSum()+nota);
    currentHotel.setNrVoturi(currentHotel.getNrVoturi()+1);
    currentHotel.setRating((double)currentHotel.getSum()/currentHotel.getNrVoturi());

    poz=currentHotel.getPosInHoteluri();
    hoteluri[poz].setSum(currentHotel.getSum());
    hoteluri[poz].setNrVoturi(currentHotel.getNrVoturi());
    hoteluri[poz].setRating(currentHotel.getRating());
    //schimb si sirul
    aux<<((int)(currentHotel.getRating()*100))/100.0;//pun rating-ul intr-un sir
    ratingHotel.getText().setString("Rating: "+aux.str()+"/10");
    ratingHotel.getText().setPosition(cityBox.getX()+header.getWidth()-ratingHotel.getText().getGlobalBounds().width-DISTANCE/2, cityBox.getY()+header.getText().getGlobalBounds().height+DISTANCE);

    ratedChange=dataChange=true;
    ratedHotels.push_back(currentHotel.getId());
    buildSearchResults();
}

void checkDataChange()
{
    if (dataChange)
    {
        ofstream fout ("data.in");
        unsigned int i;
        fout<<hoteluri.size()<<"\n";
        for (i=0; i<hoteluri.size(); ++i)
            fout<<hoteluri[i]<<"\n";
        fout.close();
    }

    if (ratedChange)
    {
        ofstream fout ("rated.in");
        unsigned int i;
        fout<<ratedHotels.size()<<"\n";
        for (i=0; i<ratedHotels.size(); ++i)
            fout<<ratedHotels[i]<<"\n";
        fout.close();
    }

    if (rezervariChange)
    {
        ofstream fout ("rezervari.in");
        unsigned int i, j, n=0;

        //aflu numarul total de rezervari
        for (i=0; i<hoteluri.size(); ++i)
            n+=hoteluri[i].getRezervariFacute().size();
        fout<<n<<"\n";

        for (i=0; i<hoteluri.size(); ++i)
            for (j=0; j<hoteluri[i].getRezervariFacute().size(); ++j)
                fout<<hoteluri[i].getRezervariFacute()[j]<<"\n";

        fout.close();
    }
}

void citireRatedHotels()
{
    if (!unreadRatedHotels) return;
    unreadRatedHotels=false;

    unsigned int i, n=0, idHotel;
    ifstream fin ("rated.in");
    fin>>n;
    for (i=1; i<=n; ++i)
    {
        fin>>idHotel;
        ratedHotels.push_back(idHotel);
    }
}

void setUpRezervareProcess()
{
    overlayRezervare.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlayRezervare.setFillColor(sf::Color(255, 255, 255, 200));

    continutRezervare.setSize(WINDOW_WIDTH*2/3, WINDOW_HEIGHT*2/3);
    continutRezervare.setPosition((WINDOW_WIDTH-WINDOW_WIDTH*2/3)/2, cityBox.getY());
    continutRezervare.setString("Format data: ZZ-LL-AAAA");
    continutRezervare.getText().setPosition((continutRezervare.getX()+continutRezervare.getWidth())/2-continutRezervare.getText().getGlobalBounds().width/2+WINDOW_WIDTH/20, continutRezervare.getY());
    continutRezervare.getShape().setFillColor(sf::Color(224, 224, 224));

    dataCheckIn.setSize(cityBox.getWidth()*2, cityBox.getHeight());
    dataCheckIn.setString("Data check-in:");
    dataCheckIn.getText().setCharacterSize(results[0].getText().getCharacterSize());
    dataCheckIn.setPosition(WINDOW_WIDTH/2-dataCheckIn.getWidth()/2, continutRezervare.getY()+continutRezervare.getText().getGlobalBounds().height*5);
    dataCheckIn.getText().setPosition(dataCheckIn.getX()+DISTANCE/2, dataCheckIn.getY());

    dataCheckOut.setSize(cityBox.getWidth()*2, cityBox.getHeight());
    dataCheckOut.setString("Data check-out:");
    dataCheckOut.getText().setCharacterSize(results[0].getText().getCharacterSize());
    dataCheckOut.setPosition(WINDOW_WIDTH/2-dataCheckOut.getWidth()/2, dataCheckIn.getY()+dataCheckIn.getText().getGlobalBounds().height*5);
    dataCheckOut.getText().setPosition(dataCheckOut.getX()+DISTANCE/2, dataCheckOut.getY());

    finalizeazaRezervare.setPosition(WINDOW_WIDTH/2-finalizeazaRezervare.getWidth()/2, dataCheckOut.getY()+dataCheckOut.getText().getGlobalBounds().height*5);
}

void makeRezervare()
{
    rezervare temp;
    if (!verificaFormat())//daca nu e bun
        return;

    if (!existaCamera())
    {
        dataCheckIn.setString("Camere insuficiente.");
        dataCheckOut.setString("Camere insuficiente.");
        return;
    }

    //daca exista camera, creez rezervarea
    temp.setCheckIn(dataCheckIn.getString());
    temp.setCheckOut(dataCheckOut.getString());
    temp.setHotelId(hoteluri[currentPosInHoteluri].getId());
    temp.setUser(utilizator);
    hoteluri[currentPosInHoteluri].getRezervariFacute().push_back(temp);
    dataCheckIn.setString("Succes!!!");
    dataCheckOut.setString("Succes!!!");
    rezervariChange=true;

    areRezervare=true;
}

bool verificaFormat()
{
    string checkIn, checkOut;
    checkIn=dataCheckIn.getString();
    checkOut=dataCheckOut.getString();
    unsigned int i;
    int ziIn, lunaIn, anIn;
    int ziOut, lunaOut, anOut;

    //verific ca sirurile sa fie corecte
    if (checkIn.size()!=checkOut.size() || checkIn.size()!=10)
    {
        dataCheckIn.setString("Format gresit!");
        dataCheckOut.setString("Format gresit!");
        return false;
    }

    if (!(checkIn[2]=='-' && checkIn[5]=='-' && checkOut[2]=='-' && checkOut[5]=='-'))
    {
        dataCheckIn.setString("Format gresit!");
        dataCheckOut.setString("Format gresit!");
        return false;
    }

    for (i=0; i<checkIn.size(); ++i)
    {
        if (i==2 || i==5) continue;
        if (!('0'<=checkIn[i] && checkIn[i]<='9' && '0'<=checkOut[i] && checkOut[i]<='9'))
        {
            dataCheckIn.setString("Format gresit!");
            dataCheckOut.setString("Format gresit!");
            return false;
        }
    }

    if (checkIn[6]=='0' || checkOut[6]=='0')
    {
        dataCheckIn.setString("An gresit!");
        dataCheckOut.setString("An gresit!");
        return false;
    }

    //si nu in ultimul rand...
    ziIn=lunaIn=anIn=0;
    ziIn=dateToInt(checkIn, "zi"); lunaIn=dateToInt(checkIn, "luna"); anIn=dateToInt(checkIn, "an");
    ziOut=dateToInt(checkOut, "zi"); lunaOut=dateToInt(checkOut, "luna"); anOut=dateToInt(checkOut, "an");

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    if (anIn<(now->tm_year + 1900) || (anIn==(now->tm_year + 1900) && lunaIn<now->tm_mon+1)  || (anIn==(now->tm_year + 1900) && lunaIn==now->tm_mon+1 && ziIn<now->tm_mday) ||
        anOut<(now->tm_year + 1900) || (anOut==(now->tm_year + 1900) && lunaOut<now->tm_mon+1)  || (anOut==(now->tm_year + 1900) && lunaOut==now->tm_mon+1 && ziOut<now->tm_mday))
    {
        dataCheckIn.setString("Data gresita!");
        dataCheckOut.setString("Data gresita!");
        return false;
    }

    return true;
}

bool existaCamera()
{
    struct pack{
        long double st, dr;
    };
    struct pack interval1, interval2;
    unsigned int i; int nrSuprapuneri=0;
    int luna, zi, an;

    //construiesc interval1

    zi=dateToInt(dataCheckIn.getString(), "zi"); luna=dateToInt(dataCheckIn.getString(), "luna"); an=dateToInt(dataCheckIn.getString(), "an");
    interval1.st=transformDateToDouble (zi, luna, an);

    zi=dateToInt(dataCheckOut.getString(), "zi"); luna=dateToInt(dataCheckOut.getString(), "luna"); an=dateToInt(dataCheckOut.getString(), "an");
    interval1.dr=transformDateToDouble (zi, luna, an);

    hotel currentHotel=hoteluri[currentPosInHoteluri];
    for (i=0; i<currentHotel.getRezervariFacute().size(); ++i)//caut sa vad daca se suprapun rezervarile
    {
        //construiesc interval2

        zi=dateToInt(currentHotel.getRezervariFacute()[i].getCheckIn(), "zi");
        luna=dateToInt(currentHotel.getRezervariFacute()[i].getCheckIn(), "luna");
        an=dateToInt(currentHotel.getRezervariFacute()[i].getCheckIn(), "an");
        interval2.st=transformDateToDouble (zi, luna, an);

        zi=dateToInt(currentHotel.getRezervariFacute()[i].getCheckOut(), "zi");
        luna=dateToInt(currentHotel.getRezervariFacute()[i].getCheckOut(), "luna");
        an=dateToInt(currentHotel.getRezervariFacute()[i].getCheckOut(), "an");
        interval2.dr=transformDateToDouble (zi, luna, an);

        if ((interval1.dr>=interval2.st && interval1.dr<=interval2.dr) || (interval1.st<=interval2.dr && interval1.st>=interval2.st))
        {
            ++nrSuprapuneri;
        }
            else
            if ((interval2.st>=interval1.st && interval2.dr<=interval1.dr) || (interval1.st>=interval2.st && interval1.dr<=interval2.dr))
            {
                ++nrSuprapuneri;
            }
    }

    if (nrSuprapuneri==currentHotel.getNrCamere())
        return false;//nu are camera disponibila in perioada respectiva

    return true;
}

int dateToInt (const string &source, const string &what)
{
    int zi, luna, an;
    zi=source[0]-'0'; zi=zi*10+(source[1]-'0');
    luna=source[3]-'0'; luna=luna*10+(source[4]-'0');
    an=source[6]-'0'; an=an*10+(source[7]-'0'); an=an*10+(source[8]-'0'); an=an*10+(source[9]-'0');
    if (!what.compare("zi"))
        return zi;
    if (!what.compare("luna"))
        return luna;
    if (!what.compare("an"))
        return an;
    return 0;
}

long double transformDateToDouble(const int &zi, const int &luna, const int &an)
{
    long double rez=0;
    int nrDaysInMonth=getDaysInMonth (luna, an);

    rez=an;
    rez+=(long double)luna/12;
    rez+=(long double)zi/(12*nrDaysInMonth);

    return rez;
}

int getDaysInMonth (const int &month, const int &year)
{
    int numberOfDays;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        numberOfDays = 30;
        else
        if (month == 2)
        {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeapYear)
            numberOfDays = 29;
            else
            numberOfDays = 28;
        }
            else
            numberOfDays = 31;

    return numberOfDays;
}

void citireRezervari()
{
    if (!unreadRezervari) return;

    unreadRezervari=false;
    unsigned int i, j, n=0;
    rezervare temp;
    ifstream fin ("rezervari.in");
    fin>>n; fin.get();//newline
    for (i=1; i<=n; ++i)
    {
        fin>>temp;
        for (j=0; j<hoteluri.size(); ++j)
            if (hoteluri[j].getId()==temp.getHotelId())
                hoteluri[j].getRezervariFacute().push_back (temp);
        fin.get();//newline
    }
    fin.close();
    return;
}

void checkScroll(const sf::Event &event)
{
    float scrollAmount=WINDOW_HEIGHT/10;
    //dy+=scrollAmount;
    if (event.key.code==sf::Keyboard::Down)
        {
            /*if (view.getCenter().y+view.getSize().y/2<CONTENT_HEIGHT)//daca are rost sa fac scroll
            {
                //vad cu cat trebuie sa fac scroll
                scrollAmount=min (scrollAmount, CONTENT_HEIGHT-view.getCenter().y+view.getSize().y/2);
            }*/
            dy+=scrollAmount;
            view.reset (sf::FloatRect(0, (int)dy, WINDOW_WIDTH, WINDOW_HEIGHT));
            //modific si pozitia butoanelor
            goBack.setPosition(goBack.getX(), goBack.getY()+scrollAmount);
        }

        if (event.key.code==sf::Keyboard::Up)
        {
            dy-=scrollAmount;
            view.reset (sf::FloatRect(0, (int)dy, WINDOW_WIDTH, WINDOW_HEIGHT));
            goBack.setPosition(goBack.getX(), goBack.getY()-scrollAmount);
        }
    window.setView(view);
}

void resetViewAndPos()
{
    window.setView(window.getDefaultView());
    dy=0;
    goBack.setPosition(DISTANCE, DISTANCE);
}

void setUpAddScreen()
{
    scrieNume.setSize(999, 999);
    scrieNume.setString("Insereaza numele hotelului");
    scrieNume.setSize(scrieNume.getText().getGlobalBounds().width+DISTANCE/2, nameBox.getHeight());
    scrieNume.setPosition(WINDOW_WIDTH/2-scrieNume.getWidth()/2, 1.5*cityBox.getY());

    scrieJudet.setSize(999, 999);
    scrieJudet.setString("Insereaza judetul hotelului");
    scrieJudet.setSize(scrieJudet.getText().getGlobalBounds().width+DISTANCE/2, nameBox.getHeight());
    scrieJudet.setPosition(WINDOW_WIDTH/2-scrieJudet.getWidth()/2, scrieNume.getY()+scrieNume.getHeight()+DISTANCE*2);

    scrieCamere.setSize(999, 999);
    scrieCamere.setString("Insereaza numarul de camere");
    scrieCamere.setSize(scrieCamere.getText().getGlobalBounds().width+DISTANCE/2, nameBox.getHeight());
    scrieCamere.setPosition(WINDOW_WIDTH/2-scrieCamere.getWidth()/2, scrieJudet.getY()+scrieJudet.getHeight()+DISTANCE*2);

    scrieDetalii.setSize(999, 999);
    scrieDetalii.setString("Insereaza detalii despre hotel");
    scrieDetalii.setSize(scrieDetalii.getText().getGlobalBounds().width+DISTANCE/2, nameBox.getHeight());
    scrieDetalii.setPosition(WINDOW_WIDTH/2-scrieDetalii.getWidth()/2, scrieCamere.getY()+scrieCamere.getHeight()+DISTANCE*2);

    finalizeazaAddHotel.setPosition(scrieDetalii.getX()+scrieDetalii.getWidth()+DISTANCE, scrieDetalii.getY()+scrieDetalii.getHeight()+DISTANCE*2);

    return;
}

void addHotel()
{
    if (!checkHotelInformation())//all good, homie
        return;

    citire();
    //altfel, inserez

    hotel temp;
    int numarCamere=0; unsigned int i;
    temp.setCity(scrieJudet.getString());
    temp.setName(scrieNume.getString());
    temp.setDescription(scrieDetalii.getString());

    //calculez numarul de camere
    for (i=0; i<scrieCamere.getString().size(); ++i)
        numarCamere=numarCamere*10+(scrieCamere.getString()[i]-'0');
    temp.setNrCamere(numarCamere);
    temp.setRating(0);
    temp.setNrVoturi(0);
    temp.setSum(0);
    temp.setId(hoteluri.size()+1);

    citire();
    hoteluri.push_back(temp);
    dataChange=true;//ca sa afisez si noul hotel

    scrieNume.setString("Succes!!!");
    scrieJudet.setString("Succes!!!");
    scrieCamere.setString("Succes!!!");
    scrieDetalii.setString("Succes!!!");
}

bool checkHotelInformation()
{
    unsigned int i;
    bool rez=true;
    for (i=0; i<scrieCamere.getString().size(); ++i)
        if (!('0'<=scrieCamere.getString()[i] && scrieCamere.getString()[i]<='9'))
    {
        scrieCamere.setString("Doar cifre!");
        rez=false;
    }

    if (scrieNume.getString().compare("Insereaza numele hotelului")==0)
    {
        scrieNume.setString("Introduceti un nume!");
        rez=false;
    }

    if (scrieJudet.getString().compare("Insereaza judetul hotelului")==0)
    {
        scrieJudet.setString("Introduceti un judet!");
        rez=false;
    }

    if (scrieDetalii.getString().compare("Insereaza detalii despre hotel")==0)
    {
        scrieDetalii.setString("Introduceti detalii despre hotel!");
        rez=false;
    }

    if (scrieCamere.getString().compare("Insereaza numarul de camere")==0)
    {
        scrieCamere.setString("Introduceti numarul de camere!");
        rez=false;
    }

    return rez;
}
