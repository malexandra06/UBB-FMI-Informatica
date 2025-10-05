#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct Edge {
    int flow, capacity;
    int x, y;
};

struct Node {
    int h, e_flow;
};

class Graph {
private:
    int V;

    vector<Node> ver;
    vector<Edge> edge;

    bool push(int u);
    void relabel(int u);
    void preflow(int s);
    void updateReverseEdgeFlow(int i, int flow);

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    int getMaxFlow(int s, int t);
};

Graph::Graph(int V) {
    this->V = V;
    for (int i = 0; i < V; i++)
        ver.push_back({ 0, 0 });
}

void Graph::addEdge(int u, int v, int capacity) {
    edge.push_back({ 0, capacity, u, v });
}

void Graph::preflow(int s) {
    ver[s].h = (int)ver.size();

    for (int i = 0; i < edge.size(); i++)
    {
        if (edge[i].x == s)
        {
            edge[i].flow = edge[i].capacity;
            ver[edge[i].y].e_flow += edge[i].flow;
            edge.push_back({ -edge[i].flow, 0, edge[i].y, s });
        }
    }
}

int overFlowVertex(vector<Node>& ver)
{
    for (int i = 1; i < ver.size() - 1; i++)
        if (ver[i].e_flow > 0)
            return i;
    return -1;
}

void Graph::updateReverseEdgeFlow(int i, int flow)
{
    int u = edge[i].y, v = edge[i].x;

    for (int j = 0; j < edge.size(); j++) {
        if (edge[j].y == v && edge[j].x == u) {
            edge[j].flow -= flow;
            return;
        }
    }

    Edge e = { 0, flow, u, v };
    edge.push_back(e);
}

bool Graph::push(int u) {
    for (int i = 0; i < edge.size(); i++) {
        if (edge[i].x == u) {
            if (edge[i].flow == edge[i].capacity) {
                continue;
            }

            if (ver[u].h > ver[edge[i].y].h) {
                int flow = min(edge[i].capacity - edge[i].flow, ver[u].e_flow);
                ver[u].e_flow -= flow;
                ver[edge[i].y].e_flow += flow;
                edge[i].flow += flow;
                updateReverseEdgeFlow(i, flow);
                return true;
            }
        }
    }

    return false;
}

void Graph::relabel(int u) {
    int mh = INT_MAX;

    for (int i = 0; i < edge.size(); i++) {
        if (edge[i].x == u) {
            if (edge[i].flow == edge[i].capacity) {
                continue;
            }

            if (ver[edge[i].y].h < mh) {
                mh = ver[edge[i].y].h;
                ver[u].h = mh + 1;
            }
        }
    }
}

int Graph::getMaxFlow(int s, int t) {
    preflow(s);

    while (overFlowVertex(ver) != -1) {
        int u = overFlowVertex(ver);
        if (!push(u)) {
            relabel(u);
        }
    }

    return ver.back().e_flow;
}

int main(int argc, char* argv[]) {
    int nodes, edges;
    in >> nodes >> edges;

    Graph graph(nodes);

    int x, y, capacity;
    for (int i = 0; i < edges; i++)
    {
        in >> x >> y >> capacity;
        graph.addEdge(x, y, capacity);
    }

    out << graph.getMaxFlow(0, nodes - 1);

    return 0;
}