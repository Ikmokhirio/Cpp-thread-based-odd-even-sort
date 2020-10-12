#include<iostream>
#include <chrono>
#include <thread>

using namespace std;

void swap(int &a, int &b) {

    int tmp = a;
    a = b;
    b = tmp;

}


void onePass(int *arr, int startPosition, int startLength) {

    for (int i = startPosition; i < startPosition + startLength; i += 2) {

        if (arr[i] > arr[i + 1]) {

            swap(arr[i], arr[i + 1]);

        }

    }

}


void oddEvenSort(int *arr, int length, int threads) {

    auto *threadArr = (thread *) malloc(sizeof(thread) * threads);

    for (int i = 0; i <= length / 2; i++) {

        // ODD
        int newLength = (length / threads);
        for (int j = 0; j < threads; j++) {
            int startPos = (newLength * j) - (newLength * j) % 2;
            if (j == threads - 1) {
                newLength += (length - length % 2) % threads;
            }

            threadArr[j] = thread(onePass, arr, startPos, newLength);

        }

        for (int j = 0; j < threads; j++) threadArr[j].join();

        // EVEN

        newLength = (length - 1) / threads;
        for (int j = 0; j < threads; j++) {
            int startPos = (newLength * j) - (newLength * j) % 2 + 1;
            if (j == threads - 1) {
                newLength += (length - length % 2 - 1) % threads;
            }
            onePass(arr, startPos, newLength);

            threadArr[j] = thread(onePass, arr, startPos, newLength);
        }

        for (int j = 0; j < threads; j++) threadArr[j].join();
    }

}

int *createArray(int size) {
    int *arr = (int *) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {

        arr[i] = rand() % 10000;

    }

    return arr;

}

void printArray(int *arr, int size) {

    for (int i = 0; i < size; i++) {

        cout << "arr[" << i << "] : " << arr[i] << endl;

    }

    cout << endl << endl;

}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "PASS [size] [num_threads]" << endl;
        return 0;
    }
    int n = 0;
    int size = 0;
    srand(time(nullptr));
    try {
        n = stoi(argv[1]);
        size = stoi(argv[2]);
        if (size <= 0) {
            cout << "Size couldn't be negative or zero" << endl;
            return 0;
        }
    } catch (exception e) {
        cout << e.what() << endl;
        return 0;
    }

    int *newArr = createArray(size);

    if (size <= 100) {
        cout << "Source array" << endl;
        printArray(newArr, size);
        cout << endl << endl;
    }

    auto start = chrono::system_clock::now();
    oddEvenSort(newArr, size, n);
    auto end = chrono::system_clock::now();

    if (size <= 100) {
        cout << "Sorted array" << endl;
        printArray(newArr, size);
        cout << endl << endl;
    }


    chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << "s";

    return 0;
}
