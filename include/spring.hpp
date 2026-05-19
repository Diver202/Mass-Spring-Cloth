#pragma once

class Spring{
    public:
        int indexA;
        int indexB;
        float restLength;
        float springConstant;

        Spring(int a, int b, float length, float stiffness);
};