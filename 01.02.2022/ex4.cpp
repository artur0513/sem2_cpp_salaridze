#include <iostream>

using namespace std;

int main()
{
	// ex 4
    int m, min_num, curr_num;
    cin >> m;
    for (int i =0; i<m; i++){
        cin >> curr_num;
        if (i == 0)
            min_num = curr_num;
        else if (curr_num < min_num)
            min_num = curr_num;
    }
    cout << min_num << endl;
	return 0;
}
