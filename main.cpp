#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <iterator>
#include <functional>

template <class T>
std::vector<T> myVecFunc(std::vector<T> vector, std::iterator begin, std::iterator end, int num, std::function func){
   //create num threads
   //they take elem of vector and call func
}


int main(int argc, char* argv[]) {
    int size = atoi(argv[1]);
    int countOfThread = atoi(argv[2]);
    std::vector<int> vector1(size) ;
    std::vector<double> vector2(size);
    std::vector<std::string> vector3(size);
    auto start;
    auto endv;
    myVecFunc(vector1, start = begin(vector1),endv = end(vector1),countOfThread, [](){
        //doing something
    });

    return 0;
}