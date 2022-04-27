
#ifndef SFT_DCGNODE_H
#define SFT_DCGNODE_H

#include "DCGComponent.hh"
#include "FGBuilding.hh"

#include <list>

namespace SFT {

  class DCGNode: public DCGComponent {
  public:
    DCGNode() = delete;
    DCGNode(const DCGNode&) = delete;
    DCGNode(DCGNode&&) = delete;
    DCGNode(FG::BuildingSP _building, helpers_t& _helpers);
    virtual ~DCGNode();

    virtual std::list<FG::BuildingSP> buildings();
    virtual std::list<FG::BuildingSP> tryConnect(helpers_t& _helpers);

  private:
    FG::BuildingSP c_building;
    std::list<DCGConnection> c_inputs, c_outputs;
  };
  typedef std::shared_ptr<DCGNode> DCGNodeSP;
}

#endif
