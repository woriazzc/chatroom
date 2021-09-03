#include "./utils.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void itoa(int num, char *dest){
    sprintf(dest, "%d", num);
}