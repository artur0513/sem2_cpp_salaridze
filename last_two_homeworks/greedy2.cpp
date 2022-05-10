#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ������ ��������� ������� 2

int birds_check(vector<pair<int, int>> &birds, int time){ // ������� ������ � �������� � ��������� ������
    int ans = 0;
    for (int i = 0; i < birds.size(); i++){
        if (birds[i].first <= time && time < birds[i].second){
            ans++;
        }
    }
    return ans;
}

void birds_delete(vector<pair<int, int>> &birds, int time){ // ������ ������ ������������������ � ��������� �����
    for (int i = 0; i < birds.size(); i++){
        if (birds[i].first <= time && time < birds[i].second){
            birds.erase(birds.begin() + i);
            i--;
        }
    }
}

int main()
{
    setlocale(0, "rus");

    int num_of_birds; // ���-�� ������
    vector<pair<int, int>> birds; // ������� ������� � ������ ������

    cin >> num_of_birds; // ������ ���������� ����
    birds.resize(num_of_birds);
    for (int i = 0; i < num_of_birds; i++){
        cin >> birds[i].first >> birds[i].second; // � ����� ������� ������ ��� ������
    }

    //sort(birds.begin(), birds.end(), [](pair<int, int> a, pair<int, int> b) {return a.first < b.first;});

    int birds_left = num_of_birds, photos = 0;
    while (birds_left > 0){
        int max_time = birds[0].first, max_birds = 1;
        for (int time = birds[0].first; time < birds[0].second; time ++){ // ���� ����� ��� ����� ������ �����������
            int curr_birds = birds_check(birds, time);
            if (curr_birds > max_birds){
                max_time = time;
                max_birds = curr_birds;
            }
        }
        birds_delete(birds, max_time);
        photos++;
        cout << "������ ���� �� �����: " << max_time << endl;
        birds_left = birds.size();
    }
    cout << "����� ����: " << photos << endl;
}
