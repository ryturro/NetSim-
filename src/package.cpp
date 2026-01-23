#include "package.hxx"

std::set<ElementID> Package::used_ID;
std::set<ElementID> Package::freed_ID;

Package::Package() {
    if (freed_ID.empty()){
        if (used_ID.empty()) {
            ID_ = 1;
        }
        else {
            ID_ = *used_ID.end() + 1;
        }
    }
    else {
        ID_ = *freed_ID.begin();

    }
    used_ID.insert(ID_);
    used_ID.erase(ID_);
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