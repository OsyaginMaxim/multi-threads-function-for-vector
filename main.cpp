#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <iterator>
#include <functional>
#include <algorithm>
#include <random>

std::mutex mut;

//template<class T>
class SimpleFunctor {
public:
    SimpleFunctor(){};
    void operator()(int& n) {
        n = n * n * n;
    }
};


template <class Iter, class Func>
void myVecFunc(Iter begin, Iter end, const int& num, Func func){
    std::vector<std::thread> threads(num);
    for(int i = 0; i < num; i++) {
        threads[i] = std::thread([&begin, end, &func](){
            Iter it;
            while(begin != end) {
                {
                    std::lock_guard<std::mutex> lockMut(mut);
                    it = begin;
                    begin++;
                }
                func(*it);
                /*std::thread::id my_ID = std::this_thread::get_id();
                std::cout<< my_ID << "hello" <<std::endl;*/
            }
        });

    }
    for(int i = 0; i < num; i++){
        if(threads[i].joinable()) {
            threads[i].join();
        }
    }
}

//template<class T>
void foo(int& n){
    n = n * n;
}



int main() {
    SimpleFunctor f;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 8);
    std::uniform_real_distribution<> dist2(10,20);
    int size = 10;
    int countOfThread = 4;
    std::vector<int> vector1(size);
    for(int i = 0; i < size; i++){
        vector1[i] = dist(gen);
    }
    std::vector<double> vector2(size);
    for(auto& v : vector2){
        v = dist2(gen);
    }
    for(auto& v : vector1){
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;



    myVecFunc( vector1.begin(), vector1.end(),countOfThread, [](int& n ){
        n++;
        std::cout<< std::to_string(n) + " ";
    });
    std::cout<<std::endl;
    for(auto& v : vector2){
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;
    myVecFunc( vector2.begin(),vector2.end(), countOfThread, [](double& n){
        n--;
        std::cout<< std::to_string(n) + " ";
    });
    std::cout<<std::endl;
    myVecFunc( vector1.begin(), vector1.end(),countOfThread, foo);
    std::cout<<std::endl;
    for(auto& v : vector1){
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;
    myVecFunc( vector1.begin(), vector1.end(),countOfThread, f);
    std::cout<<std::endl;
    for(auto& v : vector1){
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;



    return 0;
}

