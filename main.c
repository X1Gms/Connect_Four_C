#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./headers/types.h"
#include "./src/menu.c"
#include "./src/gameplay.c"
#include "./src/match_status.c"
#include "./src/ranking.c"
#include "./src/save_load.c"

int main()
{
    /* Semente para números aleatórios */
    srand(time(NULL));
    executeOption();
    return 0;
}
