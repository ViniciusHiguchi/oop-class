#include <iostream>
#include <iomanip>
#include <stdexcept>

class Data
{
    private:
            int dia, mes, ano;
    public:
            Data();
            Data(int, int, int);
            void setDia(int);
            void setMes(int);
            void setAno(int);
            int getDia();
            int getMes();
            int getAno();
            bool valida();
            static bool isBissexto(int);
            static bool isBissexto(Data);
            static int ultimoDiaDoMes(int, int);
            static int ultimoDiaDoMes(Data);
            void decrementar();
            Data operator--();
            Data operator--(int);
            friend std::ostream & operator<<(std::ostream &, Data);
            friend std::istream & operator>>(std::istream &, Data *);
};

class BeforeGregorianCalendarException : public std::runtime_error
{
    public:
            BeforeGregorianCalendarException() : runtime_error("nao existe dia anterior para esta data")
            {

            }
};

Data::Data()
{

}

Data::Data(int dia, int mes, int ano)
{
    this->setDia(dia);
    this->setMes(mes);
    this->setAno(ano);
}

void Data::setDia(int dia)
{
    this->dia = dia;
}

void Data::setMes(int mes)
{
    this->mes = mes;
}

void Data::setAno(int ano)
{
    this->ano = ano;
}

int Data::getDia()
{
    return this->dia;
}

int Data::getMes()
{
    return this->mes;
}

int Data::getAno()
{
    return this->ano;
}

bool Data::valida()
{
    return this->getDia() > 0 && this->getMes() > 0 && this->getMes() <= 12 && (this->getAno() > 1582 || (this->getAno() == 1582 && this->getMes() > 10) || (this->getAno() == 1582 && this->getMes() == 10 && this->getDia() >= 15)) && (((this->getMes() == 1 || this->getMes() == 3 || this->getMes() == 5 || this->getMes() == 7 || this->getMes() == 8 || this->getMes() == 10 || this->getMes() == 12) && this->getDia() <= 31) || ((this->getMes() == 4 || this->getMes() == 6 || this->getMes() == 9 || this->getMes() == 11) && this->getDia() <= 30) || ((this->getMes() == 2 && this->getDia() <= 28) || (this->getMes() == 2 && Data::isBissexto(this->getAno()) && this->getDia() <= 29)));
}

bool Data::isBissexto(int ano)
{
    return ano%400 == 0 || ano%100 != 0 && ano%4 == 0;
}

bool Data::isBissexto(Data dt)
{
    return Data::isBissexto(dt.getAno());
}

int Data::ultimoDiaDoMes(int mes, int ano)
{
    int ultimoDia = 0;
    if(mes == 1)
    {
        ultimoDia = 31;
    }
    else if(mes == 2)
    {
        if(Data::isBissexto(ano))
        {
            ultimoDia = 29;
        }
        else
        {
            ultimoDia = 28;
        }
    }
    else if(mes == 3)
    {
        ultimoDia = 31;
    }
    else if(mes == 4)
    {
        ultimoDia = 30;
    }
    else if(mes == 5)
    {
        ultimoDia = 31;
    }
    else if(mes == 6)
    {
        ultimoDia = 30;
    }
    else if(mes == 7)
    {
        ultimoDia = 31;
    }
    else if(mes == 8)
    {
        ultimoDia = 31;
    }
    else if(mes == 9)
    {
        ultimoDia = 30;
    }
    else if(mes == 10)
    {
        ultimoDia = 31;
    }
    else if(mes == 11)
    {
        ultimoDia = 30;
    }
    else
    {
        ultimoDia = 31;
    }
    return ultimoDia;
}

int Data::ultimoDiaDoMes(Data dt)
{
    return Data::ultimoDiaDoMes(dt.getMes(), dt.getAno());
}

void Data::decrementar()
{
    if(this->getAno() == 1582 && this->getMes() == 10 && this->getDia() == 15)
    {
        throw BeforeGregorianCalendarException();
    }
    else
    {
        this->setDia(this->getDia() - 1);
        if(!this->valida())
        {
            this->setMes(this->getMes() - 1);
            this->setDia(Data::ultimoDiaDoMes(this->getMes(), this->getAno()));
            if(!this->valida())
            {
                this->setDia(31);
                this->setMes(12);
                this->setAno(this->getAno() - 1);
            }
        }
    }
}

Data Data::operator--()
{
    this->decrementar();
    return *this;
}

Data Data::operator--(int)
{
    Data dt = *this;
    --(*this);
    return dt;
}

std::ostream & operator<<(std::ostream &saida, Data dt)
{
    saida << std::setfill('0') << std::setw(2);
    saida << dt.getDia() << " ";
    saida << std::setfill('0') << std::setw(2);
    saida << dt.getMes() << " ";
    saida << std::setfill('0') << std::setw(4);
    saida << dt.getAno();
    return saida;
}

std::istream & operator>>(std::istream &entrada, Data *dt)
{
    int dia, mes, ano;
    entrada >> dia >> mes >> ano;
    dt->setDia(dia);
    dt->setMes(mes);
    dt->setAno(ano);
    return entrada;
}

int main()
{
    Data *data = new Data();

    std::cin >> data;
	try
	{
		(*data)--;
		std::cout << (*data) << std::endl;
	}
	catch(const BeforeGregorianCalendarException &bgce)
	{
		std::cout << bgce.what() << std::endl;
	}

    return 0;
}