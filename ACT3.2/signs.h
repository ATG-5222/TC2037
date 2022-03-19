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

class signs {

private:

	int caso;
	string s;
	string resto;
	string r;

public:

	void caso0(char c){
		if (c == '*'){
			cout << "'" << c << "' = Multiplicación" << endl;
			caso = -1;
		}
		else if (c == '^'){
			cout << "'" << c << "' = Potencia" << endl;
			caso = -1;
		}
		else if (c == '='){
			cout << "'" << c << "' = Asignación" << endl;
			caso = -1;
		}
		else if (c == '('){
			cout << "'" << c << "' = Paréntesis izquierdo" << endl;
			caso = -1;
		}
		else if (c == ')'){
			cout << "'" << c << "' = Paréntesis derecho" << endl;
			caso = -1;
		}					
		else if (c == '/'){
			caso = 1;
			s+=c;
		}
	}

	void caso1(char c){
		if (c == '/'){
			caso = 2;
			s+=c;
		}
		else {
			cout << "'/' = División" << endl;
			caso = -1;
			resto+=c;
		}
	}

	void caso2(char c){
			s+=c;

	}
	string casos(string input){
		char c;
		caso = 0;
		for (int i = 0; i < input.size(); i++){
			c=input[i];		
			switch(caso){
				case -1: resto +=c; break;
				case 0 : caso0(c); break;
				case 1 : caso1(c); break;
				case 2 : caso2(c); break;
			}
		}
		if (caso == 2){
			cout << "'" << s << "' = Comentario" << endl;
		}
		string r = resto;
		resto = "";
		s = "";
		return r;
	}
};