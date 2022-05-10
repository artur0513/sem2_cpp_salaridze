#include <iostream>
#include <vector>

using namespace std;

// ������������ ���������������� ������� 1

int main()
{
    setlocale(0, "rus");

    int num_of_hostels;
    cin >> num_of_hostels;

    vector<int> price(num_of_hostels);
    for (int i = 0; i < num_of_hostels; i++){
        cin >> price[i];
    }

    vector<int> total_price(num_of_hostels);
    vector<int> path(num_of_hostels);
    total_price[0] = price[0];
    total_price[1] = price[1];
    path[0] = -100;
    path[1] = -100;
    for (int i = 2; i < num_of_hostels; i++){
        total_price[i] = min(total_price[i-1], total_price[i-2]) + price[i];
        if (total_price[i-1] < total_price[i-2]){
            path[i] = -1;
        }
        else {
            path[i] = -2;
        }
    }
    // �������� ��� �� � -1 �������, ����������� �� num_of_hostels-1 � �� ���� ������ ����
    cout << "����� ����� ����: " << total_price[num_of_hostels-1] << endl;
    cout << "������ ���������� ��������(��������� � 0): " << endl;
    int i = num_of_hostels-1;
    while (i >= 0){
        cout << i << "  ����: " << price[i] << endl;
        i += path[i];
    }
}
