
#ifndef SFT_OBJECTREFERENCE_H
#define SFT_OBJECTREFERENCE_H

#include <string>
#include <memory>

namespace FG {

  class ObjectHeader;

  class ObjectReference {
  public:
    ObjectReference();
    ObjectReference(const std::string& _ln, const std::string& _pn);
    ObjectReference(const ObjectReference& _other);
    ObjectReference(ObjectReference&&);
    ~ObjectReference();

    inline std::string& levelName() {return c_levelname;};
    inline const std::string& levelName() const {return c_levelname;};
    inline std::string& pathName() {return c_pathname;};
    inline const std::string& pathName() const {return c_pathname;};

    // comparision operators for being map keytypes for MapProperty
    bool operator<(const ObjectReference& b) const;
    bool operator>(const ObjectReference& b) const;
    bool operator==(const ObjectReference& b) const;

    void resolve();
    inline void clear() {c_me = nullptr;};
    inline std::shared_ptr<ObjectHeader>& object() {resolve(); return c_obj;};
    template<class T>
    std::shared_ptr<T> as() {
      resolve();
      return std::dynamic_pointer_cast<T>(c_obj);
    };

  private:
    void fillme();

  private:
    std::string c_levelname="";
    std::string c_pathname="";
    std::shared_ptr<ObjectHeader> c_obj;
    std::shared_ptr<ObjectReference> c_me;
  };
  typedef std::weak_ptr<ObjectReference> ObjectReferenceWP;
  typedef std::weak_ptr<ObjectReference> ObjectReferenceSP;
}

#endif
