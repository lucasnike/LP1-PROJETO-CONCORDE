
#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <vector>

using namespace std;

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

inline string to_Upper_Case(string text)
{
    for (char &c : text)
	{
		c = std::toupper(c);
	}

    return text;
}

inline string to_Lower_Case(string text)
{
    for (char &c : text)
	{
		c = std::tolower(c);
	}

    return text;
}

#endif