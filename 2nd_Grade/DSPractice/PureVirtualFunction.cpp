#include <iostream>
using namespace std;

class Shape{
public:
    virtual void draw() const = 0;
    virtual ~Shape(){
        cout << "Shape destructor" << endl;
    }
};

class Circle : public Shape{
public:
    void draw() const override{
        cout << "Drawing Circle" << endl;
    }
    ~Circle(){
        cout << "Circle destructor" << endl;
    }
};

int main(){
    Shape *shape = new Circle();
    shape->draw();

    delete shape;

    return 0;
}