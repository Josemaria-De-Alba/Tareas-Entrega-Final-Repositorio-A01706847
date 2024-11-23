/*

Nombre: Josemaria De Alba
Matricula: A01706847

*/
#ifndef SORTS_H_
#define SORTS_H_
#include <vector>
#include <list>

template <class T>
class Sorts{
  private:
    void swap(std::vector<T> &v, int i, int j){
      T aux = v[i];
      v[i] = v[j];
      v[j] = aux;
    }

    void copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high){
      for (int i = low; i <= high; i++) {
        A[i] = B[i];
      }
    }
  
    void mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high){
      int i, j, k;
      i = low;
      j = mid + 1;
      k = low;

      while (i<=mid && j<=high){
        if (A[i] < A[j]){
          B[k] = A[i];
          i++;
        }
        else{
          B[k] = A[j];
          j++;
        }
        k++;
      }
      if (i > mid){
        for(; j <= high; j++){
          B[k++] = A[j];
        }
      }
      else{
        for(; i <= mid; i++){
          B[k++] = A[i];
        }
      }
    }
  
    void mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high){
      int mid;

      if((high - low < 1)){
        return;
      }

      mid=(high + low)/2;
      mergeSplit(A, B, low, mid);
      mergeSplit(A, B, mid + 1, high);
      mergeArray(A, B, low, mid, high);
      copyArray(A, B, low, high);
    }
public:
    std::vector<T> ordenaSeleccion(std::vector<T> &v) {
      int spot;
      for(int i = v.size() - 1; i > 0; i--){
        spot = i;
        for (int j = 0; j < i; j++){
          if (v[spot] < v[j]){
            spot = j;
          }
        }
        swap(v, i, spot);	

      }
      return v;
    }

    std::vector<T> ordenaBurbuja(std::vector<T> &v) {
      
      for (int i = v.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
          if (v[j] > v[j + 1]) {
            swap(v, j, j + 1);
          }
        }
      }
      return v;
    }

    std::vector<T> ordenaMerge(std::vector<T> &v) {
      std::vector<T> tmp(v.size());
      
      mergeSplit(v, tmp, 0, v.size() - 1);
      return v;
    }


    int busqSecuencial(const std::vector<T> &v, int num){
      for (int i=0; i < v.size(); i++){
        if (v[i] ==num){
          return i;
        }
      }
      return -1;
    }

    int busqBinaria(const std::vector<T> &v, int num){
      int low = 0;
      int high = v.size() - 1;
      int mid;
      while (low < high){
        mid = (low + high) / 2;
        if(v[mid] == num){
          return mid;
        }
        else if(v[mid] < num){
          low = mid + 1;
        }
        else{
          high = mid - 1;
        }
      }
    return -1;
    }

    std::list<T>   mergeList(const std::list<T> &lst1, const std::list<T> &lst2) {
  typename std::list<T>::const_iterator itr1, itr2;
  std::list<T> result;

  return result;
}
};

  #endif