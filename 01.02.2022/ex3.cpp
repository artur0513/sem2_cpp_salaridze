#include <iostream>

using namespace std;

int main()
{
    // ex 3
    int x, y, ans=1;
    cin >> x >> y;
    for (int i =0; i<y; i++){
        ans *= x;
    }
    cout << ans << endl;
    return 0;
}
