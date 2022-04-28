
#ifndef SFT_DCG_H
#define SFT_DCG_H

#include <stdint.h>
#include <memory>
#include <string>
#include <list>
#include <map>

#include "DCGComponent.hh"
#include "DCGEdge.hh"
#include "DCGNode.hh"
#include "FGEntity.hh"

namespace SFT {

  // Directed Cyclic Graph representing a
  // closed graph of belts and their assorted connected entites;
  // Edges are aggregated belts
  // nodes are various units (attachment, production, storage, etc)

  // forward declaration to avoid circular include
  class DCG {
    /*
      NOTE: edge/node classes are split off into separate files and friended
      to avoid clutter here.
      connections are between Edges and Nodes
      AND between Edges and Edges. This happens
      when two different types (MkN) of belts are connected.
    */
  private:
    static uint32_t c_indexcounter;
  public:
    DCG();
    DCG(const DCG&) = delete;
    DCG(DCG&&) = delete;
    ~DCG();

    void build(std::map<std::string, FG::EntitySP>& _pool);
    inline uint32_t size() const {return c_edges.size()+c_nodes.size();};
    std::string dbgstr() const;

  private:
    void addElement(FG::BuildingSP _element, helpers_t _helpers);

  private:
    uint32_t c_index;
    std::map<std::string, DCGComponentSP> c_component_map;
    std::list<DCGEdgeSP> c_edges;
    std::list<DCGNodeSP> c_nodes;
  };
  typedef std::shared_ptr<DCG> DCGSP;

}
#endif
