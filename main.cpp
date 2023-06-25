#include "graphs.h"
using namespace std;
vector<char*> s;
int cycle = 0;
void dfs(graphs* w)
{
    w->state = 1;
    for(graphs* v: w->neighborhood)
    {
        if(v->state == 0)
        {
            dfs(v);
        }

        else if(v->state == 1)
        {
            cycle = 1;
        }
    }
    w->state = 2;
    s.push_back(w->name);
}

int detectCycle(vector<graphs>* g)
{
    for(graphs v: *g)
    {
        v.state = 0;
    }

    for(int i =0; i < (*g).size(); i++)
    {
        if((*g)[i].state == 0 )
        {
            dfs(&(*g)[i]);

            if(cycle)
            {
                return 1;
            }
        }
    }
    return 0;
}

void topoSort(graphs* w)
{
    w->state = 1;

    for(graphs* v: w->neighborhood)
    {
        if(v->state == 0)
        {
            topoSort(v);
        }
    }
    // char aux[1024];
    // strncpy(aux,w->name,1024);
    // s.push(aux);
    w->state = 2;
}

void sort(vector<graphs> *g)
{
    for(graphs v: *g)
    {
        v.state = 0;
    }

    for( graphs v: *g)
    {
        if(v.state == 0)
        {
            topoSort(&v);
        }
    }

    // for(graphs v: *g)
    // {
    //     cout << v.state << "\n";
    // }
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
