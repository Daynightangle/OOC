// C++ program to illustrate the multiple inheritance
#include<iostream>
using namespace std;
class Vehicle {
public:
Vehicle() { cout<<"this is Vehicle\n";}
};
class FourWheeler {
public:
FourWheeler() { cout<<"This is 4 wheeler\n";}
};
class Car:public Vehicle,public FourWheeler {
public:
Car() { cout<<"This 4 wheeler vehicle is car\n";}
};
int main()
{
Car obj;
return 0;
}
