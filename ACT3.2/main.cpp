#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <set>

#include "numbers.h"
#include "signs.h"
#include "variables.h"

using namespace std;

int main(int argc, char* argv[]) {

	ifstream d;
	string file;
	string input;
	string res;

	numbers N;
	variables V;
	signs S;

	cout << "Ingrese el nombre del archivo:" << endl;
	cin >> file;

    if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
    }

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
	return 0;
}