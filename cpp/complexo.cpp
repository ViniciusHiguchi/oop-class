#include <iostream>
#include <cmath>
#include <iomanip>

class Complexo {
  private: int x, y;
  public:
           Complexo();
           Complexo(int, int);
           void setReal(int);
           void setImag(int);
           int getReal();
           int getImag();
           Complexo operator+(Complexo);
           Complexo operator-(Complexo);
           Complexo operator*(Complexo);
           Complexo operator/(Complexo);
           void operator=(int);
           operator float();
           operator double();
};

Complexo::Complexo() {
  this->setReal(0);
  this->setImag(0);
}

Complexo::Complexo(int x, int y) {
  this->setReal(x);
  this->setImag(y);
}

void Complexo::setReal(int x) {this->x = x;}
void Complexo::setImag(int y) {this->y = y;}
int Complexo::getReal() {return this->x;}
int Complexo::getImag() {return this->y;}

Complexo Complexo::operator+(Complexo c2) {
  Complexo comp;
  comp.setReal(this->getReal() + c2.getReal());
  comp.setImag(this->getImag() + c2.getImag());
  return comp;
}// ok

Complexo Complexo::operator-(Complexo c2) {
  Complexo comp;
  comp.setReal(this->getReal() - c2.getReal());
  comp.setImag(this->getImag() - c2.getImag());
  return comp;
} // ok

//(a+bi)(c+di) = ac + adi + bic + bdi^2 ==  (ac - bd) + (ad + bc)i
Complexo Complexo::operator*(Complexo c2) {
  Complexo comp;
  comp.setReal(this->getReal()*c2.getReal() - this->getImag()*c2.getImag());
  comp.setImag(this->getReal()*c2.getImag() + this->getImag()*c2.getReal());
  return comp;
} // ok

Complexo Complexo::operator/(Complexo c2) {
  Complexo comp;
  comp.setReal((this->getReal()*c2.getReal() + this->getImag()*c2.getImag())/(c2.getReal()*c2.getReal() + c2.getImag()*c2.getImag()));
  comp.setImag((this->getImag()*c2.getReal() - this->getReal()*c2.getImag())/(c2.getReal()*c2.getReal() + c2.getImag()*c2.getImag()));
  return comp;
}

void Complexo::operator=(int n) {
  this->setReal(n);
  this->setImag(0);
}

Complexo::operator float() {
  return (float)sqrt((this->getReal()*this->getReal()) + (this->getImag()*this->getImag()));
}

Complexo::operator double() {
  return sqrt((this->getReal()*this->getReal()) + (this->getImag()*this->getImag()));
}

int main() {
  int r1;
  char i;
  Complexo num1;
  
  while (std::cin >> r1) {
    num1 = r1;
    std::cout << num1.getReal() << '+' << num1.getImag() << 'i' << std::endl;
  }

  return 0;
}