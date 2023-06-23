#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <graphviz/cdt.h>
#include <iostream>

char visitado[]="visited";
char verdadeiro[]="true";
char vazio[]="";
char falso[]="false";
char inicio[]="A";
void dfs(Agnode_t* node) {
    agsafeset(node, visitado, verdadeiro, vazio);
    std::cerr<<"Visited node: "<< agnameof(node)<<"\n";

    Agedge_t* edge;
    Agnode_t* neighbor;
    for (edge = agfstedge(agroot(node), node); edge; edge = agnxtedge(agroot(node), edge, node)) {
        neighbor = aghead(edge);
        std::cerr<<"Neighbor name: " <<agnameof(neighbor)<<"\n";
        if (!strcmp(agget(neighbor, visitado), falso)) {
            dfs(neighbor);
        }
    }
}



int main(){
    GVC_t* gvc = gvContext();

    FILE* dotFile = fopen("./teste.dot", "r");
    Agraph_t* graph = agread(dotFile, 0);

    fclose(dotFile);
    
    Agnode_t* startNode = agnode(graph, inicio, 0);
    if (startNode) {
        dfs(startNode);
    }


    gvLayout(gvc, graph, "dot");

    FILE* outputFile = fopen("saida.pdf", "w");
    gvRender(gvc, graph, "pdf", outputFile);
    fclose(outputFile);

    gvFreeLayout(gvc, graph);
    agclose(graph);
    gvFreeContext(gvc);
}