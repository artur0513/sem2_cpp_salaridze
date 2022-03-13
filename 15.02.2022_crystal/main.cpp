#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

class Vec2i{ // самый простой в мире класс для int вектора (нужен чтобы удобнее хранить координаты дислокаций)
public:
    int x, y;

    Vec2i(int _x, int _y){
        x = _x;
        y = _y;
    }
};
/*
доп задание: 1)добавить возможность дислокации пролетать через стенки и вылетать с другой стороны по одной из осей
2) снять больше тестов для второго задания с разными размерами и лианеризовать зависимость как нибудь
*/
class Crystal{ // сам класс для кристаллов
public:
    int crystal_size_x, crystal_size_y, number_of_disloc;
    vector<vector<short>> crystal; // двумерный массив кристалла

    vector<Vec2i*> moving_disloc; // ссылки координаты дислокаций, которые можно двигать
    vector<Vec2i> disloc; // координаты дислокаций

    int turn_num = 0; // счетчик ходов
    bool process_ended = false; // закончился ли процесс

    bool x_loop;

    // Размеры X, Y кристала, количество дислокаций, будет ли дислокация появлятся с другой стороны если перешла с края
    Crystal(int _crystal_size_x, int _crystal_size_y, int _number_of_disloc, bool _x_loop = false){ // конструктор класса
        crystal_size_x = _crystal_size_x;
        crystal_size_y = _crystal_size_y;
        number_of_disloc = _number_of_disloc;
        x_loop = _x_loop;
        for (int i = 0; i < _crystal_size_x; i++){
            crystal.push_back(vector<short>(_crystal_size_y, 0));
        }
        generate_disloc();
    }

    void generate_disloc(){ // генерируем атомы(дислокации)
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

    void print_crystal(){ // выводим на экран кристал
        cout << "turn number " << turn_num << endl;
        for (int y = 0; y < crystal_size_y; y++){
            for (int x = 0; x < crystal_size_x; x++){
                cout << crystal[x][y];
            }
            cout << endl;
        }
        /*cout << "dislocs " << endl;
        for (int i = 0; i < disloc.size(); i++){
            cout << disloc[i].x << " " << disloc[i].y << endl;
        }*/
    }

    bool check_move(int x, int y){ // проверяем, не слипся ли атом(есть ли соседнии)
        if (crystal_size_y > 1 && !x_loop){
            if(y==0 || y==crystal_size_y-1 || x==0 || x==crystal_size_x-1)
                return false; // проверяем стоим ли у

            if(crystal[x-1][y]==1 || crystal[x+1][y]==1 || crystal[x][y-1]==1 || crystal[x][y+1]==1)
                return false; //если рядом другая клетка

            return true; //во всех остальных случаях можем двигаться
        }
        else if (x_loop){
            if(y==0 || y==crystal_size_y-1)
                return false; // проверяем стоим ли у

            if (crystal[x][y-1]==1 || crystal[x][y+1]==1)
                return false;

            if (x != 0 && x != crystal_size_x - 1){
                if(crystal[x-1][y]==1 || crystal[x+1][y]==1)
                    return false; //если рядом другая клетка
            }
            else if (x == 0 && (crystal[crystal_size_x - 1][y]==1 || crystal[1][y] == 1)){
                return false;
            }
            else if (x == crystal_size_x-1 && (crystal[0][y]==1 || crystal[x-1][y] == 1)){
                return false;
            }

            return true; //во всех остальных случаях можем двигаться
        }
        else{ // отдельная проверка для одномерного кристалла
            if(x==0 || x==crystal_size_x-1)
                return false;
            if(crystal[x-1][y]==1 || crystal[x+1][y]==1)
                return false;
            return true;
        }
    }

    void get_moving_dislocs(){ // ищем и составляем массив с координатами дислокаций, которые будут дивгаться
        for (int i = 0; i < disloc.size(); i++){
                int x = disloc[i].x;
                int y = disloc[i].y;
                if (check_move(x, y)){
                    moving_disloc.push_back(&disloc[i]);
                }

        }
    }

    void move_all_disloc(){ // двигаем все дислокации, что нужно подвинуть
        int dir, x, y;
        for (int i = 0; i < moving_disloc.size(); i++){

            if (crystal_size_y > 1)
                dir = rand()%4;
            else
                dir = rand()%2; // если одномерный кристалл, то движемся только в двух направлениях

            x = moving_disloc[i]->x;
            y = moving_disloc[i]->y;
            crystal[x][y] = 0;

            if (dir == 0){
                cout << crystal_size_x << endl;
                if (x_loop && x == crystal_size_x - 1){
                    if (crystal[0][y] == 1){ // здесь дополнительно проверяем не заняли ли блок, куда мы хотим пойти
                        crystal[x][y] = 1;
                    }
                    else{
                        crystal[0][y] = 1;
                        moving_disloc[i]->x = 0;
                    }
                }
                else{
                    if (crystal[x+1][y] == 1){ // здесь дополнительно проверяем не заняли ли блок, куда мы хотим пойти
                        crystal[x][y] = 1;
                    }
                    else{
                        crystal[x+1][y] = 1;
                        moving_disloc[i]->x += 1;
                    }
                }
            }

            else if (dir == 1){
                if (x_loop && x == 0){
                    if (crystal[crystal_size_x - 1][y] == 1){
                        crystal[x][y] = 1;
                    }
                    else{
                        crystal[crystal_size_x - 1][y] = 1;
                        moving_disloc[i]->x = crystal_size_x - 1;
                    }
                }
                else {
                    if (crystal[x-1][y] == 1){
                        crystal[x][y] = 1;
                    }
                    else{
                        crystal[x-1][y] = 1;
                        moving_disloc[i]->x -= 1;
                    }
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

    bool update(){ // собрали все необходимые функции вместе чтобы сделать ход!
        if (!process_ended){
            moving_disloc.clear();
            get_moving_dislocs();
            if (moving_disloc.size() == 0)
                process_ended = true;
            move_all_disloc();
            turn_num++;
            if (turn_num > 200000){ // Тут можно поставить ограничение количество ходов, если тест идет слишком долго
                process_ended = true;
            }
        }
        return process_ended;
    }

};

float first_task_test(int number_of_tests, int crystal_size , bool third_test = false){ //тест среднее число ходов в симуляции с 1 дислокацией и квадратном кристалле фиксированного размера
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

void first_task_full_test(bool third_test = false, int min_size = 10, int max_size = 100, int step = 5, int num_of_simulations = 500){ // полный тест к первому заданию
    for (int i = min_size; i < max_size; i+=step){
        float x = first_task_test(num_of_simulations, i, third_test);
        cout << x << " " << i << endl;
    }
}

float second_task_test(int number_of_tests, int crystal_size, float koeff, bool third_test = false){ //тест среднее число ходов в симуляции с 1 дислокацией и квадратном кристалле
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
    int crystal_size = 150;
    if (third_test)
        crystal_size = 200;
    for (float i = min_percent; i < max_percent; i+=step){
    cout << i*100  << " " << second_task_test(num_of_simulations, crystal_size, i, third_test) << endl;
    }
}

int main()
{
srand(time(0));

Crystal test(5, 10, 1, true);
while(!test.process_ended)
{
    test.print_crystal();
    test.update();
}
}
