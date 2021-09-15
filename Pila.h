#include <cstddef>

class Pila {
	private:
		int cima;
		int fondo = -1;
		int tope;
		char array[20];
		
		bool PilaLlena() {
			if(cima <= tope) {
				return false;
			}else {
				return true; //Si la pila esta llena regresa true, si no, regresa false
			}
		}
		
	public:
		//El método PilaVacía se hizo público para poder ser capaces de saber si la Pila está vacía directamente
		bool PilaVacia() {
			if(cima-1 == fondo) {
				return true; //Si la pila esta vacía regresa true, si no, regresa false
			}else {
				return false;
			}
		}
		
		void Inicializar() { //Sirve para inicializar los contadores y topes
			cima = 0;
			tope = (SizePila()) - 1;
			return;
		}
		
		int Push(char dato) {
			if(!PilaLlena()) {
				array[cima] = dato; 
				++cima;
				return 0; //Se insertó el elemento
			}else {
				return -1; //Indica que la pila está llena
			}
		}
		
		int Pop() {
			if(!PilaVacia()) {
				array[cima-1] = NULL;
				--cima;
				return 0; //Elemento eliminado correctamente
			}else {
				return -1; //Indica que la pila está vacía
			}
		}
		
		//Se modificó el tipo del método a char para que regresara el caracter que se encuentra en la cima del array
		//Se usa el método PilaVacía antes de llamar a este método
		char Cima() {
			return array[cima-1]; //Valor de la cima
		}
		
		void LimpiarPila() {
			if(PilaVacia()) {
				Inicializar();
				return;
			}else {
				Pop();
				LimpiarPila();
			}
			//Eliminar todos los elementos de la pila
		}
		
		int SizePila() {
			return sizeof(array)/sizeof(*array); //Devolverá el tamaño de la pila declarada
		}
};
