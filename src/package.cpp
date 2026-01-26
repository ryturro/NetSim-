#include "package.hxx"

std::set<ElementID> Package::used_ID;
std::set<ElementID> Package::freed_ID;

Package::Package() {
    if (!freed_ID.empty()) {
        ID_ = *freed_ID.begin();
        freed_ID.erase(freed_ID.begin());
    } else {
        if (used_ID.empty()) {
            ID_ = 1;
        } else {
            ID_ = *used_ID.rbegin() + 1;
        }
    }
    used_ID.insert(ID_);
}
Package& Package::operator=(Package&& package) {
    if (this == &package) {
        return *this;
    }
    used_ID.erase(this -> ID_);
    freed_ID.insert(this -> ID_);
    this->ID_ = package.ID_;
    return *this;
}

Package::~Package() {
    freed_ID.insert(ID_);
    used_ID.erase(ID_);
}