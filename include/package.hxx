#include "types.hxx"
#include <set>

class Package {
public:
    Package();
    Package(ElementID ID) : ID_(ID){};
    Package(Package&& package) : ID_(package.ID_) {};

    Package& operator=(Package&& package);
    ElementID get_id() const {return ID_;}

    ~Package();

private:
    ElementID ID_;
    std::set<ElementID> used_ID;
    std::set<ElementID> freed_ID;
};