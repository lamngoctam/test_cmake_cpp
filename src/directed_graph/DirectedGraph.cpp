#include "DirectedGraph.hpp"

#include <algorithm>  // `std::sort`
#include <cassert>    // `assert`
#include <iostream>

//
Vertex::Vertex(const size_t id, const int data)  //
    : m_id(id),                                  //
      m_data(data) {
    //
}

//
size_t Vertex::getID() const {
    //
    return m_id;
}

//
int Vertex::getData() const {
    //
    return m_data;
}
void Vertex::setData(const int data) {
    //
    this->m_data = data;
}

//
std::string Vertex::toString() const {
    // v1, v2, and etc
    return "v" + std::to_string(m_id);
}

// # Returns
//
// `true` if `this` and `that` has the same id
bool Vertex::operator==(const Vertex& that) const {
    //
    return this->getID() == that.getID();
}

//
DirectedGraph::DirectedGraph()  //
    : m_vertexCounter(0),       //
      m_vertices(),             //
      m_edges() {
    //
}

// creates and adds a vertex to this graph
//
// the created vertex is guaranteed to have a unique id
//
// # Example Usage
//
// ```cpp
// DirectedGraph dg;
//
// auto* v1 = dg.addVertex(data_1);
// auto* v2 = dg.addVertex(data_2);
//
// ```
Vertex* DirectedGraph::addVertex(const int data) {
    //
    // 1. create a new vertex
    //    - make sure it has a unique id
    auto vertex = std::make_unique<Vertex>(m_vertexCounter, data);
    m_vertexCounter++;  // the next vertex will have a different id

    //
    auto* const rawPointer = vertex.get();

    // 1. add it to the graph
    m_vertices.emplace(rawPointer, std::move(vertex));
    // 1. return the pointer to the created vertex
    return rawPointer;
}

// adds an edge from `u` to `v`
//
// `u` and `v` must exist in this graph
//
// if the edge `u -> v` exists, the graph will not be modified and `false` is returned
// otherwise, the edge will be added and `true` is returned
bool DirectedGraph::addEdge(Vertex& u, Vertex& v) {
    // 1. check that both vertices exist in the graph
    assert(m_vertices.find(&u) != m_vertices.end());
    assert(m_vertices.find(&v) != m_vertices.end());

    // vertices that `u` points to
    auto& uSuccessors = m_edges[&u];
    // 1. if the edge `u -> v` exists, return false and do nothing
    if (uSuccessors.find(&v) != uSuccessors.end()) {
        return false;
    } else {
        // 1. if the edge `u -> v` does not exist, add it and return true
        uSuccessors.insert(&v);
        return true;
    }
}

// remove `u`
//
// if `u` exists in this graph, removes `u` and returns `true`
// otherwise nothing happens and returns `false`
//
// 3. remove a vertex
//      - removes the vertex
//      - removes all edges pointing to the vertex
//      - removes all edges pointing from the vertex
bool DirectedGraph::removeVertex(Vertex& u) {
    // if `u` exists
    if (m_vertices.find(&u) != m_vertices.end()) {
        //      - removes the vertex
        m_vertices.erase(&u);
        //      - removes all edges pointing from the vertex
        m_edges.erase(&u);
        //      - removes all edges pointing to the vertex
        for (auto& kvPair : m_edges) {
            // vertices that some vertex points to
            auto& successors = kvPair.second;

            // remove `u` from this set
            if (successors.find(&u) != successors.end()) {
                successors.erase(&u);
            }
        }
        return true;

    } else {
        // `u` does not exist, so do nothing
        return false;
    }
}

// remove an edge that points from `u` to `v`
//
// if this edge exists, remove it and return `true`
// nothing happens and returns `false` otherwise
// 4. remove an edge
bool DirectedGraph::removeEdge(Vertex& u, Vertex& v) {
    // if u and v exists
    if (m_vertices.find(&u) != m_vertices.end()  //
        && m_vertices.find(&v) != m_vertices.end()) {
        //
        auto& uSuccessors = m_edges[&u];
        //   if u -> v exists
        if (uSuccessors.find(&v) != uSuccessors.end()) {
            uSuccessors.erase(&v);
            return true;
        } else {
            return false;
        }

    } else {
        return false;
    }
}

// 5. get all vertices
//
// # Example Usage
// ```cpp
// void handle_v1(DirectedGraph& dg) {
//     auto vertices = dg.getVertices();
//     // modify vertices is `vertices`
// }
// void handle_v2(const DirectedGraph& dg) {
//     auto vertices = dg.getVertices();
//     // CANNOT modify vertices is `vertices`
// }
// ```
std::vector<Vertex*> DirectedGraph::getVertices() {
    // copy the vertices to a vector, return it
    std::vector<Vertex*> vertices;
    vertices.reserve(m_vertices.size());

    for (auto& kvPair : m_vertices) {
        vertices.push_back(kvPair.second.get());
    }

    return vertices;
}
std::vector<const Vertex*> DirectedGraph::getVertices() const {
    //
    std::vector<const Vertex*> vertices;
    vertices.reserve(m_vertices.size());

    for (auto& kvPair : m_vertices) {
        vertices.push_back(kvPair.first);
    }

    return vertices;
}

// return all vertices that `u` points to
//
// 6. get all vertices that some vertex points to
std::vector<Vertex*> DirectedGraph::getSuccessors(Vertex& u) {
    //
    auto& uSuccessors = m_edges[&u];

    //
    return std::vector<Vertex*>(  //
        uSuccessors.begin(),      //
        uSuccessors.end()         //
    );
}
std::vector<const Vertex*> DirectedGraph::getSuccessors(Vertex& u) const {
    if (m_edges.find(&u) != m_edges.end()) {
        //
        auto& uSuccessors = m_edges.at(&u);

        //
        return std::vector<const Vertex*>(  //
            uSuccessors.begin(),            //
            uSuccessors.end()               //
        );
    } else {
        return {};
    }
}

template <class InputIter>
std::vector<const Vertex*> toSortedVertices(const InputIter vertexBegin,
                                            const InputIter vertexEnd) {
    std::vector<const Vertex*> sortedVs(vertexBegin, vertexEnd);
    std::sort(             //
        sortedVs.begin(),  //
        sortedVs.end(),    //
        [&](const auto* const lhs, const auto* const rhs) { return lhs->getID() < rhs->getID(); });

    return sortedVs;
}

// 7. get a string representation of the graph
//      - must be deterministic; same result regardless when you run the program
//
// # Returns
//
// a string that shows all vertices and edges, in sorted order
//
// DirectedGraph:
//   vertices:
//     v0
//     v1
//     v2
//   edges:
//     v0 -> v1
//     v0 -> v2
//     v1 -> v2
std::string DirectedGraph::toString() const {
    //
    std::string s = "DirectedGraph:\n";

    s += "  vertices:\n";

    // vertices in sorted order
    const auto vertices = getVertices();
    const auto sortedVertices = toSortedVertices(vertices.begin(), vertices.end());
    //
    for (const auto* const v : sortedVertices) {
        s += "    " + v->toString() + "\n";
    }

    s += "  edges:\n";

    // for each u in sorted vertices
    for (const auto* const u : sortedVertices) {
        //     sort its successors, and print the edges
        if (m_edges.find(u) != m_edges.end()) {
            const auto& uSuccessors = m_edges.at(u);
            const auto uSuccessorsSorted = toSortedVertices(uSuccessors.begin(), uSuccessors.end());

            for (const auto* const v : uSuccessorsSorted) {
                //
                s += "    " + u->toString() + " -> " + v->toString() + "\n";
            }
        } else {
            // do nothing becasue `u` has no successors
        }
    }

    //
    return s;
}
