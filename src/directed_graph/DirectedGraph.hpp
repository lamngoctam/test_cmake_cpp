#pragma once

#include <memory>  // `std::unique_ptr`
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// # Properties
//
// 2. each vertex has a unique id, and an associated data (int)
//
// # Example Usage
//
// ```cpp
// auto u = Vertex(2, 5);
// u.setData(5);
// ```
class Vertex {
   public:
    //
    Vertex(const size_t id, const int data);

    //
    size_t getID() const;

    //
    int getData() const;
    void setData(const int data);

    //
    std::string toString() const;

    // # Returns
    //
    // `true` if `this` and `that` has the same id
    bool operator==(const Vertex& that) const;

   private:
    size_t m_id = 0;
    int m_data = 0;
};

// # Properties
//
// 1. for any pair of vertices `u` and `v`, there can be at most 1 edge pointing from `u` to `v`
//     1. essentially `u` cannot have multiple edges pointing to `v`
//     2. in other words, this graph is NOT a multigraph
// 2. each vertex has a unique id, and an associated data (int)
// 3. edges are unweighted, and have no data associated with them
//
// # Required Methods
//
// 1. add a vertex
// 2. add an edge
// 3. remove a vertex
//      - removes the vertex
//      - removes all edges pointing to the vertex
//      - removes all edges pointing from the vertex
// 4. remove an edge
// 5. get all vertices
// 6. get all vertices that some vertex points to
// 7. get a string representation of the graph
//      - must be deterministic; same result regardless when you run the program
class DirectedGraph {
   public:
    //
    DirectedGraph();

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
    //
    // # Complexity
    //
    // `O(1)`
    Vertex* addVertex(const int data);

    // adds an edge from `u` to `v`
    //
    // `u` and `v` must exist in this graph
    //
    // if the edge `u -> v` exists, the graph will not be modified and `false` is returned
    // otherwise, the edge will be added and `true` is returned
    //
    // # Complexity
    //
    // `O(1)`
    bool addEdge(Vertex& u, Vertex& v);

    // remove `u`
    //
    // if `u` exists in this graph, removes `u` and returns `true`
    // otherwise nothing happens and returns `false`
    //
    // 3. remove a vertex
    //      - removes the vertex
    //      - removes all edges pointing to the vertex
    //      - removes all edges pointing from the vertex
    //
    // # Complexity
    //
    // `O(n)`
    bool removeVertex(Vertex& u);

    // remove an edge that points from `u` to `v`
    //
    // if this edge exists, remove it and return `true`
    // nothing happens and returns `false` otherwise
    // 4. remove an edge
    //
    // # Complexity
    //
    // `O(1)`
    bool removeEdge(Vertex& u, Vertex& v);

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
    //
    // # Complexity
    //
    // `O(n)`
    std::vector<Vertex*> getVertices();
    std::vector<const Vertex*> getVertices() const;

    // return all vertices that `u` points to
    //
    // 6. get all vertices that some vertex points to
    //
    // # Complexity
    //
    // `O(n)`
    std::vector<Vertex*> getSuccessors(Vertex& u);
    std::vector<const Vertex*> getSuccessors(Vertex& u) const;

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
    //
    // # Complexity
    //
    // `O(v log v)`
    std::string toString() const;

   private:
    // 1. some vertex counter to make sure each one gets a unique id
    size_t m_vertexCounter = 0;
    // 1. container of all vertices in this graph
    std::unordered_map<const Vertex*, std::unique_ptr<Vertex>> m_vertices;
    // 1. container for all edges in this graph
    std::unordered_map<const Vertex*, std::unordered_set<Vertex*>> m_edges;
};
