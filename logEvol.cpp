#include "evoluzione.h"

int main(int argc, char** argv){
    if(argc != 3) {
        std::cout << "wrong number of arguments. specify number of evolutions and number of evolutions in the same wall"
                  << std::endl;
        return 1;
    }
    Evoluzione evoluzione(100,100,0.6,0.3);
    evoluzione.log(std::atoi(argv[1]), std::atoi(argv[2]));
}
