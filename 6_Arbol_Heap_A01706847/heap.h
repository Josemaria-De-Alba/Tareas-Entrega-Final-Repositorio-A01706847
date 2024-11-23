#ifndef HEAP_H_
#define HEAP_H_
/*

Nombre: Josemaria De Alba
Matricula: A01706847

*/
#include <string>
#include <sstream>
#include <iostream>

template <class T>
class Heap {
private:
  T *data;
  unsigned int sizes;
  unsigned int count;

  unsigned int parent(unsigned int) const;
  unsigned int left(unsigned int) const;
  unsigned int right(unsigned int) const;
  void heapify(unsigned int);
  void swap(unsigned int, unsigned int);

public:
  Heap(unsigned int) ;
  ~Heap();
  bool empty() const;
  bool full() const;
  void add(T) ;
  T remove() ;
  void clear();
  std::string toString() const;
  T push(T val);
  T pop();
  T size();
  T top();
};

template <class T>
Heap<T>::Heap(unsigned int sze)  {
  sizes = sze;
  data = new T[sizes];
  count = 0;
}

template <class T>
Heap<T>::~Heap() {
  delete [] data;
  count = 0;
  sizes = 0;
  data = 0;
}

template <class T>
bool Heap<T>::empty() const {
  return (count == 0);
}

template <class T>
bool Heap<T>::full() const {
  return (count == sizes);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
  return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
  return ((pos * 2) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
  return ((pos * 2) + 2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
  T aux = data[i];
  data[i] = data[j];
  data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
  unsigned int le = left(pos);
  unsigned int ri = right(pos);
  unsigned int min = pos;
  if(le <= count && data[le] < data[min]){
    min = le;
  }
  if(ri <= count && data[ri] < data[min]){
    min = ri;
  }
  if(min != pos){
    swap(pos,min);
    heapify(min);
  }
}

template <class T>
void Heap<T>::add(T val)  {
  unsigned int pos;
  
  pos = count;
  count++;
  while(pos > 0 && val < data[parent(pos)]){
    data[pos] = data[parent(pos)];
    pos = parent(pos);
  }
  data[pos] = val;
}

template <class T>
T Heap<T>::remove()  {
  T aux = data[0];

  data[0] = data[--count];
  heapify(0);
  return aux;
}

template <class T>
void Heap<T>::clear() {
  count = 0;
}


template <class T>
std::string Heap<T>::toString() const {
  std::stringstream aux;

  aux << "[";
  for (unsigned int i = 0; i < count; i++) {
    if (i != 0) {
      aux << " ";
    }
    aux << data[i];
  }
  aux << "]";
  return aux.str();
}

template <class T>
T Heap<T>::push(T val){
  unsigned int pos;

  pos = count;
  count++;
  while(pos > 0 && val < data[parent(pos)]){
    data[pos] = data[parent(pos)];
    pos = parent(pos);
  }
  data[pos] = val;
  return val;
}

template <class T>
T Heap<T>::pop(){
  T aux = data[0];

  data[0] = data[--count];
  heapify(0);
  return aux;
}

template <class T>
T Heap<T>::size(){
  return count;
}

template <class T>
T Heap<T>::top(){
  return data[0];
}


#endif
