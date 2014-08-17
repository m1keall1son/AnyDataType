//
//  main.cpp
//  TypecheckedGenericContainer
//
//  Created by Mike Allison on 8/17/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>
#include <vector>
#include "AnyDataType.h"

int main(int argc, const char * argv[])
{
    
    long aLong = 2500000;
    
    std::vector<AnyDataType> stuff;
        
    stuff.push_back(AnyDataType(float(25.5)));
    stuff.push_back(AnyDataType(std::string("hello")));
    stuff.push_back(AnyDataType(&aLong));
    
    stuff[0].as<float>() += 10.f;
    
    std::cout<< stuff[0].as<float>() << std::endl;
    std::cout<< stuff[1].as<std::string>() << std::endl;
    std::cout<< *stuff[2].as<long*>() << std::endl;

    return 0;
    
}

