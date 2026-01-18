#include "types.hxx"
#include "package.hxx"
#include <optional>
#include <memory>

class RecivePreferences{

};

class PackageSender{
public:
    PackageSender()=default;
    PackageSender(PackageSender&&)=default;

    RecivePreferences receiver_preferences_; 

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
    void delivergoods(Time t);

    TimeOffset get_delivery_interval() const{
        return di_;
    };
    ElementID get_id(){
        return id_;
    }


private:
    ElementID id_;
    TimeOffset di_;
    Time t_;

};

class Worker: public PackageSender{
public:
    Worker(ElementID id,TimeOffset pd, std::unique_ptr<IPackageQueue> q){
        id_=id;
        pd_=pd;
        q_=std::move(q);
    }

    void do_work(Time t);
    
    TimeOffset get_processing_duration(){return pd_;};

    Time get_processing_duration(){return t_;}; //o co tu chodzi?



private:
   ElementID id_;
   TimeOffset pd_;
   std::unique_ptr<IPackageQueue> q_;
   Time t_;


};


