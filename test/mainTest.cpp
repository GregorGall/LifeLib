#include "Desk.h"
#include <iostream>

class View{

public:

  void operator<<(const Life::Desk& desk){
    for(int i = 0; i < desk.rows(); ++i){
      for(int j = 0; j < desk.cols(); ++j){
        std::cout << desk(i, j);
      }
      std::cout << std::endl;
    }
  }

};


int main(){

  Life::Desk d(10, 10);

  auto neighbourList = d.getNeighbours(5,5);

  for(auto cellPtr: neighbourList){
    cellPtr->renew();
  }

  View v;
  v << d;

  return 0;
}
