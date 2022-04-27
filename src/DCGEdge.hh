
#ifndef SFT_DCGEDGE_H
#define SFT_DCGEDGE_H

#include "DCGComponent.hh"
#include "FGEntity.hh"
#include "FGConveyorBelt.hh"

#include <string>
#include <list>

namespace SFT {

  /*
    This class represents the edges of the graph. This
    consists of aggregated belts of various types
   */
  class DCG;
  class DCGEdge: public DCGComponent {
  public:
    DCGEdge() = delete;
    DCGEdge(const DCGEdge&) = delete;
    DCGEdge(DCGEdge&&) = delete;
    DCGEdge(FG::ConveyorBeltSP _belt, helpers_t& _helpers);
    virtual ~DCGEdge();

    virtual std::list<FG::BuildingSP> buildings();
    virtual std::list<FG::BuildingSP> tryConnect(helpers_t& _helpers);

  private:
    float c_throughput=0;
    float c_speed=0;
    float c_length=0;
    // front input, back output
    std::list<FG::ConveyorBeltSP> c_belts;
    DCGConnection c_input, c_output;
  };
  typedef std::shared_ptr<DCGEdge> DCGEdgeSP;

}

#endif
