#include <iostream>
#include <ostream>
using std::endl;
using std::cout;



class Coordinate
{
private:
        int x;
        int y;
public:
        Coordinate (int x, int y) : x(x), y(y) {};
        int getx() const { return x; };
        int gety() const { return y; };
        void setx(int newx) { x = newx; };
        void sety(int newy) { y = newy; };

        bool operator==(const Coordinate& that) const
        {
                int thisx = this->getx();
                int thisy = this->gety();
                int thatx = that.getx();
                int thaty = that.gety();

                return thisx == thatx && thisy == thaty;
        }
};



void printCoordinate(const Coordinate& point)
{
        int x = point.getx();
        int y = point.gety();
        cout << "(" << x << ", " << y << ")" << endl;
};

void swapCoordinates(Coordinate& first, Coordinate& second)
{
        Coordinate temp = first;
        first = second;
        second = temp;
}

void shiftCopy(Coordinate point, int amount)
{
        int result = amount + point.getx();
        point.setx(result);
};

void shiftOriginal(Coordinate& point, int amount)
{
        int result = amount + point.getx();
        point.setx(result);
};


std::ostream& operator<<(std::ostream& os, const Coordinate& a)
{
        int x = a.getx();
        int y = a.gety();
        os << "(" << x << ", " << y << ")";
        return os;
}


template<typename T>
void printAll(const T& items)
{
        for (const auto& object : items)
        {
                cout << object;
                cout << " ";
        }
        cout << endl;
}




int main()
{
        Coordinate original(2, 7);
        Coordinate snapshot = original;
        Coordinate* pointer = &original;
        Coordinate& alias = original;

        pointer->setx(10);
        alias.sety(20);
        printCoordinate(original);
        printCoordinate(snapshot);
        printCoordinate(*pointer);
        pointer = &snapshot;
        Coordinate& tmp = *pointer;
        tmp.setx(-5);
        printCoordinate(original);
        printCoordinate(snapshot);
};