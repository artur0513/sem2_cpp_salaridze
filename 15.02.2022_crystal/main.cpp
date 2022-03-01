#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

class Vec2i{ // ����� ������� � ���� ����� ��� int ������� (����� ����� ������� ������� ���������� ����������)
public:
    int x, y;

    Vec2i(int _x, int _y){
        x = _x;
        y = _y;
    }
};
/*
�������: 1)�������� ����������� ���������� ��������� ����� ������ � �������� � ������ ������� �� ����� �� ����
2) ����� ������ ������ ��� ������� ������� � ������� ��������� � ������������� ����������� ��� ������
*/
class Crystal{ // ��� ����� ��� ����������
public:
    int crystal_size_x, crystal_size_y, number_of_disloc;
    vector<vector<short>> crystal; // ��������� ������ ���������

    vector<Vec2i*> moving_disloc; // ������ ���������� ����������, ������� ����� �������
    vector<Vec2i> disloc; // ���������� ����������

    int turn_num = 0; // ������� �����
    bool process_ended = false; // ���������� �� �������

    Crystal(int _crystal_size_x, int _crystal_size_y, int _number_of_disloc){ // ����������� ������
        crystal_size_x = _crystal_size_x;
        crystal_size_y = _crystal_size_y;
        number_of_disloc = _number_of_disloc;
        for (int i = 0; i < _crystal_size_x; i++){
            crystal.push_back(vector<short>(_crystal_size_y, 0));
        }
        generate_disloc();
    }

    void generate_disloc(){ // ���������� �����(����������)
        int x, y;
        for (int i = 0; i < number_of_disloc; i++){
            do{
                x = rand() % crystal_size_x;
                y = rand() % crystal_size_y;
            } while (crystal[x][y] != 0);
            disloc.push_back(Vec2i(x, y));
            crystal[x][y] = 1;
        }
    }

    void print_crystal(){ // ������� �� ����� �������
        cout << "turn number " << turn_num << endl;
        for (int y = 0; y < crystal_size_y; y++){
            for (int x = 0; x < crystal_size_x; x++){
                cout << crystal[x][y];
            }
            cout << endl;
        }
    }

    bool check_move(int x, int y){ // ���������, �� ������ �� ����(���� �� ��������)
        if (crystal_size_y > 1){
        if(x==0 || x==crystal_size_x-1 || y==0 || y==crystal_size_y-1)
            return false; // ��������� ����� �� �

        if(crystal[x-1][y]==1 || crystal[x+1][y]==1 || crystal[x][y-1]==1 || crystal[x][y+1]==1)
            return false; //���� ����� ������ ������

        return true; //�� ���� ��������� ������� ����� ���������
        }

        else{ // ��������� �������� ��� ����������� ���������
            if(x==0 || x==crystal_size_x-1)
                return false;
            if(crystal[x-1][y]==1 || crystal[x+1][y]==1)
                return false;
            return true;
        }
    }

    void get_moving_dislocs(){ // ���� � ���������� ������ � ������������ ����������, ������� ����� ���������
        for (int i = 0; i < disloc.size(); i++){ // ����� ������� �������� � ������� ���� �� ������� ��������� ������ �� ����� ������������
                int x = disloc[i].x;
                int y = disloc[i].y;
                if (crystal[x][y] == 1 && check_move(x, y)){
                    moving_disloc.push_back(&disloc[i]);
                }

        }
    }

    void move_all_disloc(){ // ������� ��� ����������, ��� ����� ���������
        int dir, x, y;
        for (int i = 0; i < moving_disloc.size(); i++){

            if (crystal_size_y > 1)
                dir = rand()%4;
            else
                dir = rand()%2; // ���� ���������� ��������, �� �������� ������ � ���� ������������

            x = moving_disloc[i]->x;
            y = moving_disloc[i]->y;
            crystal[x][y] = 0;

            if (dir == 0){
                if (crystal[x+1][y] == 1){ // ����� ������������� ��������� �� ������ �� ����, ���� �� ����� �����
                    crystal[x][y] = 1;
                }
                else{
                    crystal[x+1][y] = 1;
                    moving_disloc[i]->x += 1;
                }
            }

            else if (dir == 1){
                if (crystal[x-1][y] == 1){
                    crystal[x][y] = 1;
                }
                else{
                    crystal[x-1][y] = 1;
                    moving_disloc[i]->x -= 1;
                }
            }

            else if (dir == 2){
                if (crystal[x][y+1] == 1){
                    crystal[x][y] = 1;
                }
                else{
                    crystal[x][y+1] = 1;
                    moving_disloc[i]->y += 1;
                }
            }

            else if (dir == 3){
                if (crystal[x][y-1] == 1){
                    crystal[x][y] = 1;
                }
                else{
                    crystal[x][y-1] = 1;
                    moving_disloc[i]->y -= 1;
                }
            }

        }
    }

    bool update(){ // ������� ��� ����������� ������� ������ ����� ������� ���!
        if (!process_ended){
            moving_disloc.clear();
            get_moving_dislocs();
            if (moving_disloc.size() == 0)
                process_ended = true;
            move_all_disloc();
            turn_num++;
            if (turn_num > 200000){ // ��� ����� ��������� ����������� ���������� �����, ���� ���� ���� ������� �����
                process_ended = true;
            }
        }
        return process_ended;
    }

};

float first_task_test(int number_of_tests, int crystal_size , bool third_test = false){ //���� ������� ����� ����� � ��������� � 1 ����������� � ���������� ��������� �������������� �������
    int turn_num = 0;
    int crystal_size_y = crystal_size;
    if (third_test == true){
        crystal_size_y = 1;
    }

    for (int i = 0; i <number_of_tests; i++){
        Crystal test_crystal(crystal_size, crystal_size_y, 1);
        while (test_crystal.update() == false){
            turn_num++;
        }
    }

    float avg = static_cast<float>(turn_num) / static_cast<float>(number_of_tests);
    return avg;
}

void first_task_full_test(bool third_test = false, int min_size = 10, int max_size = 100, int step = 5, int num_of_simulations = 500){ // ������ ���� � ������� �������
    for (int i = min_size; i < max_size; i+=step){
        float x = first_task_test(num_of_simulations, i, third_test);
        cout << x << " " << i << endl;
    }
}

float second_task_test(int number_of_tests, int crystal_size, float koeff, bool third_test = false){ //���� ������� ����� ����� � ��������� � 1 ����������� � ���������� ���������
    int turn_num = 0;
    int crystal_size_y = crystal_size;
    if (third_test == true){
        crystal_size_y = 1;
    }

    for (int i = 0; i <number_of_tests; i++){
        Crystal test_crystal(crystal_size, crystal_size_y, round(koeff*crystal_size*crystal_size_y));
        while (test_crystal.update() == false){
            turn_num++;
        }
    }

    float avg = static_cast<float>(turn_num) / static_cast<float>(number_of_tests);
    return avg;
}

void second_task_full_test(bool third_test = false, float min_percent = 0.02, float max_percent = 0.98, float step = 0.02, int num_of_simulations = 500){
    int crystal_size = 100;
    if (third_test)
        crystal_size = 200;
    for (float i = min_percent; i < max_percent; i+=step){
    cout << i*100  << " " << second_task_test(num_of_simulations, crystal_size, i, third_test) << endl;
    }
}

int main()
{
srand(time(0));

second_task_full_test();
}
