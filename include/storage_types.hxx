#include "package.hxx"
#include <list>

enum class PackageQueueType {
    FIFO,
    LIFO
};

class IPackageStockpile {
    using const_iterator = std::list<Package>::const_iterator;
};

class IPackageQueue : public IPackageStockpile {

};

class PackageQueue : public IPackageQueue {

};