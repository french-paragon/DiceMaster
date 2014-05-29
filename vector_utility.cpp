#include <vector>

using namespace std;

template<class T>
T sum(vector<T> v){

    T s(0);

    for(typename vector<T>::iterator it = v.begin(); it != v.end(); ++it)
        s += *it;

    return s;
}
