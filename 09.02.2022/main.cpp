#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

bool is_prime(unsigned long long value){
    int max_i = floor(sqrt(value)); // нужно #include <math.h> для перебора до корня
    for (int i = 2; i <= max_i; i++){
        if (value % i == 0){
            return false;
        }
    }
    return true;
}


unsigned long long next_prime(){
    static int counter = 2;
    while (!is_prime(counter)){
        counter++;
    }
    counter ++;
    return counter-1;
}

void reset_prime(){

}

unsigned long long read_int_value(string line){
    string ans_s;
    for(int i = 0; i<line.size(); i++){
        if (46 < line[i] && line[i] < 58){
            ans_s.push_back(line[i]);
        }
    }
    return stoll(ans_s);
}

unsigned long long factorial(int N){
    if (N == 1)
        return 1;
    return N * factorial(N-1);
}

unsigned long long fib(int N){ // недостаточно быстро
    if (N == 1)
        return 1;
    else if (N == 2)
        return 2;
    else
        return fib(N-1) + fib(N-2) ;
}

unsigned long long fast_fib(int N){ // быстрый фиббоначи
    int fib1 = 0, fib2 = 1, fib3 = 1;
    for (int i =0; i < N; i++){
        fib3 = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib3;
    }
    return fib3;
}

void print_binary(unsigned long long value){
    string reverse_ans;
    while (value > 0){
        if (value%2)
            reverse_ans.push_back('1');
        else
            reverse_ans.push_back('0');
        value /= 2;
    }
    for (int i = reverse_ans.size() - 1; i >= 0; i--){
        cout << reverse_ans[i];
    }
}

int read_hex(string hex_str){
    int ans = 0, koeff = 1;
    char c;
    for (int i = hex_str.size()-1; i >= 0; i--){
        c = hex_str[i];
        if (c > 64 && c < 71) // для ввода заглавными буквами
            ans += (c-55)*koeff;
        else if (c > 96 && c < 103) //для ввода маленькими буквами
            ans += (c-87)*koeff;
        else //если попалась циферка
            ans += (c-48)*koeff;
        koeff *= 16;
    }
    return ans;
}

bool check_bracket_sequence(string seq){ // проверить скобочную последовательность
    if (seq.size() == 0)
        return true;
    else if (seq.size() == 1)
        return false;

    int i = 0;
    while(i < seq.size()-2){
        string check = seq.substr(i, 2);
        if (check == "<>" || check == "[]" || check == "{}" || check == "()"){
            seq.erase(i, 2);// если две скобочки ПРАВИЛЬНО стоят рядом, стираем их
            return check_bracket_sequence(seq);
        }
        i++;
    }
    return false;
}

int main()
{

    return 0;
}
