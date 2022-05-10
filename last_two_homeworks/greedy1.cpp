#include <iostream>
#include <vector>

using namespace std;

// Жадные алгоритмы задание 1

int main()
{
    setlocale(0, "rus");

    int max_fuel; // На одном баке
    int current_fuel;
    int num_of_gas_stations; // Количество заправок
    vector<int> dist; // Расстояния от мск до заправок

    // Начинаем на первой заправке (лучше ввести 0 в начале?)
    // Заканчиваем на последней заправке
    // Считаем что изначально у нас полный бак и можно не заправлятся на первой заправке
    cin >> max_fuel >> num_of_gas_stations;
    dist.resize(num_of_gas_stations);
    for (int i = 0; i < num_of_gas_stations; i++){
        cin >> dist[i];
    }
    current_fuel = max_fuel;

    int current_station = 0, station_counter = 0;

    while (current_station < num_of_gas_stations-1){
        int delta = dist[current_station+1] - dist[current_station];
        if (delta > max_fuel){ // Если до следующей заправки больше чем полный бак
            cout << "не доедем вообще" << endl;
            return 0;
        }
        else if (delta > current_fuel){ // Если до следующей заправки больше чем текущий бак
            station_counter++;
            current_station++;
            cout << dist[current_station-1] << "; "; // Номер станции где остановились
            current_fuel = max_fuel - delta;
        }
        else { // Если можно просто доехать
            current_station++;
            current_fuel -= delta;
        }
    }

    cout << endl << "итого заправок: " << station_counter << endl;
}
