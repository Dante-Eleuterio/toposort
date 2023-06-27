#include <bits/stdc++.h>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <graphviz/cdt.h>
using namespace std;

class graphs{
    public:
        char name[1024];
        int state;
        int pre;
        int pos;
        vector<graphs*> neighborhood;
};