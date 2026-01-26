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

};