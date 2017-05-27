#ifndef BOX_H
#define BOX_H


class box
{
    int width, height;
    int x, y;

    public:
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void setX(const int&);
    void setY(const int&);
    void setWidth(const int&);
    void setHeight(const int&);
};

#endif // BOX_H
