#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <set>
using namespace std;

set<char> alpha = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};

set<char> num = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

set<char> sign = {'+', '-', '=', '*', '/', '^', '(', ')'};

class numbers{		//para identificar números enteros y decimales
	
    public:
    
        int caso;
        string numero;
        string resto;
        string r;
	
        void caso0(char c){		//inicio
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

        void caso1(char c){		//int
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
                cout << "'" << numero << "' = número entero" << endl;
            }
        }

        void caso2(char c){	//signo
            if(num.find(c) != num.end()){
                numero += c;
                caso = 1;
            }
            else if(c == '.'){
                caso = 3;
                numero += c;
            }
            else {
                if (numero == "+") {	//identificando signos de suma y resta
                    cout << "'" << numero << "' = suma" << endl;
                    caso = -1;
                    resto+=c;
                }
                else if(numero == "-") {
                    cout << "'" << numero << "' = resta" << endl;
                    caso = -1;
                    resto += c;
                }
                else {
                    resto += c;
                    caso = -1;
                }
            }		
        }

        void caso3(char c){		//punto
            if(num.find(c) != num.end()){
                numero += c;
                caso = 4;
            }
            else if(numero.size() == 1){
                cout << "'" << numero << "' = punto" << endl;
            }
            else{
                resto+=c;
                caso = -1;
            }
        }

        void caso4(char c){		//número después del punto
            if(num.find(c) != num.end()){
            numero += c;
            }
            else if(c == 'e' || c == 'E'){
                numero += c;
                caso = 5;
            }
            else{
                cout << "'" << numero << "' = número real" << endl;
                caso = -1;
                resto += c;
            }
        }

        void caso5(char c){		//e, E
            if(c == '+' || c == '-'){
                caso = 6;
                numero+=c;
            }
            else if(n.find(c) != n.end()){
            numero += c;
            caso = 7;
            }		
            else {
                caso = -1;
                //resto+= c;
                cout << "valor no reconocido" << endl;	//esto porque el exponencial no tiene un valor numérico.
            }
        }

        void caso6(char c){		//signo después de e,E
            if(n.find(c) != n.end()){
            numero+=c;
            caso = 7;
            }	
            else {
                caso = -1;
                //resto += c;
                cout << "valor no reconocido" << endl; //esto porque el exponencial no tiene un valor numérico.
            }
        }
        void caso7(char c){		//número después de e,E
            if(n.find(c) != n.end()){
            numero+=c;
            }	
            else{
                cout << "'" << numero << "' = número real" << endl;
                caso = -1;
                resto += c;
            }		

        }

        string casos(string input){
            char c;
            caso = 0;
            for (int i = 0; i < input.size(); i++){
                c=input[i];
                switch(caso){
                    case -1 : resto+=c; break;
                    case 0 : caso0(c); break;
                    case 1 : caso1(c); break;
                    case 2 : caso2(c); break;
                    case 3 : caso3(c); break;
                    case 4 : caso4(c); break;
                    case 5 : caso5(c); break;
                    case 6 : caso6(c); break;
                    case 7 : caso7(c); break;		        
                }
            }
            if (caso == 1){		//En caso de que se termine el renglón
                cout << "'" << numero << "' = número entero" << endl;
            }
            if (caso == 4 || caso == 7){
                cout << "'" << numero << "' = número real" << endl;
            }
            r = resto;
            resto = "";
            numero= "";
            return r;
        };
};