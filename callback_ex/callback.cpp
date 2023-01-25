#include<iostream>
using namespace std;
typedef int (*CallbackType)(int);

int sumCallback(int x){
    return x + x;
}

int squareCallback(int x){
    return x * x;
}

int doMath(int num, CallbackType callback){
    return callback(num);
}

int main()
{
    cout << " Math program: num = 5" << endl;
    cout << " Sum: " << doMath(5, &sumCallback) << endl;
    cout << " Square: " << doMath(5, &squareCallback) << endl;
}