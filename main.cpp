#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <iterator>
#include <functional>
#include <algorithm>
#include <random>

std::mutex mut;

class MyFunctor {
public:
    MyFunctor(){};
    void operator()(int& n) {
        n = n * n * n;
    }
};

void foo(int& n){
    n = n * n;
}


template <class Iter, class Func>
void myVecFunc(Iter begin, Iter end, const int& num, Func func){
    std::vector<std::thread> threads(num);
    for(int i = 0; i < num; i++) {
        threads[i] = std::thread([&begin, end, &func](){
            Iter it;
            int n = 10;
            while(begin != end) {
                {
                    std::lock_guard<std::mutex> lockMut(mut);
                    it = begin;
                    begin += n;
                }
                for(int j = 0; j < n; j++, it++) {
                    func(*it);
                }
            }
        });

    }
    for(int i = 0; i < num; i++){
        if(threads[i].joinable()) {
            threads[i].join();
        }
    }
}




int main() {
    MyFunctor f;
    std::random_device rd;
    std::mt19937 gen(3);
    std::uniform_int_distribution<> dist(1, 8);
    std::uniform_real_distribution<> dist2(10,20);
    int size = 30;
    int countOfThread = 10;
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
    int tmp1;
    for( auto& v: vector1){
        tmp1 += v;
    }
    std::cout<< tmp1<<std::endl;

    myVecFunc( vector1.begin(), vector1.end(),countOfThread, [](int& n ){
        n++;
        std::cout<< std::to_string(n) + " ";
    });
    int tmp;
    for( auto& v: vector1){
        tmp += v;
    }
    std::cout<<"\n"  + std::to_string(tmp)<<std::endl;

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

