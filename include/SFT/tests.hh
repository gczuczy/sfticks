
#ifndef SFT_TESTS_H
#define SFT_TESTS_H

#include "FG/World.hh"
#include <functional>

namespace SFT {

  struct testargs {
    FG::WorldSP world;
    int frequency;
  };

  typedef std::function<void(testargs&)> testfun_t;

  void test_beltsplines(testargs& _args);
  void test_objrefs(testargs& _args);
  void test_world(testargs& _args);
  void test_entityticks(testargs& _args);

}

#endif
