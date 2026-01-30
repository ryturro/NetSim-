#include "factory.hxx"
#include "nodes.hxx"
#include <stdexcept>
#include <algorithm>

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors) {
    if (node_colors[sender] == NodeColor::VERIFIED) {
        return true;
    }

    node_colors[sender] = NodeColor::VISITED;

    if (sender->receiver_preferences_.get_preferences().empty()) {
        throw std::logic_error("Sender does not have any receivers");
    }

    for (const auto& receiver : sender->receiver_preferences_.get_preferences()) {
        if (receiver.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
            return true;
        } else if (receiver.first->get_receiver_type() == ReceiverType::WORKER) {
            PackageSender* sendrecv_ptr = dynamic_cast<PackageSender*>(dynamic_cast<class Worker*>(receiver.first));

            if (sendrecv_ptr == sender) {
                continue;
            }

            if (node_colors[sendrecv_ptr] == NodeColor::UNVISITED && has_reachable_storehouse(sendrecv_ptr, node_colors)) {
                return true;
            }
        }
    }

    node_colors[sender] = NodeColor::VERIFIED;
    throw std::logic_error("Error");
}
void Factory::remove_worker(ElementID id){
    Worker* node = &(*worker_kontyner.find_by_id(id));

    std::for_each(worker_kontyner.begin(), worker_kontyner.end(), [node](Worker& worker) {
        worker.receiver_preferences_.remove_receiver(node);
    });

    std::for_each(ramp_kontyner.begin(), ramp_kontyner.end(), [node](Ramp& ramp) {
        ramp.receiver_preferences_.remove_receiver(node);
    });

    worker_kontyner.remove_by_id(id);
}

void Factory::remove_storehouse(ElementID id){
    Storehouse* node = &(*storehouse_kontyner.find_by_id(id));
    std::for_each(worker_kontyner.begin(), worker_kontyner.end(), [&node](Worker& ramp) {
        ramp.receiver_preferences_.remove_receiver(node);
    });

    std::for_each(worker_kontyner.begin(), worker_kontyner.end(), [&node](Worker& worker) {
        worker.receiver_preferences_.remove_receiver(node);
    });
    storehouse_kontyner.remove_by_id(id);
}

bool Factory::is_consistent() const {
  std::map<const PackageSender*, NodeColor> kolor;

    auto set_unvisited_colors = [&kolor](const auto& container) {
        for (auto it = container.cbegin(); it != container.cend(); ++it) {
            const auto& item = *it;
            const PackageSender* sender = dynamic_cast<const PackageSender*>(&item);
            if(sender){
                kolor[sender] = NodeColor::UNVISITED;
            }
            
        }
    };

    set_unvisited_colors(worker_kontyner);
    set_unvisited_colors(ramp_kontyner);

    try {
        for (auto it = ramp_kontyner.cbegin(); it != ramp_kontyner.cend(); ++it) {
            const auto& ramp = *it;
            const PackageSender* sender = dynamic_cast<const PackageSender*>(&ramp);
            if(sender){
                has_reachable_storehouse(sender, kolor);
            }
        }
    } catch (const std::logic_error&) {
        return false;
    }

    return true;

};
void Factory::do_deliveries(Time t){
    for(auto &ramp : ramp_kontyner)
        ramp.deliver_goods(t);
}

void Factory::do_work(Time t){
    for(auto &worker : worker_kontyner)
        worker.do_work(t);
}

void Factory::do_package_passing(){
    for(auto &ramp : ramp_kontyner)
        ramp.send_package();
    for(auto &Worker :worker_kontyner)
        Worker.send_package();
}
template<class Node>
void Factory::remove_receiver(NodeCollection<Node>& collection, ElementID id) {

    auto iter = collection.find_by_id(id);

    auto receiver_ptr = dynamic_cast<IPackageReceiver*>(iter);

    for (auto& ramp: ramp_kontyner) {
        auto& _preferences = ramp.receiver_preferences_.get_preferences();
        for (auto _preference: _preferences) {
            if (_preference.first == receiver_ptr) {
                ramp.receiver_preferences_.remove_receiver(receiver_ptr);
                break;
            }
        }
    }

    for (auto& worker: worker_kontyner) {
        auto& _preferences = worker.receiver_preferences_.get_preferences();
        for (auto _preference: _preferences) {
            if (_preference.first == receiver_ptr) {
                worker.receiver_preferences_.remove_receiver(receiver_ptr);
                break;
            }
        }
    }
}
