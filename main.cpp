
#include "simulator.h"
#include "publisher.h"

int main(int argc, char* argv[]) {

  //TODO(aasghar) allow input using command line.
  Publisher pb;
  Simulator ss(20, 3, 3);
  ss.start();
  pb.publish(ss);

  return 0;
}
