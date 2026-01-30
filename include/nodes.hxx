#include "helpers.hxx"
#include "storage_types.hxx"
#include "types.hxx"
#include "package.hxx"
#include <optional>
#include <memory>
#include <map>

enum class ReceiverType{
    WORKER,
    STOREHOUSE
};
enum class NodeColor{
    UNVISITED, VISITED, VERIFIED
};

class IPackageReceiver{
public:
    virtual void receive_package(Package&& p) = 0;

    virtual ElementID get_id() const = 0;
    
    virtual IPackageStockpile::const_iterator cbegin() const = 0;

    virtual IPackageStockpile::const_iterator cend() const = 0;

    virtual IPackageStockpile::const_iterator begin() const = 0;

    virtual IPackageStockpile::const_iterator end() const = 0;

    virtual ReceiverType get_receiver_type() const = 0;
    
    virtual ~IPackageReceiver() = default;
};

class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    explicit ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : generate_probability_(
            std::move(pg)) {};

    void add_receiver(IPackageReceiver* r);

    void remove_receiver(IPackageReceiver* r);

    IPackageReceiver* choose_receiver();

    const preferences_t& get_preferences() const {
        return preferences_;
    };

    const_iterator cbegin() const {return preferences_.cbegin();}

    const_iterator cend() const {return preferences_.cend();}

    const_iterator begin() const {return preferences_.begin();}

    const_iterator end() const {return preferences_.end();}
    
private:
    preferences_t preferences_;
    ProbabilityGenerator generate_probability_;
};

class PackageSender{
public:
    PackageSender()=default;
    PackageSender(PackageSender&&)=default;

    ReceiverPreferences receiver_preferences_; 

    void send_package(); 

    std::optional<Package>& get_sending_buffer() {
        return buffer_;
    };


protected:
    void push_package(Package&& p){
        buffer_.emplace(std::move(p));
    };

    std::optional<Package> buffer_ = std::nullopt;
};

class Ramp: public PackageSender{
public:
    Ramp(ElementID id,TimeOffset di){
        id_=id;
        di_=di;
    }
    void deliver_goods(Time t);

    TimeOffset get_delivery_interval() const{
        return di_;
    };
    ElementID get_id() const {
        return id_;
    }


private:
    ElementID id_;
    TimeOffset di_;
    Time t_;

};

class Worker: public PackageSender, public IPackageReceiver {
public:
    Worker(ElementID id,TimeOffset pd, std::unique_ptr<IPackageQueue> q){
        id_=id;
        pd_=pd;
        q_=std::move(q);
    }

    void do_work(Time t);
    void receive_package(Package&& p);
    
    ElementID get_id() const override { return id_; }
    //ReceiverType get_receiver_type() const override { return ReceiverType::WORKER; }
    
    IPackageStockpile::const_iterator begin() const override { return q_->cbegin(); }
    IPackageStockpile::const_iterator end() const override { return q_->cend(); }
    IPackageStockpile::const_iterator cbegin() const override { return q_->cbegin(); }
    IPackageStockpile::const_iterator cend() const override { return q_->cend(); }

    TimeOffset get_processing_duration() const {return pd_;};

    Time get_package_processing_start_time() const {return t_;}; 



private:
   ElementID id_;
   TimeOffset pd_;
   std::unique_ptr<IPackageQueue> q_;
   Time t_;

   std::optional<Package> processing_buffer_ = std::nullopt;

};

class Storehouse: public IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::FIFO)){
        id_=id;
        d_=std::move(d);
    }

    ElementID get_id() const override {return id_;}
    
    void receive_package(Package&& p) override;

    //ReceiverType get_receiver_type() const override {return ReceiverType::STOREHOUSE;}
    
    IPackageStockpile::const_iterator cbegin() const override {return d_->cbegin();}

    IPackageStockpile::const_iterator cend() const override {return d_->cend();}

    IPackageStockpile::const_iterator begin() const override {return d_->begin();}

    IPackageStockpile::const_iterator end() const override {return d_->end();}

private:
   ElementID id_;
   std::unique_ptr<IPackageStockpile> d_;
};

