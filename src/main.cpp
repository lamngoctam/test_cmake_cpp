#include <cassert>

#include "directed_graph/DirectedGraph.hpp"

// test from the `directed graph setup` video
void test_DirectedGraph_setup() {
    DirectedGraph graph;

    std::vector<Vertex*> vs;
    for (int i = 0; i < 4; i++) {
        auto* const v = graph.addVertex(i);
        vs.push_back(v);
    }

    // v0 -> v0
    graph.addEdge(*vs.at(0), *vs.at(0));
    // v0 -> v1
    graph.addEdge(*vs.at(0), *vs.at(1));
    // v0 -> v3
    graph.addEdge(*vs.at(0), *vs.at(3));
    // v2 -> v3
    graph.addEdge(*vs.at(2), *vs.at(3));
    // v2 -> v3
    graph.addEdge(*vs.at(2), *vs.at(3));

    // compare using `DirectedGraph::toString`
    const auto result = graph.toString();
    const auto expected = std::string("DirectedGraph:\n")  //
                          + "  vertices:\n"                //
                          + "    v0\n"                     //
                          + "    v1\n"                     //
                          + "    v2\n"                     //
                          + "    v3\n"                     //
                          + "  edges:\n"                   //
                          + "    v0 -> v0\n"               //
                          + "    v0 -> v1\n"               //
                          + "    v0 -> v3\n"               //
                          + "    v2 -> v3\n";              //

    assert(result == expected);
}

int main(int argc, char** argv) {
    test_DirectedGraph_setup();
    return 0;
}

