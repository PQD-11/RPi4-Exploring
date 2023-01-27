#include<pthread.h>
#include<stdio.h>
#include<iostream>
#include<chrono>
#include<thread>

using namespace std;

#define NUM_RAND 5000000

void *threadFunct(void *){
    unsigned rand_seed = 0; 
    for (int i = 0; i < NUM_RAND; i++){
        rand_r(&rand_seed);
    }
    return 0;
}

void random_generate_no_threads(int numCalls){
    for(int i = 0; i < numCalls; i++){
        threadFunct(0);
    }
}

void random_generate_with_threads(int numCalls){
    pthread_t *threads[numCalls];
    for (int i = 0; i < numCalls; i++){
        threads[i] = new pthread_t;
    }
    pthread_attr_t *attr = new pthread_attr_t;
    pthread_attr_init(attr);
    for (int i =  0; i < numCalls; i++){
        pthread_create(threads[i], attr, threadFunct, 0);
    }
    for (int i = 0; i < numCalls; i++){
        pthread_join(*threads[i],0);
    }

    pthread_attr_destroy(attr);
    for (int i = 0; i < numCalls; i++){
        delete threads[i];
    }
    delete attr;
}

int main(int argc, char *argv[]){
    int numCalls = 1;
    if (argc == 2){
        int passed = atoi(argv[1]);
        if (passed == 0){
            cout << "Invalid number passed to the program -- exiting!" << endl;
            return -EINVAL;
        }
        else {
            numCalls = passed;
        }
    }

    unsigned int numThreads = thread::hardware_concurrency();
    cout << "This hardware supports " << numThreads << " concurrent threads."<< endl;
    auto begin = chrono::high_resolution_clock::now();
    random_generate_no_threads(numCalls);
    auto end = chrono::high_resolution_clock::now();
    cout << "Real Time: No threads " << chrono::duration_cast<chrono::microseconds>(end-begin).count() << endl;

    begin = chrono::high_resolution_clock::now();
    random_generate_with_threads(numCalls);
    end = chrono::high_resolution_clock::now();
    cout << "Real Time: With threads " << chrono::duration_cast<chrono::microseconds>(end-begin).count() << endl;
    return 0;
}