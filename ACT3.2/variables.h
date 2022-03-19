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

class variables {		//para identificar variables

public:

	public:
	
	int caso;
	string v;
	string resto;
	string r;

	void inicio(char c){
		if (alpha.find(c) != alpha.end()){
			caso = 1;
			v+=c;
		}
		else {
			cout << "'" << c << "' = Valor no reconocido" << endl;
			resto +=c;
			caso = -1;
		}
	}
	void caso1(char c){
		if (alpha.find(c) != alpha.end() || num.find(c) != num.end()){
			v+=c;
		}
		else {
			caso = -1;
			cout << "'" << v << "' = Variable" << endl;
			resto +=c;
		}
	}
	string casos(string input){
		char c;
		caso = 0;
		for (int i = 0; i < input.size(); i++){
			c=input[i];
			switch(caso){
				case -1: resto+=c; break;
		        case 0 : inicio(c); break;
		        case 1 : caso1(c); break;
		    }
		}
		if (caso != -1){
			cout << "'" << v << "' = variable" << endl;
		}
		r = resto;
		resto = "";
		v = "";
		return r;		
	}
};