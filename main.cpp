#include "graphs.h"
using namespace std;
vector<char*> s;
int cycle = 0;
int t =0;
void dfs(graphs* w)
{
    w->state = 1;
    w->pre = t++;
    for(graphs* v: w->neighborhood)
    {
        if(v->state == 0)
        {
            dfs(v);
        }

    }
    w->state = 2;
    w->pos = t++;
    s.push_back(w->name);
}
// pre[v] < pre[u] < pos [u] < pos[v]
int detectCycle(vector<graphs>* g)
{
    for(graphs v: *g)
    {
        v.state = 0;
    }
    t = 0;
    for(int i =0; i < (*g).size(); i++)
    {
        if((*g)[i].state == 0 )
        {
            dfs(&(*g)[i]);
        }
    }
    

    for( graphs v: *g)
    {
        for(graphs* w: v.neighborhood)
        {
            if(v.pos < w->pos)
            {
                return 1;
            }
        }
    }

    return 0;
}



int main(int argc, char **argv){
    vector<graphs> g;
    GVC_t* gvc = gvContext();

    FILE* dotFile = stdin;
    
    Agraph_t* graph = agread(dotFile, 0);
    std::fclose(dotFile);

    Agnode_t* v = agfstnode(graph);
    for (int i = 0; i < agnnodes(graph); i++){
        graphs aux;
        strncpy(aux.name,agnameof(v),1024);
        aux.state=0;
        g.push_back(aux);
        v = agnxtnode(graph,v);
    }
    
    for(int i = 0; i < agnnodes(graph); i++){
        for(int j = 0; j < agnnodes(graph); j++){
            if( agedge(graph, agnode(graph, g[i].name, 0), agnode(graph, g[j].name, 0), NULL, 0 ) ){
                g[i].neighborhood.push_back(&g[j]);
            }
        }
    }

    agclose(graph);
    gvFreeContext(gvc);



    if(detectCycle(&g) == 1){
        cout << "Grafo não é um DAG\n";
        exit(1);
    }
    else{
        for(int i = s.size()-1; i >= 0; i--)
        {
            if(i == 0)
            {
                cout << s[i];
            }
            else
            {
                cout << s[i] << " ";

            }
        }
    }


    return 0;


}
