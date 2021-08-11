#include "../include/A.h"
#include "../include/B.h"
#include "../include/Bind.h"

Bind::Bind(A* a, B* b)
:   a_(a),
    b_(b)
{}


Bind::~Bind(){
    delete a_;
    delete b_;
}


void Bind::show(){
    a_->show();
    b_->show();
}



