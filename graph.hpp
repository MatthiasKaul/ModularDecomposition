#ifndef DYNGRAPH_HPP
#define DYNGRAPH_HPP

#include <bit>
#include <string>
#include <vector>
#include "log.hpp"


typedef size_t vx;

class Graph{
private:
  vx numVerts;
  vx activeVerts;
  std::vector<vx> contractionSeq;
  std::vector<std::vector<vx>> blackAdj; // blackAdj[i] contains all black neighbours of vertex i, in Order
  std::vector<std::vector<vx>> redAdj;
  std::vector<vx> contractionTargets;
  std::vector<vx> redDegrees;

public:
  Graph() = default;
  ~Graph() = default;
  Graph(vx n);
  std::vector<vx> contractionSequence() const {return contractionSeq;}

  void addBlackEdge(vx v, vx w);
  //void removeBlackEdge(vx v, vx w);
  bool isBlackEdge(vx v, vx w) const;
  void addRedEdge(vx v, vx w);
  //void removeRedEdge(vx v, vx w);
  bool isRedEdge(vx v, vx w) const;
  void inspect() const;
  void contract(vx v, vx w);
  vx redDegree(vx v) const;
  //vx blackDegree(vx v) const;
  vx getNumVertices() const {return activeVerts;}
  vx currentWidth() const;
  vx  resultingWidth(vx v, vx w) const;
  void doBestContraction();
  //void logToFile(std::string fname) const;
  std::vector<size_t> getNeighbours(size_t v) const {return blackAdj[v];}
  std::vector<vx> activeVertices() const;
};

Graph initGraphFromFile(const std::string& fname);
void unpackContractionSequence(std::vector<vx>& cs);
Graph randomGraph(size_t n, size_t m);


#endif /* end of include guard: GRAPH_HPP */
