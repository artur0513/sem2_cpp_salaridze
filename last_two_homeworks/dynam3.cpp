#include <iostream>
#include <vector>

using namespace std;

// ƒинамическое программирование задание 3

struct GameState{
    unsigned long score0, score1, pos0, pos1, turn;
};

// позици€ от 0 до 10, счет от 0 до 21
unsigned long game_state_id(unsigned long score0, unsigned long score1, unsigned long pos0, unsigned long pos1, unsigned long turn){
    unsigned long id = score0 * 4400;
    id += score1 * 200;
    id += pos0 * 20;
    id += pos1 * 2;
    id += turn;
    return id;
}

unsigned long game_state_id(GameState st){
    return game_state_id(st.score0, st.score1, st.pos0, st.pos1, st.turn);
}

GameState get_state(unsigned long id){
    GameState st;
    st.score0 = id / 4400;
    id %= 4400;
    st.score1 = id / 200;
    id %= 200;
    st.pos0 = id / 20;
    id %= 20;
    st.pos1 = id / 2;
    st.turn = id % 2;
    return st;
}

int main()
{
    setlocale(0, "rus");

    // —осто€ние игры определ€етс€ 5ю параметрами - счет у двух игроков, позици€ у двух и чей сейчас ход
    // счет от 0 до 21 (если больше, то считаем что выиграли и счет = 21)
    // всего тогда состо€ний будет 22*22*10*10*2 = 96800 состо€ний игры
    vector<double> current_states(96800); // id ¬озможных состо€ний игры к некоторому кокретному ходу и количество мультивселенных где они реализованы
    vector<double> previous_states(96800);

    unsigned long start_pos0, start_pos1; // Ќачальные позиции игроков, начинает всегда игрок #0!!!
    cin >> start_pos0 >> start_pos1;

    previous_states[game_state_id(0, 0, start_pos0, start_pos1, 0)] = 1;

    // »де€ така€ - храним массив previous_states с количеством вселенных, где игра находитс€ в указанном состо€нии
    // дл€ каждого состо€ни€ моделируем все возможные случаи выпадени€ кубиков и записываем новые ввселенные в current_states
    // но т.к. в unsigned long не влезает вроде бы (€ пыталс€), то € перешел в double и делаю все то же самое, но на
    // каждом шаге нормирую все на еденицу и получаю сразу веро€тности
    unsigned long longest_game = 0;
    unsigned long not_ended = 100;
    while (not_ended > 0){ // ѕока есть незаконченные игры
        longest_game++;
        not_ended = 0;
        for (unsigned long i = 0; i < 96800; i++){ // проходим по всем ситуаци€м
            if (previous_states[i] == 0) // ≈сли таких ситуаций нет, то идем дальше
                continue;

            GameState st = get_state(i);
            if (st.score0 == 21 || st.score1 == 21){ // »ли если  в этой ситуации игра уже закончилась то веро€тность не мен€етс€
                current_states[i] += previous_states[i];
                continue;
            }

            not_ended++;
            for (unsigned long cube1 = 1; cube1 <= 3; cube1++){ // ѕроходим по всем вариантам выпадени€ кубиков
                for (unsigned long cube2 = 1; cube2 <= 3; cube2++){
                    for (unsigned long cube3 = 1; cube3 <= 3; cube3++){
                        st = get_state(i);
                        if (st.turn == 0){ // просто обновл€ем состо€ние игры
                            st.pos0 += cube1 + cube2 + cube3;
                            st.pos0 %= 10;
                            st.score0 += st.pos0;
                            if (st.score0 > 21)
                                st.score0 = 21;
                            st.turn = 1;
                        }
                        else if (st.turn == 1){
                            st.pos1 += cube1 + cube2 + cube3;
                            st.pos1 %= 10;
                            st.score1 += st.pos1;
                            if (st.score1 > 21)
                                st.score1 = 21;
                            st.turn = 0;
                        }
                        current_states[game_state_id(st)] += previous_states[i];
                    }
                }
            }
        }
        previous_states = current_states;
        double sum_prob = 0.0;
        for (unsigned long i = 0; i < 96800; i++){
            current_states[i] = 0;
            sum_prob += previous_states[i];
        }
        for (unsigned long i = 0; i < 96800; i++){
            previous_states[i] /= sum_prob;
        }
    }

    double first_win = 0, second_win = 0;
    for (unsigned long i = 0; i < 96800; i++){
        GameState st = get_state(i);
        if (st.score0 == 21){
            first_win += previous_states[i];
        }
        if (st.score1 == 21){
            second_win += previous_states[i];
        }
        if (st.score1 == 21 && st.score0 == 21 && previous_states[i] > 0)
            cout << "WTF??" << endl;
    }
    cout << "„исло ходов в самой длинной игре: " << longest_game << endl;
    cout << "Ўанс победы первого : " << first_win << "  ¬торого: " << second_win << endl;
    cout << "—умма шансов побед (дл€ проверки): " << first_win + second_win << endl;
    cout << "соотношение побед: " << float(first_win)/float(second_win) << endl;
}
