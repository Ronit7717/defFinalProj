#include <iostream>
#include <math.h>


void f(int i) { std::cout << pow(i, 2) << std::endl; }
double f(double r) { return pow(r, 2); }
int f(int i) { return pow(i, 2); }
int main() {

 double d = f(12.6); std::cout << "d is " << d << std::endl;
 int s = f(18); std::cout << "s is " << s << std::endl;
 }