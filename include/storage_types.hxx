#include "package.hxx"
#include <list>

enum class PackageQueueType {
    FIFO,
    LIFO
};

class IPackageStockpile{
    public:
    virtual void push(Package&& package) = 0;

    virtual bool empty() const = 0;

    virtual size_t size() const = 0;

    virtual  ~IPackageStockpile()=default;

    virtual Package begin() = 0;

    virtual Package end() = 0;

    virtual Package cbegin() const  = 0;

    virtual Package cend() const = 0;

};

class IPackageQueue:IPackageStockpile{
    public:

    virtual Package pop() =0;

    virtual PackageQueueType get_queue_type() const =0;

    ~IPackageQueue() override = default;

};

class PackageQueue:IPackageQueue{
    public:

    PackageQueue() = delete;

    PackageQueue(PackageQueueType QueueType) : QueueType_(QueueType), PackageList_(){};

    void push(Package&& package) override {PackageList_.pushback(package);};

    bool empty() const override{return PackageList_ == [];};

    size_t size() const override {return PackageList_.size();};

    Package pop() override ;

    PackageQueueType const override {return QueueType_;};

    ~IPackageQueue() override = default;

    private:
    PackageQueueType QueueType_;
    std::list<Package> PackageList_;
};