#include <vector>

using namespace std;

template<class C>
C sum(vector<C> v){

    C s(0);

    for(typename vector<C>::iterator it = v.begin(); it != v.end(); ++it)
        s += *it;

    return s;
}
