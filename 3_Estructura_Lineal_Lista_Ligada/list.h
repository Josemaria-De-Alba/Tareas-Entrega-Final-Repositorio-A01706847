/*

Nombre: Josemaria De Alba
Matricula: A01706847

*/

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>


template <class T> class Link;
template <class T> class List;

template <class T> class ListIterator;

template <class T>

class Link {
private:
  Link(T);
  Link(T, Link<T>*);
  Link(const Link<T>&);

  T	    value;
  Link<T> *next;

  friend class List<T>;
  friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) :value(val), next(0){}

template <class T>
Link<T>::Link(T val, Link* nxt): value(val), next(next) {}

template <class T>
Link<T>::Link(const Link<T> &source):value(source.value), next(source.next) {}
//

template <class T>
class List{
  private:
    Link <T> *head;
    int size;
  public:
    std::string toString() const;
    List();
    T insertion(T val);
    T search(T val);
    void update(T val, T val2);
    void deleteAt(int val);
    
};

template <class T>
List<T>::List():head(0), size(0){}

template <class T>
T List <T>::insertion(T val){
  
  Link<T> *newLink;
  newLink = new Link<T>(val);
  if (head == NULL){
    head = newLink;
  }
  else {
    Link<T> *p = head;
    while (p->next != 0){
      p = p->next;
    }
    p->next=newLink;
    size++;
  }
  return val;
}

template <class T>
T List <T>::search(T val){
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
void List <T>::update(T val, T val2){
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
void List <T>::deleteAt(int val){

  if (val > size || val < 0){
    return;
  }
  
  Link<T> *p, *q;
  p = head;
  q = p -> next;
  if(val == 0){
    head = q;
    delete p;
    return;
  }
  int cont = 1;
  while (cont != val){
    p = p -> next;
    q = q -> next;
    cont ++;
  }
  p -> next = q -> next;
  delete q;
  return;
  
}

template <class T>
std::string List<T>::toString() const {
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
class ListIterator {
public:
  ListIterator(List<T>*);
  ListIterator(const ListIterator<T>&);

  bool begin();
  bool end();
  T&   operator() () ;
  bool operator++ ();
  void operator= (T) ;

private:
  Link<T> *current;
  Link<T> *previous;
  List<T> *theList;

  friend class List<T>;
};


#endif