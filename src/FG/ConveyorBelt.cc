
#include "FG/ConveyorBelt.hh"
#include "FG/ArrayProperty.hh"
#include "FG/StructProperty.hh"
#include "FG/ObjectProperty.hh"
#include "SFT/Trace.hh"
#include "FG/DescObject.hh"

#include "SFT/Exception.hh"
#include "misc.hh"
#include <cmakeconfig.hh>
#include <algorithm>

namespace FG {

  ConveyorBelt::BeltItem::BeltItem(float _position, DescObjectSP _item)
    : position(_position), item(_item) {
  }
  
  ConveyorBelt::BeltItem::BeltItem(float _position, ObjectReference _item): position(_position) {
    item = _item.as<DescObject>();
    if ( !item )
      EXCEPTION(strprintf("Reference %s:%s cannot be looked up as DescObject",
			  _item.levelName().c_str(),
			  _item.pathName().c_str()));
  }

  std::set<uint32_t> ConveyorBelt::c_cache_throughputs{60, 120, 270, 480, 780};
  std::map<uint32_t, float> ConveyorBelt::c_cache_movelens{};

  ConveyorBelt::ConveyorBelt(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput)
    : Building(_et, _reader, _fgoh), c_throughput(_throughput) {
    defineProperty(std::make_shared<ArrayProperty<StructProperty<SplinePointData> > >("mSplineData", c_mSplineData));

    // supplemental data handler
    defineSupplementalHandler(std::bind(&ConveyorBelt::supplementalHandler,
					this,
					std::placeholders::_1));
  }

  ConveyorBelt::~ConveyorBelt() {
  }

  void ConveyorBelt::associateComponents() {
    Building::associateComponents();

    // convert the refs to actual items
    for (auto& it: c_belt_items_ref) {
      c_belt_items.push_back(BeltItem(it.position, it.item));
    }

    c_length =calcLength();
  }

  float ConveyorBelt::calcLength() {
    float len(0);
    if ( c_mSplineData.size() < 2 )
      EXCEPTION("ConveyorBelt::length needs at least 2 points");

    Vector3 prev = c_mSplineData[0].Location;

    for (int i=1; i<c_mSplineData.size(); ++i) {
      len += (prev - c_mSplineData[i].Location).length();
      prev = c_mSplineData[i].Location;
    }

    // this is called from associatecomponents,
    // and that means we have the belt items already
    // so if the calc length is shorter than the maxpos item, we adjust it

    for (auto& it: c_belt_items) {
      if ( it.position > len ) len = it.position;
    }

    return len;
  }

  void ConveyorBelt::doTick(SFT::tickinfo_t& _tick) {
    // this one essentially moves items forward on the belt
    float beltlen = length();
    float movelen = c_cache_movelens[c_throughput];
    float itemahead = -1; // -1 signifies we're the first, nothing is ahead
    FactoryConnectionComponentSP& outconn = outputs()[0];

    printf("Items(%lu, len:%.2f movelen:%.2f):\n", c_belt_items.size(), beltlen, movelen);
    // NOTE: This should be a circular buffer for alloc-free mechanics
    for (auto it=c_belt_items.begin(); it!=c_belt_items.end(); ++it) {
      printf(" - %.2f: %s\n", it->position, it->item->className().c_str());
      /* Rules (of engagement):
	 - If >= beltlen then we try to transfer it. On success pop it
	 - Min delta_pos=FG_BELTITEM_DISTANCE(120)
       */
      float nextpos = it->position+movelen;

      // there's a difference if we're the first
      if ( itemahead<0 ) {
	if ( nextpos >= beltlen ) {
	  // item is first in line, and needs a transfer
	  if ( outconn->send(it->item, _tick) ) {
	  // send succeeded
	    printf("  - First, send succeeded\n");
	    c_belt_items.erase(it);
	  } else {
	    // send failed
	    printf("  - First, send failed\n");
	    it->position = beltlen;
	    itemahead = beltlen;
	  }
	} else {
	  it->position = nextpos;
	  itemahead = nextpos;
	}
	continue;
      } // itemahead<0
      // Right here it's garanteed we're not at the front, so just push stuff forward
      // because there's no jumping ahead for transfers
      it->position = std::min(itemahead-FG_BELTITEM_DISTANCE, it->position+movelen);
      itemahead = it->position;
    } // for c_belt_items
    printf("Newpos:\n");
    for (auto& it: c_belt_items) {
      printf(" %.2f: %s\n", it.position, it.item->className().c_str());
    }

    //EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }

  bool ConveyorBelt::recv(DescObjectSP& _item, SFT::tickinfo_t& _tick, FactoryConnectionComponent& _src) {
    /* Because the logic is to move backwards in the graph, by the time anything
       is passed here, contents have already been moved forward, so we don't have to
       take that into account
     */
    float movelen = c_cache_movelens[c_throughput];
    // we have to see whether there's any space left after the last item on the belt

    auto last = c_belt_items.rbegin();
    // if there's no place on the belt, returning false
    if ( last->position <= FG_BELTITEM_DISTANCE ) return false;

    // Take it, it'll be the last
    c_belt_items.emplace_back(std::min(last->position-FG_BELTITEM_DISTANCE, movelen),
			      _item);
    
    return true;
  }
  
  void ConveyorBelt::doTickCache(SFT::tickinfo_t& _tick) {
    for (auto& it: c_cache_throughputs) {
      c_cache_movelens[it] = (it/60)*_tick.timedelta*FG_BELTITEM_DISTANCE;
    }
  }

  void ConveyorBelt::supplementalHandler(Reader& _reader) {
    int32_t count;
    std::string unused;

    _reader.skip(4);
    _reader(count);

    std::string level,path;
    for (int i=0; i<count; ++i) {
      BeltItemRef bi;
      _reader.skip(4);
      _reader(path)(level)(unused)(bi.position);
      bi.item = std::move(ObjectReference(level, path));
      c_belt_items_ref.push_back(bi);
    }
  }
}
