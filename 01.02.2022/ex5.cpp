#include <iostream>

using namespace std;

int main()
{
    // ex 5
    int curr_num1, min_num1 = 102, ans1=0;
    while(cin >> curr_num1){
        if (curr_num1%101 < min_num1)
            min_num1 = curr_num1%101;
            if (ans1 < curr_num1)
                ans1 = curr_num1;
    }
    cout << ans1 << endl;
    return 0;
}
