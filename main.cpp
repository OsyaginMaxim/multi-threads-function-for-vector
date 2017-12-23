#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <iterator>
#include <functional>
#include <algorithm>

std::mutex mut;

template <class Iter, class Func>
void myVecFunc(Iter begin, Iter end, const int& num, Func func){
    std::vector<std::thread> threads(num);
    for(int i = 0; i < num; i++) {
        threads[i] = std::thread([&begin, end, func](){
            int j;
            Iter it;
            while(begin != end){
                {
                    std::lock_guard<std::mutex> lockMut(mut);
                    it = begin;
                    begin++;
                }
                func(*it);
            }

        });

    }
    for(int i = 0; i < num; i++){
        threads[i].join();
    }
}




int main() { //int argc, char* argv[]
   // int size = atoi(argv[1]);
   // int countOfThread = atoi(argv[2]);
    int size = 5;
    int countOfThread = 3;
    std::vector<int> vector1(size);
    for(int i = 0; i < size; i++){
        vector1[i] = i;
    }
    std::vector<double> vector2(size);
    myVecFunc( vector1.begin(), vector1.end(),countOfThread, [](int& n ){
        n++;
        std::cout<< std::to_string(n) + "\n";
    });

    return 0;
}

