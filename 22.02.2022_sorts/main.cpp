/***
 * Требуется:
 * 1. Реализовать алгоритм медленной сортировки (один из: сортировка выбором, вставками, пузырьком)
 * 2. Реализовать алгоритм быстрой сортировки (сортировка Хоара или сортировка слиянием)
 * 3. Реализовать алгоритмы поиска элемента в отсортированном массиве (тривиальный алгоритм, бинарный поиск)
* Вопросы к заданию:
 * 1. Определить зависимость времени работы медленной сортировки (сортировки выбором) от числа элементов массива
 * 2. Определить зависимость времени работы быстрой сортировки (сортировка Хоара/сортировка слиянием)  от числа элементов массива
 * 3. Определить количество элементов массива при котором медленная сортировка работает быстрее быстрой.
 * 4. Определить зависимость времени работы тривиального поиска от количества элементов массива и количества запросов поиска
 * 5. Определить зависимость времени работы бинарного поиска от количества элементов массива и количества запросов поиска
 * 6. Обменяться кодами быстрой сортировки с одногрупниками, провести исследование времени работы альтернативного алгоритма.
 * 7. Определить диапазоны значений параметра N, для которых тот или иной алгоритм сортировки применим
 * 8. Определите максимальное значение параметра MAX_N (с точностью до десятков тысяч) при котором программа может работать
*/

#include <iostream>
#include <algorithm>
#include "extension.hpp"

using namespace std;

unsigned long long const MAX_N = 100000; //Максимальное количество элементов в массиве

//******************************Поиск элемента в массиве**********************************

//Напишите здесь функцию, которая выполняет поиск заданного элемента в массиве и возвращает его индекс

unsigned long find_element(long vec[], unsigned long N, long request) {
    unsigned int l_c = 0, r_c = N, mid = N/2;

    while (l_c < mid){
        if (request > vec[mid]) {
            l_c = mid;
            mid = (l_c + r_c)/2;
        }
        else if (request < vec[mid]){
            r_c = mid;
            mid = (l_c + r_c)/2;
        }
        else {
            return mid;
        }
    }
    return mid;
}

//***************************************************************************************

// СОРТИРОВКА ПУЗЫРЬКОМ
void bubble_sort(long vec[], unsigned long N) {
    bool is_sort = false;
    int i = 0;
    //long* vec = &f;

    int num_of_operations = 0;

    while (is_sort == false) {
        is_sort = true;
        for (int j = 0; j < N - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
                num_of_operations++;
                is_sort = false;
            }
        }
        i++;
    }
}
// =================

//**********************************Сортировака слиянием*********************************
long merge_temp[MAX_N];
void one_merge(long vec[], unsigned long l, unsigned long r, unsigned long c = 0){
    if (c == 0){
        c = (r+l)/2;
    }
    unsigned long l_c = l;
    unsigned long r_c = c;

    unsigned long i = 0;
    while (l_c < c || r_c < r){
        if ((vec[l_c] < vec[r_c] || r_c == r) && l_c < c){
            merge_temp[i] = vec[l_c];
            l_c++;
        }
        else {
            merge_temp[i] = vec[r_c];
            r_c++;
        }
        i++;
    }
    for (int j = 0; j < i; j++){
        vec[l + j] = merge_temp[j];
    }

}

void merge_sort(long vec[], unsigned long N) {
    unsigned long msize = 2;

    while (msize < N){

        int i = 0;
        while (i < N/msize){
            one_merge(vec, i*msize,(i+1)*msize);
            i++;
        }
        one_merge(vec, (i-1)*msize, N, i*msize);
        msize *= 2;
    }
    one_merge(vec, 0, N, msize/2);

}

//***************************************************************************************

//**********************************Сортировка Хоара*************************************

//Напишите здесь функцию, которая выполняет сортировку Хоара для переданного ей массива (если от вас это требуется)

//***************************************************************************************

void search_test_function(long A[MAX_N], unsigned long N, unsigned long requests_counts){
  Utils util;
  long *requests =new long[requests_counts];
  util.generate_data(requests, requests, requests_counts);

  Timer t; t.start();
  unsigned long misses = 0;
  for (auto i = 0ul; i < requests_counts; ++i){
    unsigned long index = 0;
    index =  find_element(A, N, requests[i]) ;
    if (index >= N){
      ++misses;
    }
    if (index < N && A[index] != requests[i]){
      std::cout << "Fail to search " << requests[i] << ". A[index] == " << A[index] << std::endl;
      return;
    }
  }
  t.stop();

  std::cout << "Processed " << requests_counts << " requests for array size " << N << ". Missed "<< misses
            << " requests. Elapsed time: "
            << t.elapsed() << " microseconds." << std::endl;

  delete[] requests;
}

int main() {
  Utils util;

  long slow_data[MAX_N], rapid_data[MAX_N];

  unsigned long const N = 10000; //Варьируемый параметр. Можно смело изменять для получения зависимости времени от N. N <= MAX_N

  //Генерация N произвольных числе из отрезка [-1000, 1000] в массивы slow_data и rapid_data. slow_data[i] == rapid_data[i]
  util.generate_data(slow_data, rapid_data, N);

  //*****************************Тестирование медленной сортировки******************************************************
  {
    Timer t;
    t.start();

    bubble_sort(slow_data, N);

    t.stop();

    if (!util.check_order(slow_data, N)) {
      std::cout << "Sort order is wrong. Check the sort function." << std::endl;
    } else {
      std::cout << "Performed slow sort of " << N << " elements. Elapsed time: " << t.elapsed() << " microseconds.\n" ;
    }
    std::cout << "First min(" << N << ", 10) elements:\n";
    for (auto i = 0; i < std::min(N, 10ul); ++i)
      std::cout << slow_data[i] << " ";
    std::cout << std::endl;
  }
  //********************************************************************************************************************

  //*****************************Тестирование быстрой сортировки********************************************************
  {
    Timer t;
    t.start();

    merge_sort(rapid_data, N);

    t.stop();

    if (!util.check_order(rapid_data, N)) {
      std::cout << "Sort order is wrong. Check the sort function." << std::endl;
    } else {
      std::cout << "Performed rapid sort of " << N << " elements. Elapsed time: " << t.elapsed() << " microseconds.\n";
    }

    std::cout << "First min(" << N << ", 10) elements:\n";
    for (auto i = 0; i < std::min(N, 10ul); ++i)
      std::cout << rapid_data[i] << " ";
    std::cout << std::endl;
  }
  //********************************************************************************************************************

  //*****************************Тестирование поиска элемента в массиве*************************************************
  unsigned long request_count = 100; //Количество запросов поиска. Можно варьировать в неограниченных (в разумной степени) пределах
  search_test_function(slow_data, N, request_count);
  //********************************************************************************************************************
  return 0;
}
