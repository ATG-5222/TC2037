#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <set>

#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

using namespace std;

//Actividad 5.3
//Aldo Tena García - A01275222
//Renato Sebastían Ramirez Calva - A01275401

set<char> alpha = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};

set<char> num = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

set<char> sign = {'+', '-', '=', '*', '/', '^', '(', ')','.'};

class numbers{	//Identificar tipos de numeros
	
    public:
    
        int caso;
        string numero;
        string resto;
        string r;
	
        void c0(char c);
        void c1(char c);
        void c2(char c);
        void c3(char c);
        void c4(char c);
        void c5(char c);
        void c6(char c);
        void c7(char c);
        string casos(string input);
};

class variables { //Identificación de variables

public:

	public:
	int caso;
	string v;
	string resto;
	string r;

	void inicio(char c);
	void c1(char c);
	string casos(string input);
};

//Identificación de signos y comentarios
class signs {

	public:

		int caso;
		string s;
		string resto;
		string r;

		void c0(char c);
		void c1(char c);
		void c2(char c);
		string casos(string input);
};

void signs::c0(char c){
	
		if (c == '*'){
			cout << c << " = Multiplicacion" << endl;
			caso = -1;			
		}
		else if (c == '^'){
			cout << c << " = Potencia" << endl;
			caso = -1;			
		}
		else if (c == '='){
			cout << c << " = Asignacion" << endl;
			caso = -1;
		}
		else if (c == '('){
			cout << c << " = Parentesis izquierdo" << endl;
			caso = -1;
		}
		else if (c == ')'){
			cout << c << " = Parentesis derecho" << endl;
			caso = -1;
		}					
		else if (c == '/'){
			caso = 1;
			s+=c;
		}
}

void signs::c1(char c){
		if (c == '/'){
				caso = 2;
				s+=c;
		}
		else {
				cout << "/ = Division" << endl;
				caso = -1;
				resto+=c;
		}

}

void signs::c2(char c){
		s+=c;
}

string signs::casos(string input){
	char c;
	caso = 0;
	for (int i = 0; i < input.size(); i++){
		c=input[i];		
		switch(caso){
			case -1: resto +=c; break;
			case 0 : c0(c); break;
			case 1 : c1(c); break;
			case 2 : c2(c); break;
		}
	}
	if (caso == 2){
		cout << s << " = Comentario" << endl;
	}
	string r = resto;
	resto = "";
	s = "";
	return r;
}

void numbers::c0(char c){		//Inicio de la busqueda de numeros
    if(num.find(c) != num.end()){
        caso = 1;
        numero += c;
    }
    else if(c == '+' || c == '-'){
        caso = 2;
        numero += c;
    }
    else if(c == '.'){
        caso = 3;
        numero += c;
    }
    else{
        caso = -1;
        resto += c;
    }
}

void numbers::c1(char c){	//Numeros enteros
    if(num.find(c) != num.end()){
        numero += c;
	}
    else if(c == '.'){
        caso = 3;
        numero += c;
    }
    else if(c == 'e' || c == 'E'){
        caso = 5;
        numero += c;
    }
    else{
        caso = -1;
        resto += c;
        cout <<  numero << " = Numero entero" << endl;
    }
}

void numbers::c2(char c){	//Deteccion de signo de suma o resta
    if(num.find(c) != num.end()){
        numero += c;
        caso = 1;
    }
    else if(c == '.'){
        caso = 3;
        numero += c;
    }
    else {
        if (numero == "+") { //Detección de suma o resta
            cout << numero << " = Suma" << endl;
            caso = -1;
            resto+=c;
        }
        else if(numero == "-") {
            cout << numero << " = Resta" << endl;
            caso = -1;
            resto += c;
        }
        else {
            resto += c;
            caso = -1;
        }
    }		
}

void numbers::c3(char c){	//Detección del signo y numeros reales (flotantes)
    if(num.find(c) != num.end()){
        numero += c;
        caso = 4;
    }
    else if(numero.size() == 1){
        cout << numero << " = Punto" << endl;
    }
    else{
        resto+=c;
        caso = -1;
    }
}

void numbers::c4(char c){	//Detección del número despues del punto
    if(num.find(c) != num.end()){
        numero += c;
    }
	else if(c == 'e' || c == 'E'){
        numero += c;
        caso = 5;
    }
    else{
        cout << numero << " = Numero real" << endl;
        caso = -1;
        resto += c;
    }
}

void numbers::c5(char c){	//Detección del numero de Euler
    if(c == '+' || c == '-'){
        caso = 6;
        numero+=c;
    }
    else if(num.find(c) != num.end()){
        numero += c;
        caso = 7;
    }		
    else {
        caso = -1;
        cout << "Valor no reconocido" << endl;	//Valor no expresado correctamente.
    }
}

void numbers::c6(char c){	//Detección del signo después del número de Euler
    if(num.find(c) != num.end()){
        numero+=c;
        caso = 7;
    }	
    else {
        caso = -1;
        cout << "Valor no reconocido" << endl; // Exponencial sin valor númerico.
    }
}

void numbers::c7(char c){	//Detección del número después del número de Euler
    if(num.find(c) != num.end()){
        numero+=c;
    }	
    else{
        cout << numero << " = Numero real" << endl;
        caso = -1;
        resto += c;
    }		
}

string numbers::casos(string input){ //Selección entre los distintos casoss
    char c;
    caso = 0;
    for (int i = 0; i < input.size(); i++){
        c=input[i];
        switch(caso){
            case -1 : resto+=c; break;
            case 0 : c0(c); break;
            case 1 : c1(c); break;
            case 2 : c2(c); break;
            case 3 : c3(c); break;
            case 4 : c4(c); break;
            case 5 : c5(c); break;
            case 6 : c6(c); break;
            case 7 : c7(c); break;		        
        }
    }
    if (caso == 1){		//En caso de salto de linea
        cout << numero << " = Numero entero" << endl;
    }
    if (caso == 4 || caso == 7){
        cout << numero << " = Numero real" << endl;
    }
    r = resto;
    resto = "";
    numero= "";
    return r;
}

void variables::inicio(char c){
	if (alpha.find(c) != alpha.end()){
		caso = 1;
		v+=c;
	}
	else {
		cout << c << " = Valor no reconocido" << endl;
		resto +=c;
		caso = -1;
	}
}

void variables::c1(char c){
	if (alpha.find(c) != alpha.end() || num.find(c) != num.end()){
		v+=c;
	}
	else {
		caso = -1;
		cout << v << " = Variable" << endl;
		resto +=c;
	}
}

string variables::casos(string input){
	char c;
	caso = 0;
	for (int i = 0; i < input.size(); i++){
		c=input[i];
		switch(caso){
			case -1: resto+=c; break;
            case 0 : inicio(c); break;
            case 1 : c1(c); break;
		}
	}
	if (caso != -1){
		cout << v << " = Variable" << endl;
	}
	r = resto;
	resto = "";
	v = "";
	return r;		
}

void* lexerAritmetico(string file) {

    ifstream d;
	string input;
	string res;

	numbers N;
	variables V;
	signs S;

    d.open(file);
	if (d.is_open()){
		while (getline(d, input)){
			while (input != ""){
				char c = input[0];
				if (num.find(c) != num.end() || c == '+' || c == '-' || c == '.'){
					res = N.casos(input);
					input = res;
				}
				else if (alpha.find(c) != alpha.end()){
					res = V.casos(input);
					input = res;
				}
				else if (sign.find(c) != sign.end()){
					res = S.casos(input);
					input = res;
				}
                else if(c == ' '){
                    input.erase(0,1);				
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {

    double seq, parallel;

    if (argc > 1){
        string arg1(argv[1]);
        string file = arg1;
    }

    if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
    }

    /*************************************************************
	* Implementacion Secuencial
	*************************************************************/
	cout << endl;
	cout << "Running sequential code..." << endl;
	cout << argv[1] << endl;
	lexerAritmetico(argv[1]);
	printf("\tTiempo en secuencial = %lf \n",seq);
	cout << endl;

    
	return 0;
}