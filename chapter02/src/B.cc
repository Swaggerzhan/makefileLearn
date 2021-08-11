#include "../include/B.h"
#include <iostream>



B::B()
:   n_(-1),
    m_(-2)
{

}

B::~B(){

}

void B::show(){
    std::cout << n_ << std::endl;
    std::cout << m_ << std::endl;
}