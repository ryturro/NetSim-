#ifndef PACKAGE_HXX
#define PACKAGE_HXX

#include "types.hxx"
#include <set>

class Package {
public:
    Package();
    Package(ElementID ID) : ID_(ID){};
    Package(Package&& package) : ID_(package.ID_) { used_ID.insert(ID_); }

    Package& operator=(Package&& package);
    ElementID get_id() const {return ID_;}

    ~Package();

private:
    ElementID ID_;
    static std::set<ElementID> used_ID;
    static std::set<ElementID> freed_ID;
};

#endif
