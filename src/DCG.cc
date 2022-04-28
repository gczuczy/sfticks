
#include "DCG.hh"
#include "Exception.hh"
#include "misc.hh"
#include "FGEntity.hh"
#include "FGBuilding.hh"
#include "FGConveyorBelt.hh"

namespace SFT {

  uint32_t DCG::c_indexcounter=0;
  DCG::DCG() {
    c_index = c_indexcounter++;
  }

  DCG::~DCG() {
  }

  void DCG::build(std::map<std::string, FG::EntitySP>& _pool) {
    helpers_t helpers;

    helpers.reg = [&](DCGComponentSP _comp) {
      // first associate the buildings with the component
      // and remove them from the pool
      std::string inststr;
#ifdef DEBUG_DCG_BUILD
      printf("DCG:%u reg&erase %lu:\n", c_index, _pool.size());
#endif
      for (auto it: _comp->buildings()) {
	inststr = it->instance();
#ifdef DEBUG_DCG_BUILD
	printf(" - %s\n", inststr.c_str());
#endif
	if ( _pool.find(inststr) == _pool.end() ) {
	  if ( c_component_map.find(inststr) == c_component_map.end() ) {
	    EXCEPTION(strprintf("DCG:%u reg/erase: instance not in pool and not reg: %s",
				c_index, inststr.c_str()));
	  } else {
	    EXCEPTION(strprintf("DCG:%u reg/erase: instance not in pool and reg: %s",
				c_index, inststr.c_str()));
	  }
	}
	c_component_map[inststr] = (_comp);
	_pool.erase(inststr);
      }
      // then register the nodes and edges
      if ( _comp->componentType() == DCGComponentType::Edge ) {
	c_edges.push_back(std::dynamic_pointer_cast<DCGEdge>(_comp));
#ifdef DEBUG_DCG_BUILD
	printf(" edge\n");
#endif
      } else if ( _comp->componentType() == DCGComponentType::Node ) {
	c_nodes.push_back(std::dynamic_pointer_cast<DCGNode>(_comp));
#ifdef DEBUG_DCG_BUILD
	printf(" node\n");
#endif
      }
#ifdef DEBUG_DCG_BUILD
      printf(" Pool remnants: %lu\n", _pool.size());
#endif
    };

    helpers.lookup = [&](FG::BuildingSP _b)->DCGComponentSP {
      auto it = c_component_map.find(_b->instance());
      if ( it != c_component_map.end() ) return it->second;
      return nullptr;
    };

    FG::BuildingSP element = std::dynamic_pointer_cast<FG::Building>(_pool.begin()->second);

    if ( !element )
      EXCEPTION("Unable to cast to BuildingSP");

#ifdef DEBUG_DCG_BUILD
    printf(" DCG:%u Starting with %s\n", c_index, element->instance().c_str());
#endif
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

#ifdef DEBUG_DCG_BUILD
      printf("Collected toadd %lu\n", toadd.size());
#endif

      // nothing to add, job well done
      if ( toadd.size() == 0 ) break;

      for (auto& it: toadd) {
	if ( c_component_map.find(it->instance()) == c_component_map.end() ) {
	  addElement(it, helpers);
	} else {
#ifdef DEBUG_DCG_BUILD
	  printf("toadd loop skipping %s\n", it->instance().c_str());
#endif
	}
      }
    } // while true, looping while we've added everything to this dcg
  }

  std::string DCG::dbgstr() const {
    std::string rv;

    // list the elements
    rv += strprintf("DCG:%u Nodes(%lu): \n", c_index, c_nodes.size());
    for (auto& it: c_nodes) rv += it->dbgstr();

    rv += strprintf("DCG:%u Edges(%lu):\n", c_index, c_edges.size());
    for (auto& it: c_edges) rv += it->dbgstr();

    return rv;
  }

  void DCG::addElement(FG::BuildingSP _element, helpers_t _helpers) {
    DCGComponentSP comp;

#ifdef DEBUG_DCG_BUILD
    printf("Adding element %s ... ", _element->instance().c_str());
#endif
    if (FG::ConveyorBeltSP item; (item = std::dynamic_pointer_cast<FG::ConveyorBelt>(_element)) ) {
#ifdef DEBUG_DCG_BUILD
      printf("is belt\n");
#endif
      comp = std::make_shared<DCGEdge>(item, _helpers);
    } else if ( FG::BuildingSP item; (item = std::dynamic_pointer_cast<FG::Building>(_element)) ) {
#ifdef DEBUG_DCG_BUILD
      printf("is building\n");
#endif
      comp = std::make_shared<DCGNode>(item, _helpers);
    } else {
#ifdef DEBUG_DCG_BUILD
      printf("fuck knows %u\n", _element->entityType());
#endif
    }
    _helpers.reg(comp);
#ifdef DEBUG_DCG_BUILD
    printf("\n");
#endif
  }
}
