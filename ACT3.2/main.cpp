#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <set>

#include <numbers.h>

using namespace std;

set<char> alph = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};

set<char> n = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

set<char> sgn = {'+', '-', '=', '*', '/', '^', '(', ')'};


int main(int argc, char* argv[]) {

	ifstream d;
	string file;
	string input;
	string res;

	//numbers N;
	//var V;
	//signs S;

	cout << "Ingrese el nombre del archivo" << endl;
	cin >> file;

    if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
    }

    lexerAritmetico(argv[1]);
	
	return 0;
}

void lexerAritmetico(string archivo) {
  d.open(file);
	if (d.is_open()){
		while (getline(d, input)){
			while (input != ""){
				char c = input[0];
				if (n.find(c) != n.end() || c == '+' || c == '-' || c == '.'){
					res = N.casos(input);
					input = res;
				}
				else if (alph.find(c) != alph.end()){
					res = V.casos(input);
					input = res;
				}
				else if (sgn.find(c) != sgn.end()){
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