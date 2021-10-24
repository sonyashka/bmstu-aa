#include "interface.h"

int main(void)
{
    int mode = 1, rc = 0;
    while (mode)
    {
        printf("Choose mode:\n"
               "1 - Calculate editorial distance\n"
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
        }
    }
    printf("Exit succesfully!");
    return 0;
}
