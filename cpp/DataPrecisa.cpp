#include <iostream>
#include <stdexcept>

class HourOutOf24HourBoundsRuntimeException : public std::runtime_error {
    public:
        HourOutOf24HourBoundsRuntimeException() : runtime_error("Horário maior ou igual a 24 horas deu pau no pc.") 
        {

        }
};

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
        std::string getStrRepr();
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


std::string Cronometro::getStrRepr() {
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

//-----------------------------------------------------------------------------------

class Relogio : public Cronometro {
    public:
        Relogio();
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

Relogio::Relogio() {
    this->setHora(0);
    this->setMin(0);
    this->setSeg(0);
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
        throw HourOutOf24HourBoundsRuntimeException();
    }
}

//-----------------------------------------------------------------------------------

class Data {
    private:
      int dia, mes, ano;
    public:
      Data();
      Data(int, int, int);
      std::string getStrRepr();
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

std::string Data::getStrRepr() {
    std::string data = "";
    data += std::to_string(this->getDia()) + "/";
    data += std::to_string(this->getMes()) + "/";
    data += std::to_string(this->getAno());
    return data;
}

Data::Data(int dia, int mes, int ano) {
    this->setDia(dia);
    this->setMes(mes);
    this->setAno(ano);
}

Data::Data() {}

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
    return this->getDia() > 0 && this->getMes() > 0 && this->getMes() <= 12 \
    && (this->getAno() > 1582 || (this->getAno() == 1582 && this->getMes() > 10) || (this->getAno() == 1582 && this->getMes() == 10 && this->getDia() >= 15)) \
    && (((this->getMes() == 1 || this->getMes() == 3 || this->getMes() == 5 || this->getMes() == 7 || this->getMes() == 8 || this->getMes() == 10 || this->getMes() == 12)&& this->getDia() <= 31) \
    || ((this->getMes() == 4 || this->getMes() == 6 || this->getMes() == 9 || this->getMes() == 11) && this->getDia() <= 30) \
    || ((this->getMes() == 2 && this->getDia() <= 28) || (this->getMes() == 2 && Data::isBissexto(this->getAno()) && this->getDia() <= 29)));
}

void Data::incrementa() {
    this->setDia( this->getDia() + 1);
    if (!this->valida()) {
        this->setDia( 1 );
        this->setMes( this->getMes() + 1);
        if (!this->valida()) {
            this->setMes( 1 );
            this->setAno( this->getAno() + 1);
        }
    }
}

void Data::setDia(int dia) {this->dia = dia;}
void Data::setMes(int mes) {this->mes = mes;}
void Data::setAno(int ano) {this->ano = ano;}
int Data::getDia() {return this->dia;}
int Data::getMes() {return this->mes;}
int Data::getAno() {return this->ano;}

//-----------------------------------------------------------------------------------
class DataPrecisa : public Relogio, public Data {
    public:
        DataPrecisa(int, int, int, int, int, int);
        void incrementa();
        std::string getStrRepr();
};

DataPrecisa::DataPrecisa(int dia, int mes, int ano, int h, int m, int s) {
    this->setDia(dia);
    this->setMes(mes);
    this->setAno(ano);
    this->setHora(h);
    this->setMin(m);
    this->setSeg(s);

}

std::string DataPrecisa::getStrRepr() {
    std::string data = Data::getStrRepr();
    std::string horario = Relogio::getStrRepr();

    return data + " " + horario;
}

void DataPrecisa::incrementa() {
    try {
        this->tic();
    } catch (const HourOutOf24HourBoundsRuntimeException &error) {
        this->setHora(0);
        this->setMin(0);
        this->setSeg(0);
        Data::incrementa();
    }
}

//-----------------------------------------------------------------------------------

int main(){
    std::string input;
    int h, m, s;
    int dia, mes, ano;

    DataPrecisa *c;

    std::cin >> dia >> mes >> ano >> h >> m >> s;
    c = new DataPrecisa(dia, mes, ano, h,m,s);
    std::cin >> input;
    for (int i = 0; i<input.length(); i++) {
        c->incrementa();
    }

    std::cout << c->getStrRepr() << std::endl;
}