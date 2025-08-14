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
        virtual std::string watchface();
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
    Cronometro::tic();
    if (!this->valida()) {
        this->setHora(0);
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


class Watch : public Cronometro {
    private:
        bool am;
    public:
        Watch(int, int, int, std::string);
        void tic();
        void tac();
        void toc();
        bool valida();
        std::string watchface();
        bool getAm();
        void setAm(bool);
};

bool Watch::getAm() {return this->am;}
void Watch::setAm(bool am) {this->am = am;}

Watch::Watch(int h, int m, int s, std::string am) {
    this->setHora(h);
    this->setMin(m);
    this->setSeg(s);
    if (am == "AM"){
        this->setAm(true);
    } else {
        this->setAm(false);
    }
}

bool Watch::valida() {
    if (Cronometro::valida()) {
        if (this->getHora() > 12) {
            return false;
        }
        return true;
    }
    return false;
}

void Watch::tic() {
    this->setSeg( this->getSeg() + 1);
    if (!valida()) {
        this->setSeg(0);
        this->tac();
    }
}

void Watch::tac() {
    this->setMin( this->getMin() + 1);
    if (!this->valida()) {
        this->setMin(0);
        this->toc();
    }
}

void Watch::toc() {
    this->setHora( this->getHora() + 1 );

    if(this->getHora() == 12) {
        this->setAm( !this->getAm() );
    }

    if (!this->valida()) {
        this->setHora(1);
    }
    
}

std::string Watch::watchface(){
    std::string ampm = this->getAm() ? "AM" : "PM";
    return Cronometro::watchface() + " " + ampm;
}

int main(){
    std::string input;
    int h, m, s;
    std::string ampm;
    Cronometro *c;

    c = new Watch(12,0,0, "AM");

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
