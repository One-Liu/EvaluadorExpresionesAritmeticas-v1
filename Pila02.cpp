#include<iostream>
using namespace std;
#include "Pila.h"

void EvaluarExpresionesAritmeticas(Pila,char[],char[],int,int,int,int,bool);
int SacarOperadores(Pila,char[],int);
void RevisarPila(Pila,char[],int);
void MostrarPostfija(char[],int);

int main() {
	int opc;
	Pila p;
	int tamanio = 20;
	char expresionInfija[tamanio];
	char expresionPostfija[tamanio];
	char caracter;
	do{
		cout<<"Ingrese una opcion:"<<endl;
		cout<<"[1] Inicializar pila"<<endl;
		cout<<"[2] Trabajar postfija y operadores"<<endl;
		cout<<"[3] Salir"<<endl;
		cout<<">";
		cin>>opc;
		switch(opc) {
			case 1:
				p.Inicializar();
				cout<<"Se ha inicializado la pila"<<endl;
				break;
			case 2:
				cout<<"Ingrese una expresion infija: ";
				cin>>expresionInfija;
				EvaluarExpresionesAritmeticas(p,expresionInfija,expresionPostfija,0,0,0,0,false);
				break;
			case 3:
				cout<<"Saliendo del programa..."<<endl;
				break;
			default:
				cout<<"Ingrese una opcion valida!"<<endl;
				break;
		}
		system("pause");
		system("cls");
	}while(opc != 3);
	return 0;
}

void EvaluarExpresionesAritmeticas(Pila p,char expresionInfija[],char expresionPostfija[],int posInfija,int prioridadInfija,int prioridadPila,int posPostfija,bool valorCambiado) {
	if(expresionInfija[posInfija]==NULL) {
		RevisarPila(p,expresionPostfija,posPostfija);
		return;
	}else {
		if(valorCambiado == false) {
			switch(expresionInfija[posInfija]) {
				case '^':
					prioridadInfija = 4;
					valorCambiado = true;
					break;
				case '*':
				case '/':
					prioridadInfija = 2;
					valorCambiado = true;
					break;
				case '-':
				case '+':
					prioridadInfija = 1;
					valorCambiado = true;
					break;
				case '(':
					prioridadInfija = 5;
					valorCambiado = true;
					break;
				case ')':
					posPostfija = SacarOperadores(p,expresionPostfija,posPostfija);
					break;
				default:
					expresionPostfija[posPostfija] = expresionInfija[posInfija];
					++posInfija;
					++posPostfija;
					break;
			}
		}
		
		if(valorCambiado == true) {
			if(p.PilaVacia() == false) {
				if(prioridadInfija > prioridadPila) {
					p.Push(expresionInfija[posInfija]);
					++posInfija;
					valorCambiado = false;
				}
				if(prioridadInfija <= prioridadPila) {
					expresionPostfija[posPostfija] = p.Cima();
					p.Pop();
					++posPostfija;
				}
				
				switch(p.Cima()) {
					case '^':
						prioridadPila = 3;
						break;
					case '*':
					case '/':
						prioridadPila = 2;
						break;
					case '-':
					case '+':
						prioridadPila = 1;
						break;
					case '(':
						prioridadPila = 0;
						break;
				}
			}else {
				p.Push(expresionInfija[posInfija]);
				++posInfija;
				valorCambiado = false;
				
				switch(p.Cima()) {
					case '^':
						prioridadPila = 3;
						break;
					case '*':
					case '/':
						prioridadPila = 2;
						break;
					case '+':
					case '-':
						prioridadPila = 1;
						break;
					case '(':
						prioridadPila = 0;
						break;
				}
			}	
		}
		//Para que no caiga en un bucle si la última posición es un ')'
		//(Puesto que ese case no suma 1 a posInfija y nunca puede salir ya que se queda en la misma posición)
		if(expresionInfija[posInfija+1] == NULL) {
			++posInfija;
		}
		EvaluarExpresionesAritmeticas(p,expresionInfija,expresionPostfija,posInfija,prioridadInfija,prioridadPila,posPostfija,valorCambiado);
	}
}

int SacarOperadores(Pila p, char expresionPostfija[], int pos) {
	if(p.Cima() != '(') {
		p.Pop();
		return pos;
	}else {
		if(p.Cima() != '(' && p.Cima() != ')') {
			expresionPostfija[pos] = p.Cima();
			++pos;
		}
		p.Pop();
		SacarOperadores(p,expresionPostfija,pos);
	}
}

void RevisarPila(Pila p, char expresionPostfija[], int pos) {
	if(p.PilaVacia()) {
		MostrarPostfija(expresionPostfija,0);
		cout<<endl;
		return;
	}else {
		if(p.Cima() != '(' && p.Cima() != ')') {
			expresionPostfija[pos] = p.Cima();
			pos++;
		}
		p.Pop();
		RevisarPila(p,expresionPostfija,pos);
	}
}

void MostrarPostfija(char expresionPostfija[], int cont) {
	if(expresionPostfija[cont] == NULL) {
		return;
	}else {
		cout<<expresionPostfija[cont];
		++cont;
		MostrarPostfija(expresionPostfija,cont);
	}
}
