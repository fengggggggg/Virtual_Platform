//
//  main.cpp
//  C++ program
//
//  Created by Feng on 2019/5/8.
//  Copyright © 2019 Feng. All rights reserved.
//

#include <stdio.h>
#include <string.h>

void fun1()
{
    int m = 10;
    char num[4];
    strcpy(num, "bbbbbbbbbbbbb\x0F\x10\x40\x00");
}

void fun2()
{
    printf("Yor were attacked.\n");
}

int main()
{
    fun1();
    return 0;
}
