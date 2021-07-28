#include "include/Bind.h"
#include "include/A.h"
#include "include/B.h"

int main(int argc, char** args){

    A* a = new A();
    B* b = new B();

    Bind* target = new Bind(a, b);
    target->show();

    return 0;

} 