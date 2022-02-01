#include <iostream>

using namespace std;

int main()
{
	// ex 6
    int num1, num2, curr_streak = 1, max_streak = 1;
    cin >> num1;
    while(cin >> num2){
        if (num2 > num1)
            curr_streak ++;
        else {
            if (curr_streak > max_streak)
                max_streak = curr_streak;
            curr_streak = 1;
        }
        num1 = num2;
    }
    cout << max_streak << endl;
    return 0;
}
