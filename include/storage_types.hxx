#ifndef STORAGE_TYPES_HXX
#define STORAGE_TYPES_HXX

#include "package.hxx"
#include <list>
#include <cstddef>

enum class PackageQueueType {
    FIFO,
    LIFO
};

class IPackageStockpile{
    public:

    using const_iterator = std::list<Package>::const_iterator;
    using iterator = std::list<Package>::iterator;

    virtual void push(Package&& package) = 0;

    virtual bool empty() const = 0;

    virtual size_t size() const = 0;

    virtual  ~IPackageStockpile()=default;

    virtual iterator begin() = 0;

    virtual iterator end() = 0;

    virtual const_iterator cbegin() const  = 0;

    virtual const_iterator cend() const = 0;

};

class IPackageQueue: public IPackageStockpile{
    public:

    virtual Package pop() =0;

    virtual PackageQueueType get_queue_type() const =0;

    ~IPackageQueue() override = default;

};

class PackageQueue: public IPackageQueue{
    public:

    PackageQueue() = delete;

    PackageQueue(PackageQueueType QueueType) : QueueType_(QueueType), PackageList_(){}

    void push(Package&& package) override {PackageList_.push_back(std::move(package));}

    bool empty() const override{return PackageList_.empty();}

    size_t size() const override {return PackageList_.size();}

    Package pop() override ;

    PackageQueueType get_queue_type() const override {return QueueType_;}

    ~PackageQueue() override = default;

    iterator begin() override {return PackageList_.begin();}

    iterator end() override {return PackageList_.end();}

    const_iterator cbegin() const override {return PackageList_.cbegin();}

    const_iterator cend() const override {return PackageList_.cend();}

    private:
    PackageQueueType QueueType_;
    std::list<Package> PackageList_;
};

#endif