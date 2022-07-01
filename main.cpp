#include <iostream>
#include <chrono>
#include <fstream>
#include <math.h>


class MayRand{
    unsigned long long int seed;
    unsigned long long int seed2;
    int num;
    int den;
    std::ofstream log;
    public:
    float show(){
        std::cout << (float)num / (float)den << std::endl;
    }
    MayRand(){
        log = std::ofstream("res.txt");
        seed = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        seed2 = seed << 32 + seed >> 32;
        num = 0;
        den = 0;
    }
    bool random(){
        unsigned long long int y = ~seed + 1;
        unsigned long long int x = seed;
        
        unsigned long long int xh = x >> 32, xl = x & 0xffffffff;
        unsigned long long int yh = y >> 32, yl = y & 0xffffffff;
        unsigned long long int a = xh * yl, ah = a >> 32, al = a & 0xffffffff;
        unsigned long long int b = xl * yh, bh = b >> 32, bl = b & 0xffffffff;
        unsigned long long int res = ((((xl * yl) >> 32) + al + bl) >> 32) + ah + bh + xh * yh;
        res <<= 2;
        seed = res;
        // float r = 0;
        // float f = 0.5;
        // for(int i = 63;i > 0;i--){
        //     if((seed >> i) % 2 == 1){
        //         r += f;
        //     }
        //     f /= 2;
        // }
        // log << r << std::endl;
        den += 1;
        if(seed == 0){
            seed = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        }
        if(seed >> 63 == 1){
            num += 1;
            return true;
        }else{
            return false;
        }
    }
    float random(int N){
        float res = 0;
        float f = 0.5;
        for(int i = 0;i < N;i++){
            if(random()){
                res += f;
            }
            f /= 2;
        }
        return res;
    }
};

int main(int argc, char **argv){
    if(argc < 2){
        std::cerr << "File path needed" << std::endl;
        exit(-1);
    }
    std::ofstream ofs(argv[1]);
    if(!ofs.is_open()){
        std::cerr << "Error: Cannot open file" << std::endl;
    }

    MayRand m = MayRand();
    int N = 100000;

    int interval = 1000;
    int num = 0;
    int den = 0;
    for(int i = 0;i < N;i++){
        float x = m.random(23);
        float y = m.random(23);
        x = x * 2 - 1;
        y = y * 2 - 1;
        if(std::sqrt(std::pow(x, 2) + std::pow(y, 2)) <= 1){
            num += 1;
        }
        den += 1;
        if(i % interval == interval - 1){
            std::cout << "pi" << std::endl;
            std::cout << i << std::endl;
            std::cout << num * 4 << "/" << den << std::endl;
            m.show();
        }
            ofs << x << "," << y << std::endl;
    }
}