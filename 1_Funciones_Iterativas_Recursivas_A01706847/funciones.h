/*

Nombre: Josemaria De Alba
Matricula: A01706847

*/
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;

class Funciones{
public:

long sumaIterativa(int valor){
  long total=0;
  for (int i = 1;i <= valor;i++){
    total += i;
  }
return total;
}

long sumaRecursiva(int valor){
  if (valor == 0)
    return 0;
  else;
    return valor + sumaRecursiva(valor - 1);
}

long sumaDirecta(int valor){
  return (valor * (valor + 1)) / 2;
}

};
#endif