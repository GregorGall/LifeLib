#include "Desk.h"
#include "Engines/CommonEngine.h"
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
  Life::CommonEngine cme(d);

  auto& c1 = d(1,2);
  auto& c2 = d(3,2);
  auto& c3 = d(3,3);
  auto& c4 = d(2,3);
  auto& c5 = d(2,4);

  c1.renew();
  c2.renew();
  c3.renew();
  c4.renew();
  c5.renew();

  cme.add(&c1);
  cme.add(&c2);
  cme.add(&c3);
  cme.add(&c4);
  cme.add(&c5);

  cme.process();
  cme.process();
  cme.process();
  cme.process();

  View v;
  v << d;

  return 0;
}
