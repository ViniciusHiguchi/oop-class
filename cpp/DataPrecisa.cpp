#include <iostream>

class Cronometro 
{
    private: 
        int hora, minuto, segundo;
    public: 
        Cronometro();
        Cronometro(int, int, int);
        
        int getHora();
        int getMin();
        int getSeg();
        
        void setHora(int);
        void setMin(int);
        void setSeg(int);

        virtual void tic();
        virtual void tac() = 0;
        virtual void toc() = 0;
        bool valida();
        std::string watchface();
};

Cronometro::Cronometro() {
    this->setHora(0);
    this->setMin(0);
    this->setSeg(0);
}

Cronometro::Cronometro(int h, int m, int s) {
    this->setHora(h);
    this->setMin(m);
    this->setSeg(s);
}

bool Cronometro::valida() {
    if (getSeg() > 59 || getMin() > 59) {
        return false;
    }

    return true;
}

void Cronometro::tic() {
    setSeg( getSeg()+1 );

    if (!valida()) {
        setSeg(0);
        setMin( getMin() + 1 );

        if (!valida()) {
            setMin(0);
            setHora( getHora() + 1 );
        }
    }
}


std::string Cronometro::watchface() {
    std::string wf = "";
    wf += std::to_string(this->getHora()) + ":";
    wf += std::to_string(this->getMin()) + ":";
    wf += std::to_string(this->getSeg());
    return wf;
}

int Cronometro::getHora() {return this->hora;}
int Cronometro::getMin() {return this->minuto;}
int Cronometro::getSeg() {return this->segundo;}
void Cronometro::setHora(int v) {this->hora = v;}
void Cronometro::setMin(int v) {this->minuto = v;}
void Cronometro::setSeg(int v) {this->segundo = v;}


class Relogio : public Cronometro {
    public:
        Relogio(int,int,int);
        void tic();
        void tac();
        void toc();
        bool valida();
};

Relogio::Relogio(int h, int m, int s) {
    this->setHora(h);
    this->setMin(m);
    this->setSeg(s);
}

bool Relogio::valida() {
    if (Cronometro::valida()) {
        if (this->getHora() > 23) {
            return false;
        }
        return true;
    }
    return false;
}

void Relogio::tic() {
    setSeg( getSeg()+1 );
    if (!this->valida()) {
      this->setSeg(0);
      this->tac();
    }
}

void Relogio::tac() {
    setMin( getMin() + 1);
    if (!this->valida()) {
        setMin(0);
        this->toc();
    }
}

void Relogio::toc() {
    setHora( getHora() + 1 );
    if (!this->valida()) {
        this->setHora(0);
    }
}


class Data {
    private:
      int dia, mes, ano;
    public:
      Data(int, int, int);
      std::string getDataRepr();
      bool valida();
      bool isBissexto();
      bool isBissexto(Data);
      bool isBissexto(int);
      void incrementa();

      void setDia(int);
      void setMes(int);
      void setAno(int);

      int getDia();
      int getMes();
      int getAno();
};

Data::Data(int dia, int mes, int ano) {
    this->setDia(dia);
    this->setMes(mes);
    this->setAno(ano);
}

bool Data::isBissexto()  {
    return this->getAno()%400 == 0 || this->getAno()%100 != 0 && this->getAno()%4 == 0;
}

bool Data::isBissexto(int ano) {
    return ano%400 == 0 || ano % 100 != 0 && ano%4 == 0;
}

bool Data::isBissexto(Data data) {
    return data.isBissexto();
}

bool Data::valida() {
    return this->getDia() > 0 && this->getMes() > 0 && this->getMes() <= 12 && (this->getAno() > 1582 || (this->getAno() == 1582 && this->getMes() > 10) || (this->getAno() == 1582 && this->getMes() == 10 && this->getDia() >= 15)) && (((this->getMes() == 1 || this->getMes() == 3 || this->getMes() == 5 || this->getMes() == 7 || this->getMes() == 8 || this->getMes() == 10 || this->getMes() == 12) && this->getDia() <= 31) || ((this->getMes() == 4 || this->getMes() == 6 || this->getMes() == 9 || this->getMes() == 11) && this->getDia() <= 30) || ((this->getMes() == 2 && this->getDia() <= 28) || (this->getMes() == 2 && Data::isBissexto(this->getAno()) && this->getDia() <= 29)));
}

void Data::setDia(int dia) {this->dia = dia;}
void Data::setMes(int mes) {this->mes = mes;}
void Data::setAno(int ano) {this->ano = ano;}
int Data::getDia() {return this->dia;}
int Data::getMes() {return this->mes;}
int Data::getAno() {return this->ano;}


int main() {
  int dia, mes, ano;
  Data *c;

  std::cin >> dia >> mes >> ano;
  c = new Data(dia, mes, ano);
  std::cout << c->valida();
  return 0;
}

/*
int main(){
    std::string input;
    int h, m, s;
    Cronometro *c;

    std::cin >> h >> m >> s;
    c = new Relogio(h,m,s);

    while( std::cin >> input ) {
        if (input == "tic") {
            c->tic();
        } else if (input == "tac") {
            c->tac();
        } else if (input == "toc") {
            c->toc();
        }
    }

    std::cout << c->watchface() << std::endl;
}
*/
