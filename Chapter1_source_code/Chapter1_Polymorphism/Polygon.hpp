#include <iostream>

class Polygon{
    protected:
        int width, height;
    public:
        Polygon(int w=0, int h=0){
            width = w;
            height = h;
        };
        void set_values(int w, int h);
        virtual int Area() const{
            return (0);
        }
};

class Rectangle:public Polygon{
    public:
        Rectangle(int w = 0, int h = 0):Polygon(w,h){}
    int Area() const{
        return width*height;
    }
};


class Triangle:public Polygon{
    public:
        Triangle(int w = 0, int h = 0):Polygon(w,h){}
    int Area() const{
        return width*height/2;
    }
};
