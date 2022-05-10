#include <iostream>
#include <vector>

using namespace std;

// ������ ��������� ������� 3

int main()
{
    setlocale(0, "rus");

    int money; // ������� ����� ���������
    cin >> money;

    const int coins_num = 5;
    int coins[coins_num] = {1, 2, 5, 7, 10}; // ���� ������ �� ������� ������
    vector<int> min_coins; // ����������� ���������� ����� ����� ��������� ����� �� 0 �� money
    min_coins.resize(money+1);
    min_coins[0] = 0;

    for (int i = 1; i < money+1; i++){
        int current_min = 2147483647;
        for (int j = 0; j < coins_num; j++){
            if (i - coins[j] < 0)
                continue;

            if (min_coins[i - coins[j]] < current_min){
                current_min = min_coins[i - coins[j]];
            }
        }
        min_coins[i] = current_min + 1;
    }
    cout << "����� �����: " << min_coins[money] << endl;
}
