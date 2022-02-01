#include <iostream>

using namespace std;

int main()
{
	// ex 2
    int n;
    cin >> n;
    if (n%5 == 0){
        for (int i =0; i<n; i++){
            cout << "@";
        }
    }
    else{
        for (int i =0; i<n; i++){
            cout << "%";
        }
    }

    cout << endl;
    return 0;
}
