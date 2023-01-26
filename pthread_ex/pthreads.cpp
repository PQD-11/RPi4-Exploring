#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

void *threadFunct(void *value)
{
    int *x = (int *)value;
    while ((*x) < 5)
    {
        usleep(10);
        (*x)++;
    }
    return x;
}

int main(){
    int x = 0, y = 0;
    pthread_t thread;
    if (pthread_create(&thread, NULL, &threadFunct, &x) != 0)
    {
        cout << "Failed to create the thread" << endl;
        return 1;
    }

    while (y < 5)
    {
        cout << "The value of x = " << x << " and y = " << y++ << endl;
        usleep(10);  
    }
    pthread_join(thread, NULL);
    cout << "Final: x = " << x << " y = " << y << endl;
    return 0;
}