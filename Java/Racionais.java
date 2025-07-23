import java.util.Scanner;

public class Racionais {
    public static void main(String[] args) {
        Racional r1 = new Racional(0, 0);
        Racional r2 = new Racional(0, 0);
        String operation;

        Scanner sc = new Scanner(System.in);
        while (sc.hasNextInt()) {
            r1.setNumerador(sc.nextInt());
            r1.setDenominador(sc.nextInt());
            operation = sc.next();
            r2.setNumerador(sc.nextInt());
            r2.setDenominador(sc.nextInt());

            switch (operation) {
                case "+":
                    r1.adicao(r2);
                    break;
                case "-":
                    r1.subtracao(r2);
                    break;
                case "/":
                    r1.divisao(r2);
                    break;
                case "*":
                    r1.multiplicacao(r2);
                    break;
            }

            r1.simplifica();
            System.out.printf("%d %d\n",r1.getNumerador(), r1.getDenominador());
        }
    }
}

class Racional {

    private int denominador;
    private int numerador;

    public Racional(int numerador, int denominador) {
        this.denominador = denominador;
        this.numerador = numerador;
    }

    public void negativo() {
        this.numerador = -this.numerador;
    }

    public void adicao(Racional operando) {
        int denom, num;
        num = (this.numerador * operando.getDenominador()) + (operando.getNumerador() * this.denominador);
        denom = this.denominador * operando.getDenominador();

        this.numerador = num;
        this.denominador = denom;
    }

    public void subtracao(Racional operando) {
        int denom, num;
        num = (this.numerador * operando.getDenominador()) - (operando.getNumerador() * this.denominador);
        denom = (this.denominador * operando.getDenominador());
        
        this.numerador = num;
        this.denominador = denom;
    }

    public void multiplicacao(Racional operando) {
        this.numerador *= operando.getNumerador();
        this.denominador *= operando.getDenominador();
    }

    public void divisao(Racional operando) {
        this.numerador *= operando.getDenominador();
        this.denominador *= operando.getNumerador();
    }

    public void divisao(int operando) {
        this.denominador *= operando;
    }

    public void simplifica() {
        int a, b, temp;

        if (this.denominador < 0) {
            this.numerador = -this.numerador;
            this.denominador = -this.denominador;
        }

        a = Math.abs(this.numerador);
        b = Math.abs(this.denominador);

        // Euclidean Algorithm
        while (b != 0) {
            temp = b; // Store current b
            b = a % b;    // b becomes the remainder of a divided by b
            a = temp;     // a becomes the old b
        }

        this.denominador /= a;
        this.numerador /= a;
    }

    public int getDenominador() {return this.denominador;}
    public int getNumerador() {return this.numerador;}

    public void setDenominador(int newValue) {this.denominador = newValue;}
    public void setNumerador(int newValue) {this.numerador = newValue;}

}
