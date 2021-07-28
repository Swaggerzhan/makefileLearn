#include "../include/A.h"
#include <iostream>


A::A()
:   n_(10),
    m_(20)
{}


A::~A(){

}

void A::show(){
    std::cout << n_ << std::endl;
    std::cout << m_ << std::endl;
}