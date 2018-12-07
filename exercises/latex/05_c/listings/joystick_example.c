#include "init.h"

int main(){
    initBoard();
    while(1) {
        cppp_microDelay();
        delay(1000);
    }
}
