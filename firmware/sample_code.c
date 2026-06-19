#include <stdio.h>

int main(void)
{
    int motorCurrent = 10;
    int motorTemp = 45;
    int vibration = 20;

    while(1)
    {
        if(motorTemp > 90 || vibration > 80 || motorCurrent > 18)
        {
            //  sample fault condition
        }
        else if(motorTemp > 70 || vibration > 60 || motorCurrent > 15)
        {
            // sample warning condition
        }
        else
        {
            // if its in good condition
        }
    }

    return 0;
}
