#include "nodes.hxx"
#include <algorithm>

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    if (preferences_.size() == 0) {
        preferences_[r] = 1.0;
    }
    else {
        auto denominator = static_cast<double>(preferences_.size()+1);
        for (auto& receiver_preference : preferences_) {
            receiver_preference.second = 1.0 / denominator;
        }
        preferences_[r] = 1.0 / denominator;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    
    if (preferences_.count(r)) {
        preferences_.erase(r);
        if (!preferences_.empty()) {
            auto denominator = static_cast<double>(preferences_.size());
            for (auto& receiver_preference : preferences_) {
                receiver_preference.second = 1.0 / denominator;
            }
        }
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    auto shot = generate_probability_();
    double distributor = 0.0;
    for (const auto& [receiver, probability] : preferences_) {
        distributor += probability;
        if (shot<=distributor){
            return receiver;
        }
    }
    if (preferences_.empty()) return (--preferences_.end())->first; //bledy zaokraglen, zwraca ostatni element
    return nullptr; //pusty kontener
}

void PackageSender::send_package(){
    if(!buffer_.has_value()){return;}
    IPackageReceiver* receiver = receiver_preferences_.choose_receiver();
    receiver -> receive_package(std::move(*buffer_));
    buffer_.reset();
}

void Worker::receive_package(Package &&p){
    q_ -> push(std::move(p));
}

void Worker::do_work(Time t){
    if (!processing_buffer_.has_value()&& !q_->empty()){
        processing_buffer_.emplace(q_->pop());
        t_=t;
    }
    if(processing_buffer_.has_value()){
        if (t-t_+1 ==pd_){
            push_package(std::move(processing_buffer_.value()));
            processing_buffer_.reset();   
        }
    }
    
}

void Ramp::deliver_goods(Time t){
    if(!buffer_){
        push_package(Package());
        buffer_.emplace(id_);
        t_=t;
        }
    if(t-di_==t_){
        push_package(Package());
        }
    }
