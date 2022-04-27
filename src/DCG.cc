
#include "DCG.hh"
#include "Exception.hh"
#include "misc.hh"
#include "FGEntity.hh"
#include "FGBuilding.hh"
#include "FGConveyorBelt.hh"

namespace SFT {

  DCG::DCG() {
  }

  DCG::~DCG() {
  }

  void DCG::build(std::map<std::string, FG::EntitySP>& _pool) {
    helpers_t helpers;

    helpers.reg = [&](DCGComponentSP _comp) {
      // first associate the buildings with the component
      // and remove them from the pool
      std::string inststr;
      for (auto it: _comp->buildings()) {
	inststr = it->instance();
	c_component_map[inststr] = (_comp);
	_pool.erase(inststr);
      }
      // then register the nodes and edges
      if ( _comp->componentType() == DCGComponentType::Edge ) {
	c_edges.push_back(std::dynamic_pointer_cast<DCGEdge>(_comp));
      } else if ( _comp->componentType() == DCGComponentType::Node ) {
	c_nodes.push_back(std::dynamic_pointer_cast<DCGNode>(_comp));
      }
    };

    helpers.lookup = [&](FG::BuildingSP _b)->DCGComponentSP {
      auto it = c_component_map.find(_b->instance());
      if ( it != c_component_map.end() ) return it->second;
      return nullptr;
    };

    FG::BuildingSP element = std::dynamic_pointer_cast<FG::Building>(_pool.begin()->second);

    if ( !element )
      EXCEPTION("Unable to cat to BuildingSP");

    addElement(element, helpers);

    // we have the first component, now build the rest of the graph based
    // on the first's unconnected parts
    while ( true ) {
      // now we go through edges and nodes
      // if any are not connected, we grab their unconnected
      // objects, create nodes/edges for them, and rince-repeat

      std::list<FG::BuildingSP> toadd;

      for (auto& it: c_nodes) {
	toadd.splice(toadd.begin(), it->tryConnect(helpers));
      }

      for (auto& it: c_edges) {
	toadd.splice(toadd.begin(), it->tryConnect(helpers));
      }

      printf("Collected toadd %lu\n", toadd.size());

      // nothing to add, job well done
      if ( toadd.size() == 0 ) break;

      for (auto& it: toadd)
	addElement(it, helpers);
    }
  }

  void DCG::addElement(FG::BuildingSP _element, helpers_t _helpers) {
    DCGComponentSP comp;

    printf("Adding element %s ... ", _element->instance().c_str());
    if (FG::ConveyorBeltSP item; (item = std::dynamic_pointer_cast<FG::ConveyorBelt>(_element)) ) {
      printf("is belt\n");
      comp = std::make_shared<DCGEdge>(item, _helpers);
    } else if ( FG::BuildingSP item; (item = std::dynamic_pointer_cast<FG::Building>(_element)) ) {
      printf("is building\n");
      comp = std::make_shared<DCGNode>(item, _helpers);
    } else {
      printf("fuck knows %u\n", _element->entityType());
    }
    _helpers.reg(comp);
  }
}
