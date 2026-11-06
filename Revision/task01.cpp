#include <iostream>
#include <ostream>
#include <vector>
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


std::vector<Coordinate*> selectByX(const std::vector<Coordinate>& points, int minimumX)
{
        std::vector<Coordinate*> result;
        for (Coordinate point : points) {
                if (point.getx() >= minimumX) {
                        result.push_back(&point);
                }
        }
        return result;
}


void shiftSelected(const std::vector<Coordinate*>& selected, int dx, int dy)
{
        for (Coordinate* point : selected)
        {
                if (point != nullptr)
                {
                        point->setx(point->getx() + dx);
                        point->sety(point->gety() + dy);
                }
        }
}


std::pair<int, int> xBounds(const std::vector<Coordinate>& points)
{
        std::pair<int, int> result;
        result.first = points[0].getx();
        result.second = points[0].getx();
        if (points.size() > 1)
        {
                for (int i = 1; i < points.size(); i++)
                {
                        if (points[i].getx() < result.first)
                        {
                                result.first = points[i].getx();
                        }
                        else if (points[i].getx() > result.second)
                        {
                                result.second = points[i].getx();
                        }
                }
                return result;
        }

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