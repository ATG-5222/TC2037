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

//Hola

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

	//cout << "Lexer con el bloque: " << num << " de tipo: " << type << endl;

	if (type == 's'){
		writeFile.open("secuencial.html");
		cout << "Secuencial detectado" << endl;
	}
	else if (type == 'p'){
		if(num == 1){
			writeFile.open("paralelo1.html");
			cout << "Paralelo 1 detectado" << endl;
		}
		else if(num == 2){
			writeFile.open("paralelo2.html");
			cout << "Paralelo 2 detectado" << endl;
		}
	}

	writeFile << "<!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Actividad 5.3</title> <link rel='stylesheet' href='styles.css'> </head> <body>";

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
	int start, limit,id;
	string file;
} Block;


void* task(void* param){
    Block *block;
    block = (Block *) param;
	//cout << "Trabajando con el thread: " << block->id << endl;
	//cout << "Verificacion de hilos de trabajo" << endl;
	/*for (int i = 0; i < 2; i++) {
		cout << "id: " << block[i].id << endl;
		lexerAritmetico(block[i].file, block[i].start, block[i].limit,'p',block[i].id);
	}*/
	/*
	for (int i = block->start; i < block->end; i++) {
		lexerAritmetico(block->files[i], 'p', block[i].id);
	}
	*/
	lexerAritmetico(block->file,block->start,(block->limit)-1,'p',block->id);
    //return ((void*)lexerAritmetico(block->file, block->start, block->limit,'p',block->id));
}


int main(int argc, char* argv[]) {

	string line, result = "<!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Actividad 3.4 Paulina</title> <link rel='stylesheet' href='styles.css'> </head> <body>", text = "";
	int numberLines,numberLines2;
	double seq, parallel;
	ofstream writeFilePar, writeFilePar2;

	writeFilePar.open("paralelo1.html");
	writeFilePar << "";
	writeFilePar2.open("paralelo2.html");
	writeFilePar2 << "";

	ifstream file;
	file.open(argv[1]);
	while (getline(file, line)){
		numberLines++;
	}
	ifstream file2;
	file2.open(argv[2]);
	while (getline(file2, line)){
		numberLines2++;
	}
	int NL[] = {numberLines,numberLines2};

	/*************************************************************
	* Implementacion Secuencial
	*************************************************************/
	cout << endl;
	cout << "Running sequential code..." << endl;
	start_timer();
	lexerAritmetico(argv[1],0,NL[0]-1,'s',1);
	seq = stop_timer();
	printf("\tTiempo en secuencial = %lf \n",seq);
	cout << endl;


	/*************************************************************
	* Implementacion en Paralelo
	*************************************************************/
	cout << "Running parallel code..." << endl;
	
	Block blocks[THREADS];
	pthread_t threads[THREADS];
	/*long jump = numberLines / THREADS; //Aqui inicia el comentario: size = (argc - 1) / THREADS; */

	for (int i = 0; i < THREADS; i++){
		blocks[i].id = i;
		blocks[i].start = 0;
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
	cout << "Archivo contenido en el bloque: " << blocks[0].file << endl;
	cout << "Bloque: " << blocks[1].id << endl;
	cout << "Archivo contenido en el bloque: " << blocks[1].file << endl;
	cout << "------------------" << endl;

	start_timer();
	for (int i = 0; i < THREADS; i++){
		pthread_create(&threads[i],NULL, task,(void*) &blocks[i]);
	}
	for (int i = 0; i < THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	parallel = stop_timer();

	cout << "\tTiempo paralelo = " << parallel << endl;
	cout << "Speed up = " << (float) seq / (float) parallel*100 << "%" << endl;
}