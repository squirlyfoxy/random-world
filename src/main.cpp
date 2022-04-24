#include "./win/window.h"

#include "t.h"

int main() {
    if (NewWindow(1280, 720, "GAME") == -1) {
        return FAIL;
    }
    EnterLoop();

    return SUCCESS;
}