#include <iostream>
#include <chrono>
#include <string>
#include "log.hpp"
#include "graph.hpp"
#include "partitionRefinement.hpp"

class Timer {
private:
  std::chrono::time_point<std::chrono::system_clock> startTime;
  std::string name;
public:
  Timer (std::string name) : name{name} {startTime = std::chrono::system_clock::now();}
  virtual ~Timer (){
    auto endTime = std::chrono::system_clock::now();
    LOG( name << " took " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms.");
  };
};

int main(int argc, char const *argv[]) {
  std::string infile;

  srand(time(nullptr));
  Graph G;
  if(argc == 2){
    G = initGraphFromFile(argv[1]);
  }
  else {
      G = randomGraph(2000, 2000000);
      G.logToFile("glog.gr");
  }
  auto T = new Timer("Compute FP");
  auto fp = factorizingPermutation(G);
  delete T;
  for(auto x : fp) std::cout << x << " ";
  std::cout << std::endl;
  return 0;
}
