#ifndef DLIST_H_
#define DLIST_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

template <class T> class Link;
template <class T> class DList;

template <class T> class ListIterator;

template <class T>

class Link {
private:
  Link(T);
  Link(T, Link<T>*);
  Link(const Link<T>&);

  T	    value;
  Link<T> *next;
  Link<T> *prev;

  friend class DList<T>;
  friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) :value(val), next(0), prev(0){}

template <class T>
Link<T>::Link(T val, Link* nxt): value(val), next(next),prev(prev) {}

template <class T>
Link<T>::Link(const Link<T> &source):value(source.value), next(source.next),prev(source.previous) {}
//

template <class T>
class DList{
  private:
    Link <T> *head;
    Link <T> *tail;
    int size;
  public:
    std::string toString() const;
    DList();
    T insertion(T val);
    T search(T val);
    void update(T val, T val2);
    T deleteAt(int val);
    std::string toStringForward();
    std::string toStringBackward();

};

template <class T>
DList<T>::DList():head(NULL),tail(NULL),size(0){}

template <class T>
T DList <T>::insertion(T val){

  Link<T> *newLink = new Link<T>(val);
  if (tail == NULL){
    head = newLink;
    tail = newLink;
  }
  else {
    tail -> next = newLink;
    newLink -> prev = tail;
    tail = newLink;
  }
  size++;
  return val;
}

template <class T>
T DList <T>::search(T val){
  Link<T> *p;
  p = head;
  int cont = 0;
  while (p != 0){
    if(p -> value == val){
      return cont;
    }
    cont++;
    p = p -> next;
  }
  return -1;
}

template <class T>
void DList <T>::update(T val, T val2){
  Link<T> *p;
  p = head;
  int cont = 0;
  while (cont != val){
    p = p -> next;
    cont ++;
  }
  p -> value = val2;
}

template <class T>
T DList <T>::deleteAt(int val){

  Link<T> *p, *q;
  p = head;
  q = NULL;
  T remove;
  int i = 0;
  if(val == 0){
    remove = head -> value;
    p = head;
    head = head -> next;
    if(head != NULL){
      head -> prev = NULL;
    }
    else{
      tail = NULL;
    }
    delete p;
    size--;
    return remove;
  }
  while(p != NULL && i < val){
    q = p;
    p = p -> next;
    i++;
  }
  remove = p -> value;
  q -> next = p -> next;
  if (p -> next != NULL){
    p -> next -> prev = q;
  }
  else{
    tail = q;
  }
  delete p;
  size--;
  return remove;

}

template <class T>
std::string DList<T>::toString() const {
  std::stringstream aux;
  Link<T> *p;

  p = head;
  aux << "[";
  while (p != 0) {
    aux << p->value;
    if (p->next != 0) {
      aux << ", ";
    }
    p = p->next;
  }
  aux << "]";
  return aux.str();
}

template <class T>
std::string DList<T>::toStringForward(){
  std::stringstream aux;
  Link<T> *p;

  p = head;
  aux << "[";
  while (p != 0) {
    aux << p->value;
    if (p->next != 0) {
      aux << ", ";
    }
    p = p->next;
  }
  aux << "]";
  return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward(){
  std::stringstream aux;
  Link<T> *p = tail;
  aux << "[";
  
  while (p != 0) {
    aux << p -> value;
    if (p -> prev!= 0) {
      aux << ", ";
    }
    p = p -> prev;
  }
  
  aux << "]";
  return aux.str();
}

template <class T>
class ListIterator {
public:
  ListIterator(DList<T>*);
  ListIterator(const ListIterator<T>&);

  bool begin();
  bool end();
  T&   operator() () ;
  bool operator++ ();
  void operator= (T) ;

private:
  Link<T> *current;
  Link<T> *previous;
  DList<T> *theList;

  friend class DList<T>;
};

#endif