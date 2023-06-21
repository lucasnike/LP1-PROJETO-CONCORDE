
#include <iostream>
#include <vector>

using namespace std;

#pragma once

template<typename T>
bool find_element(vector<T> vetor, T search)
{
    bool found = false;
    for(T item : vetor)
    {
        if (item == search)
        {
            return true;
        }
    }

    return false;
}