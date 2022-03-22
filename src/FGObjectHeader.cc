
#include "FGObjectHeader.hh"

#include "stdio.h"

#include "Trace.hh"
#include "misc.hh"
#include "Exception.hh"

void FGObjectHeader::instdata::clear() {
  str1 = "";
  str2 = "";
  objtype = "";
  instid = -1;
  compname = "";
  compinstid = -1;
}

void FGObjectHeader::instdata::print() {
  printf("str1: %s\nstr2: %s\n", str1.c_str(), str2.c_str());
  printf("objtype: %s\ninstid: %i\n", objtype.c_str(), instid);
  printf("compname: %s\ncompinstid: %i\n", compname.c_str(), compinstid);
}

FGObjectHeader::FGObjectHeader(Reader& _reader): Saveable() {
  deserialize(_reader);
}

FGObjectHeader::~FGObjectHeader() {
}

bool FGObjectHeader::parse_inststr(const std::string& _str, bool _entity, FGObjectHeader::instdata& _data) {
#ifdef SFT_DEBUG
  printf("Parsing(entity:%c) %s\n", _entity?'t':'f', _str.c_str());
#endif
  _data.clear();

  std::string::size_type sep0,sep1,sep2;

  // extract str1
  if ( (sep0 = _str.find(':', 1)) == _str.npos ) return false;
  _data.str1 = _str.substr(0, sep0);

  // str2 is until the first dot(.)
  if ( (sep1 = _str.find('.', sep0+1)) == _str.npos ) return false;
  _data.str2 = _str.substr(sep0+1, sep1-sep0-1);

  // returns the current position
  auto typenid = [&](std::string::size_type start, std::string& objtype, int32_t& instid) {
    std::string::size_type s0, s1, rv;
    std::string scope;

    //printf("_str:'%s', start:%lu/%c\n", _str.c_str(), start, _str[start]);
    // we look for the next dot, this will be the local scope of inspection
    if ( (s0 = _str.find('.', start)) ==_str.npos ) {
      // no dot, we're at the end
      scope = _str.substr(start, _str.npos);
      rv = _str.npos;
      //printf("npos scope:'%s'\n", scope.c_str());
    } else {
      scope = _str.substr(start, s0-start);
      rv = s0+1;
      //printf("hit:%lu scope:'%s'\n", s0, scope.c_str());
    }

    // now look for the last underscore, separating the instanceid at the end
    if ( (s1 = scope.rfind('_')) == scope.npos ) {
      // no underscore, the whole stringis the objtype
      objtype = scope;
      return rv;
    }

    // no if the part after the underscore can be converted to int
    // then it's an instanceid, otherwise the whole stuff is the objtype
    if ( strtoint32(scope.substr(s1+1), instid) ) {
      objtype = scope.substr(0, s1);
    } else {
      objtype = scope;
    }
    return rv;
  };

  int32_t dpos;
  // entity object type and instanceid
  dpos = typenid(sep1+1, _data.objtype, _data.instid);
  if ( !_entity ) {
    if ( dpos == _str.npos ) {
      printf("component and there should be more\n");
      return false;
    }
    typenid(dpos, _data.compname, _data.compinstid);
  }

  return true;
}

void FGObjectHeader::deserialize(Reader& _reader) {
  TRACE;
  _reader(c_objtype)(c_name)(c_proptype)(c_instance);
  instdata data;

  if ( !parse_inststr(c_instance, isEntity(), data) ) {
    EXCEPTION(strprintf("Unable to parse '%s'", c_instance.c_str()));
  }
  c_fgobjtype = data.objtype;
  c_instanceid = data.instid;
  if ( isComponent() ) {
    c_component_name = data.compname;
    c_component_instanceid = data.compinstid;
  }
}

std::string FGObjectHeader::str() const {
  return strprintf("Type: %s\n", c_objtype==0?"Component":"Entity") +
    strprintf("Name: %s\n", c_name.c_str()) +
    strprintf("Proptype: %s\n", c_proptype.c_str()) +
    strprintf("Instance: %s\n", c_instance.c_str()) +
    strprintf("FGObjType: %s\n", c_fgobjtype.c_str()) +
    strprintf("Instanceid: %i\n", c_instanceid);
}