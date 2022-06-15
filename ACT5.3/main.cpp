#include <iostream>
#include <string>
#include <fstream>
#include <pthread.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

const int STATE_A = 0;
const int STATE_B = 1;
const int STATE_C = 2;
const int STATE_D = 3;
const int STATE_E = 4;
const int STATE_F = 5;
const int STATE_G = 6;
const int STATE_H = 7;
const int STATE_I = 8;

#include "Comentario.hpp"
#include "Entero.hpp"
#include "Reales.hpp"
#include "Variable.hpp"
#include "String.hpp"
#include "PalabraReservada.hpp"
#include "utils.h"

#define THREADS 2

using namespace std;

string writeTag(string type, string text) {
	return "<span class='" + type + "'>" + text + "</span>";
}

void* lexerAritmetico(string archivo, int start, int limit, char type, int num) {
	string c, str, substring, textoHTML;
	Comentario comentario;
	String tipoString;
	Entero entero;
	Reales real;
	Variable variable;
	PalabraReservada palabraReservada;

	ofstream writeFile;

	if (type == 's'){
		writeFile.open("secuencial.html");
		cout << "Secuencial detectado" << endl;
		writeFile << "<!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Actividad 5.3 - Secuencial</title> <link rel='stylesheet' href='styles.css'> </head> <body>";
	}
	else if (type == 'p'){
		if(num == 0){
			writeFile.open("paralelo1.html");
			cout << "Paralelo 1 detectado" << endl;
			writeFile << "<!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Actividad 5.3 - Paralelo 1</title> <link rel='stylesheet' href='styles.css'> </head> <body>";
		}
		else if(num == 1){
			writeFile.open("paralelo2.html");
			cout << "Paralelo 2 detectado" << endl;
			writeFile << "<!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Actividad 5.3 - Paralelo 2</title> <link rel='stylesheet' href='styles.css'> </head> <body>";
		}
	}

	ifstream readFile;
	readFile.open(archivo);
	int cont = 0;
	while (getline(readFile, str))
	{
		if(cont >= start && cont <= limit){
			writeFile <<  "<br>";
			for (int i = 0; i < str.length(); i++)
			{
				c = str[i];
				substring = str.substr(i);
				if (c == " ") {
					writeFile<< " ";
				}
				else if (c == "\t") {
					writeFile<< "&nbsp;&nbsp;&nbsp;&nbsp";
				}
				else if (tipoString.processEntry(substring) != -1) {
					writeFile<< writeTag("string", substring.substr(0, tipoString.processEntry(substring) + 1));
					i += tipoString.processEntry(substring);
				}
				else if (comentario.processEntry(substring) != -1) {
					writeFile<< writeTag("comentario",substring);
					i += comentario.processEntry(substring);
				}
				else if (palabraReservada.processEntry(substring) != -1) {
					writeFile<< writeTag("palabra-reservada", substring.substr(0, palabraReservada.processEntry(substring) + 1));
					i += palabraReservada.processEntry(substring);
				}
				else if (variable.processEntry(substring) != -1) {
					writeFile<< writeTag("variable", substring.substr(0, variable.processEntry(substring)+1));
					i += variable.processEntry(substring);
				}
				else if (real.processEntry(substring) != -1) {
					writeFile<< writeTag("real", substring.substr(0, real.processEntry(substring)+1));
					i += real.processEntry(substring);
				}
				else if (entero.processEntry(substring) != -1) {
					writeFile<< writeTag("numero", substring.substr(0, entero.processEntry(substring) + 1));
				}
				else if (c == "=") {
					writeFile<< writeTag("operadores",c);
				}
				else if (c == "+"){
					writeFile<< writeTag("operadores",c);
				}
				else if (c == "*") {
					writeFile<< writeTag("operadores",c);
				}
				else if (c == "/"){
					writeFile<< writeTag("operadores",c);
				}
				else if (c == "^") {
					writeFile<< writeTag("operadores",c);
				}
				else if ( c == "-" && str[i+1]==' ' ){
					writeFile<< writeTag("operadores", c);
				}
				else if ( c == "%" ){
					writeFile<< writeTag("operadores",c);
				}
				else if ( c == "(" ){
					writeFile<< writeTag("operadores",c);
				}
				else if ( c == ")" ){
					writeFile<< writeTag("operadores",c);
				}
				else if (c == "'")
				{
					writeFile<< writeTag("operadores", c);
				}
				else if ( c == "," ){
					writeFile<< writeTag("operadores",c);
				}
				else if ( c == "#" ){
					writeFile<< writeTag("operadores",c);
				}
				else if ( c == ";" ){
					writeFile<< writeTag("operadores",c);
				}
				else if (c == "{"){
					writeFile<< writeTag("operadores", c);
				}
				else if ( c == "}" ){
					writeFile<< writeTag("operadores",c);
				}
				else if (c == "["){
					writeFile<< writeTag("operadores", c);
				}
				else if ( c == "]" ){
					writeFile<< writeTag("operadores",c);
				}
				else if ( c == "<" ){
					writeFile<< writeTag("operadores",c);
				}
				else if (c == ">"){
					writeFile<< writeTag("operadores", c);
				}
				else continue;
			}
		}
		cont++;
	}
	return (void*) 0;
}

/*************************************************************
* Concurrent implementation
*************************************************************/
typedef struct{
	int start=0, limit,id;
	string file;
} Block;


void* lexer_paralelo(void* param){
    Block *block;
    block = (Block *) param;
	lexerAritmetico(block->file,block->start,block->limit,'p',block->id);
}

int main(int argc, char* argv[]) {

	string line,line2;
	int numberLines,numberLines2;
	double seq, parallel;
	ofstream writeFilePar, writeFilePar2;
	ifstream file,file2;
	unsigned t0,t1,t2,t3;

	writeFilePar.open("paralelo1.html");
	writeFilePar << "";
	writeFilePar2.open("paralelo2.html");
	writeFilePar2 << "";

	file.open(argv[1]);
	while(getline(file, line)){
		numberLines++;
	}
	file2.open(argv[2]);
	while(getline(file2, line2)){
		numberLines2++;
	}
	int NL[] = {numberLines,numberLines2};

	/*************************************************************
	* Implementacion Secuencial
	*************************************************************/
	cout << endl;
	cout << "Running sequential code..." << endl;
	t0 = clock();
	lexerAritmetico(argv[1],0,NL[0],'s',1);
	t1 = clock();
	double time_secuencial = (double(t1 - t0)/CLOCKS_PER_SEC);
	printf("\tTiempo en secuencial = %lf \n",time_secuencial);
	cout << endl;


	/*************************************************************
	* Implementacion en Paralelo
	*************************************************************/
	cout << "Running parallel code..." << endl;
	
	Block blocks[THREADS];
	pthread_t threads[THREADS];

	for (int i = 0; i < THREADS; i++){
		blocks[i].id = i;
		blocks[i].limit = NL[i];
		blocks[i].file = argv[i+1];
	}

	/*
	for (int i = 0; i < THREADS; i++){
		blocks[i].id = i;
		blocks[i].start = (i * size) + 1;
		blocks[i].limit = (i != THREADS)? ((i + 1) * size) + 1 : argc;
		blocks[i].files = argv;
	}
	*/

	cout << "Bloque: " << blocks[0].id << endl;
	cout << "Start: " << blocks[0].start << endl;
	cout << "Limit: " << blocks[0].limit << endl;
	cout << "Archivo contenido en el bloque: " << blocks[0].file << endl;
	cout << "Bloque: " << blocks[1].id << endl;
	cout << "Start: " << blocks[1].start << endl;
	cout << "Limit: " << blocks[1].limit << endl;
	cout << "Archivo contenido en el bloque: " << blocks[1].file << endl;
	cout << "------------------" << endl;

	t2 = clock();
	for (int i = 0; i < THREADS; i++){
		pthread_create(&threads[i],NULL,lexer_paralelo,(void*) &blocks[i]);
	}
	for (int i = 0; i < THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	t3 = clock();
	double time_paralelo = (double(t3 - t2)/CLOCKS_PER_SEC);
	printf("\tTiempo en paralelo = %lf \n",time_paralelo);

	cout << "Speed up = "<< (double) time_secuencial / (double) time_paralelo *100<< "%"<<endl;
}