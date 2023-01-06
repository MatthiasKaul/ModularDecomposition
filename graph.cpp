#include "graph.hpp"
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
auto findItem(const std::vector<vx>& vec, vx item){
  return std::lower_bound(vec.begin(), vec.end(), item);
}

std::vector<vx> unify(const std::vector<vx>& v1, const std::vector<vx>& v2, std::vector<vx>& degrees, const std::vector<vx>& labels ){
  std::vector<vx> rval;
  auto i1 = v1.begin();
  auto i2 = v2.begin();
  while(i1 != v1.end() && i2 != v2.end()){
    if(*i1 < *i2){if(labels[*i1] == *i1) rval.push_back(*i1); i1++;continue;}
    if(*i2 < *i1){if(labels[*i2] == *i2) rval.push_back(*i2); i2++;continue;}
    if(*i2 == *i1){if(labels[*i1] == *i1) {rval.push_back(*i1); degrees[*i1]--;} i1++; i2++; }
  }
  while(i1 != v1.end()){
    if(labels[*i1] == *i1) rval.push_back(*i1); i1++;
  }
  while(i2 != v2.end()){
    if(labels[*i2] == *i2) rval.push_back(*i2); i2++;
  }
  return rval;
}

std::vector<vx> unify(const std::vector<vx>& v1, const std::vector<vx>& v2, const std::vector<vx>& labels ){
  std::vector<vx> rval;
  auto i1 = v1.begin();
  auto i2 = v2.begin();
  while(i1 != v1.end() && i2 != v2.end()){
    if(*i1 < *i2){if(labels[*i1] == *i1) rval.push_back(*i1); i1++;continue;}
    if(*i2 < *i1){if(labels[*i2] == *i2) rval.push_back(*i2); i2++;continue;}
    if(*i2 == *i1){if(labels[*i1] == *i1) {rval.push_back(*i1);} i1++; i2++; }
  }
  while(i1 != v1.end()){
    if(labels[*i1] == *i1) rval.push_back(*i1); i1++;
  }
  while(i2 != v2.end()){
    if(labels[*i2] == *i2) rval.push_back(*i2); i2++;
  }
  return rval;
}

std::vector<vx> intersect(const std::vector<vx>& v1, const std::vector<vx>& v2, const std::vector<vx>& labels ){
  std::vector<vx> rval;
  auto i1 = v1.begin();
  auto i2 = v2.begin();
  while(i1 != v1.end() && i2 != v2.end()){
    if(*i1 < *i2){i1++;continue;}
    if(*i2 < *i1){i2++;continue;}
    if(*i2 == *i1){if(labels[*i1] == *i1) {rval.push_back(*i1);} i1++; i2++; }
  }

  return rval;
}

std::vector<vx> setSub(const std::vector<vx>& base, const std::vector<vx>& subtract, const std::vector<vx>& labels  ){
  std::vector<vx> rval;
  auto i1 = base.begin();
  auto i2 = subtract.begin();
  while(i1 != base.end() && i2 != subtract.end()){
    if(labels[*i1] != *i1){i1++; continue;}
    if(labels[*i2] != *i2){i2++; continue;}

    if(*i1 < *i2){rval.push_back(*i1); i1++; continue;}
    if(*i2 < *i1){i2++; continue;}
    if(*i2 == *i1){i1++; i2++; }
  }
  while(i1 != base.end()){
    if(labels[*i1] == *i1) rval.push_back(*i1); i1++;
  }
  return rval;
}

std::pair<std::vector<vx>, std::vector<vx>> partition(const std::vector<vx>& v1, const std::vector<vx>& v2, const std::vector<vx>& labels){
  std::vector<vx> intersect;
  std::vector<vx> symDiff;

  auto i1 = v1.begin();
  auto i2 = v2.begin();
  while(i1 != v1.end() && i2 != v2.end()){
    if(labels[*i1] != *i1){i1++; continue;}
    if(labels[*i2] != *i2){i2++; continue;}
    if(*i1 < *i2){symDiff.push_back(*i1); i1++; continue;}
    if(*i2 < *i1){symDiff.push_back(*i2); i2++;continue;}
    if(*i2 == *i1){intersect.push_back(*i1); i1++; i2++;continue;}
  }
  while(i1 != v1.end()){
    if(labels[*i1] == *i1) symDiff.push_back(*i1); i1++;
  }
  while(i2 != v2.end()){
    if(labels[*i2] == *i2) symDiff.push_back(*i2); i2++;
  }

  return {intersect, symDiff};
}

void Graph::inspect() const{
  auto vs = activeVertices();
  for(auto x : vs){
    std::cout << x <<" : ";
    for(auto y : blackAdj[x]) std::cout << y << " ";
    std::cout << "\n";
  }
}

Graph::Graph(vx n){
  numVerts = n;
  activeVerts = n;
  blackAdj = std::vector< std::vector<vx> >(n);
  redAdj = std::vector< std::vector<vx> >(n);

  contractionTargets = std::vector<vx>(n);
  for (size_t i = 0; i < n; i++) {
    contractionTargets[i] = i;
  }
  redDegrees = std::vector<vx>(n, 0);

}

void Graph::addBlackEdge(vx v, vx w){
  if(contractionTargets[v] != v || contractionTargets[w] != w) return;
  auto insertLocation = findItem(blackAdj[v], w);
  if(insertLocation == blackAdj[v].end() || *insertLocation != w) //Edge not present
    blackAdj[v].insert(insertLocation, w); //Inefficient, but given the input format probably fine.

  insertLocation = findItem(blackAdj[w], v);
  if(insertLocation == blackAdj[w].end() || *insertLocation != v)
    blackAdj[w].insert(insertLocation, v);
}

void Graph::addRedEdge(vx v, vx w){
  if(contractionTargets[v] != v || contractionTargets[w] != w) return;
  auto insertLocation = findItem(redAdj[v], w);
  if(insertLocation == redAdj[v].end() || *insertLocation != w) //Edge present
    redAdj[v].insert(insertLocation, w);

  insertLocation = findItem(redAdj[w], v);
  if(insertLocation == redAdj[w].end() || *insertLocation != v)
    redAdj[w].insert(insertLocation, v); //Inefficient, but given the input format probably fine.
}

bool Graph::isBlackEdge(vx v, vx w) const {
  if(contractionTargets[v] != v || contractionTargets[w] != w) return false;
  if(isRedEdge(v,w)) {return false;}
  auto loc = findItem(blackAdj[v], w);
  return loc != blackAdj[v].end() && *loc == w;
}

bool Graph::isRedEdge(vx v, vx w) const{
  if(contractionTargets[v] != v || contractionTargets[w] != w) return false;
  auto loc = findItem(redAdj[v], w);

  return loc != redAdj[v].end() && *loc == w;
}

void Graph::contract(vx v, vx w){
  if(v > w) std::swap(v,w); //We always contract into the smaller index
  if(v == w) return;
  contractionTargets[w] = v;

  auto[same, diff] = partition(blackAdj[v], blackAdj[w], contractionTargets);

  auto reds = unify(redAdj[v], redAdj[w], redDegrees, contractionTargets);
  for(auto x : setSub(diff, reds, contractionTargets)){
    redDegrees[x]++; //Add a red edge to every neighbour that gains a red edge.
 }

  blackAdj[v] = same;
  redAdj[v] = unify(diff, reds, redDegrees);
  for(auto x : redAdj[v]) addRedEdge(x,v);//Quite expensive, but for low twin-width we don't call this often.
  contractionSeq.push_back(v);
  contractionSeq.push_back(w);
  activeVerts--;
  redDegrees[w] = 0;
  redDegrees[v] = redAdj[v].size();
}

vx Graph::redDegree(vx v) const{
  return redDegrees[v];
}

vx Graph::currentWidth() const{
  return *std::max_element(redDegrees.begin(), redDegrees.end());
}

std::vector<vx> Graph::activeVertices() const{
  std::vector<vx> rval;
  for(int i = 0; i < numVerts; i++){
    if(contractionTargets[i] == i) rval.push_back(i);
  }
  return rval;
}

vx Graph::resultingWidth(vx v, vx w) const {
  vx rval = currentWidth();
  auto[same, diff] = partition(blackAdj[v], blackAdj[w], contractionTargets);
  auto reds = unify(redAdj[v], redAdj[w], contractionTargets);

  for(auto x : setSub(diff, reds, contractionTargets)){

    rval = std::max(rval, redDegrees[x] + 1);
  }

  rval = std::max(rval, unify(reds, diff, contractionTargets).size());

  return rval;

}

void Graph::doBestContraction(){
  vx bestWidth = activeVerts;
  auto vs = activeVertices();
  vx bestV = 0;
  vx bestW = 1;
  for(auto v : vs){
    for(auto w : vs){
      if(w <= v) continue;
      if(resultingWidth(v,w) < bestWidth){
        bestWidth = resultingWidth(v,w);
        bestV = v;
        bestW = w;
      }
    }

  }
  contract(bestV, bestW);
}

void unpackContractionSequence(std::vector<vx>& cs){
  auto n = cs.size();
  for(int i = n-1; i > 0; i-=2){
    for(int j = i+1; j < n; j++){
      if(cs[j] >= cs[i]) cs[j]++;
    }
  }
}

Graph randomGraph(vx n, vx m){
  Graph G(n);
  for (vx i = 0; i < m; i++) {
    vx v = std::rand() % n;
    vx w = std::rand() % n;
    G.addBlackEdge(v,w);
  }
  return G;
}

Graph initGraphFromFile(const std::string& fname){
  bool problemLine = false;
  int n,m;
  std::ifstream f(fname, std::ios::in);
  Graph G;
  if (f.is_open()) {

    std::string line;
    while (std::getline(f, line)) {
      if(line[0] == 'c') continue;

      if(line[0] == 'p'){
        std::stringstream ss(line.substr(6));
        ss >> n >> m;
        G = Graph(n);

        problemLine = true;
        continue;
      }
      if(!problemLine) continue;
      std::stringstream ss(line);
      vx v,w;
      ss >> v >> w;
      v--;
      w--;
      G.addBlackEdge(v,w);
      m--;
    }
    f.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  if(!problemLine) LOG( "Input file did not coontain a problem line. No Graph has been generated.\n");
  if(m != 0)  LOG("File Parsing did not produce the number of edges indicated in the problem line");
  return G;
}
