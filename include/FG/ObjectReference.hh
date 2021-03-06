
#ifndef SFT_OBJECTREFERENCE_H
#define SFT_OBJECTREFERENCE_H

#include <string>
#include <memory>

#include "FG/BaseObject.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  class ObjectHeader;

  class ObjectReference {
  public:
    ObjectReference();
    ObjectReference(const std::string& _ln, const std::string& _pn);
    ObjectReference(const ObjectReference& _other);
    ObjectReference(ObjectReference&&);
    ~ObjectReference();

    ObjectReference& operator=(const ObjectReference& other);
    ObjectReference& operator=(ObjectReference&& other);

    //inline std::string& levelName() {return c_levelname;};
    inline const std::string& levelName() const {return c_levelname;};
    //inline std::string& pathName() {return c_pathname;};
    inline const std::string& pathName() const {return c_pathname;};

    // comparision operators for being map keytypes for MapProperty
    bool operator<(const ObjectReference& b) const;
    bool operator>(const ObjectReference& b) const;
    bool operator==(const ObjectReference& b) const;
    inline operator bool() const {
      return c_pathname.size()!=0;
    };

    void resolve();
    std::string str();
    inline std::shared_ptr<BaseObject>& object() {resolve(); return c_obj;};
    template<class T>
    std::shared_ptr<T> as() {
      resolve();
      return std::dynamic_pointer_cast<T>(c_obj);
    };

    template<class T> bool resolveInto(std::shared_ptr<T>& _obj, bool _throw=true) {
      if ( (*this) && !_obj) {
	_obj = as<T>();
	if ( !_obj ) {
	  if ( _throw ) EXCEPTION(strprintf("Unable to resolve %s\n", str().c_str()));
	  else return false;
	}
      }
      return true;
    }

  private:
    std::string c_levelname="";
    std::string c_pathname="";
    BaseObjectSP c_obj = nullptr;
  };
  typedef std::weak_ptr<ObjectReference> ObjectReferenceWP;
  typedef std::weak_ptr<ObjectReference> ObjectReferenceSP;
}

#endif
