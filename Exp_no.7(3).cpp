// c++ program to illustrate the implement of hybrid inheritance 
#include<iostream>
using namespace std;
class Vehicle {
public:
Vehicle() { cout<<"This is a vehicle\n";}
};
class Fare {
public:
Fare() { cout<<"Fare of Vehicle\n";}
};
class Car:public Vehicle
{
public:
Car() { cout<<"This Vehicle is Car\n";}
};
class Bus:public Vehicle,public Fare {
public:
Bus() { cout<<"this Vehicle is a Bus with Fare\n";}
};
int main()
{
Bus obj2;
return 0;
}
