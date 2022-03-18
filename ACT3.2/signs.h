#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <set>
using namespace std;

set<char> alph = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};

set<char> n = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

set<char> sgn = {'+', '-', '=', '*', '/', '^', '(', ')'};


class signs {
private:
	int caso;
	string s;
	string resto;
	string r;

public:
	void caso0(char c){
		if (c == '*'){
			cout << "'" << c << "' = multiplicación" << endl;
			caso = -1;
		}
		else if (c == '^'){
			cout << "'" << c << "' = potencia" << endl;
			caso = -1;
		}
		else if (c == '='){
			cout << "'" << c << "' = asignación" << endl;
			caso = -1;
		}
		else if (c == '('){
			cout << "'" << c << "' = paréntesis que abre" << endl;
			caso = -1;
		}
		else if (c == ')'){
			cout << "'" << c << "' = paréntesis que cierra" << endl;
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
			cout << "'/' = división" << endl;
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
			cout << "'" << s << "' = comentario" << endl;
		}
		string r = resto;
		resto = "";
		s = "";
		return r;
	}
};