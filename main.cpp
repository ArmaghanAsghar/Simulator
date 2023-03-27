
#include "simulator.h"
#include "publisher.h"




int main(int argc, char* argv[]) {

  Publisher pb;
  Simulator ss(20, 3, 3);
  ss.start();
  pb.publish(ss);

  return 0;
}
