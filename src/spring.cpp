#include "../include/spring.hpp"

Spring::Spring(int a, int b, float length, float stiffness){
    indexA = a;
    indexB = b;
    restLength = length;
    springConstant = stiffness;
}