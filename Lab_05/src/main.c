#include "interface.h"

int main(void)
{
    int mode = 1, rc = 0;
    while (mode)
    {
        printf("Choose mode:\n"
               "1 - Calculate integral\n"
               "2 - Time calculating\n"
               "0 - Exit\n"
               "Choose mode: ");
        rc = scanf("%d", &mode);
        if (rc)
        {
            if (mode == 1)
                show();
            else if (mode == 2)
                calc();
            else
                mode = 0;
        }
        else
            mode = 0;
    }
    printf("Exit succesfully!\n");
    return 0;
}
