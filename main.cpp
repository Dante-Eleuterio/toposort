#include "graphs.h"
using namespace std;

int main(){
    vector<graphs> g;
    GVC_t* gvc = gvContext();
    char filename[1024];
    cin>>filename;
    FILE* dotFile = fopen(filename, "r");
    if (!dotFile){
        std::cerr<<"File not found\n";
        exit(1);
    }

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
                g[i].neighborhood.push_back(g[j]);
            }
        }
    }

    for(int i = 0; i < agnnodes(graph); i++){
        for(int j = 0; j < g[i].neighborhood.size(); j++){
            std::cerr<<g[i].name<<"->"<<g[i].neighborhood[j].name<<"\n";
        }
    }




    gvLayout(gvc, graph, "dot");

    FILE* outputFile = fopen("saida.pdf", "w");
    gvRender(gvc, graph, "pdf", outputFile);
    fclose(outputFile);

    gvFreeLayout(gvc, graph);
    agclose(graph);
    gvFreeContext(gvc);
}