#include <iostream>
#include <vector>

using namespace std;

// ������ ��������� ������� 1

int main()
{
    setlocale(0, "rus");

    int max_fuel; // �� ����� ����
    int current_fuel;
    int num_of_gas_stations; // ���������� ��������
    vector<int> dist; // ���������� �� ��� �� ��������

    // �������� �� ������ �������� (����� ������ 0 � ������?)
    // ����������� �� ��������� ��������
    // ������� ��� ���������� � ��� ������ ��� � ����� �� ����������� �� ������ ��������
    cin >> max_fuel >> num_of_gas_stations;
    dist.resize(num_of_gas_stations);
    for (int i = 0; i < num_of_gas_stations; i++){
        cin >> dist[i];
    }
    current_fuel = max_fuel;

    int current_station = 0, station_counter = 0;

    while (current_station < num_of_gas_stations-1){
        int delta = dist[current_station+1] - dist[current_station];
        if (delta > max_fuel){ // ���� �� ��������� �������� ������ ��� ������ ���
            cout << "�� ������ ������" << endl;
            return 0;
        }
        else if (delta > current_fuel){ // ���� �� ��������� �������� ������ ��� ������� ���
            station_counter++;
            current_station++;
            cout << dist[current_station-1] << "; "; // ����� ������� ��� ������������
            current_fuel = max_fuel - delta;
        }
        else { // ���� ����� ������ �������
            current_station++;
            current_fuel -= delta;
        }
    }

    cout << endl << "����� ��������: " << station_counter << endl;
}
