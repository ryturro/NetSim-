#include "factory.hxx"
#include "nodes.hxx"

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
        for (const auto& item : container) {
            const PackageSender* sender = dynamic_cast<const PackageSender*>(&item);
            kolor[sender] = NodeColor::UNVISITED;
        }
    };

    set_unvisited_colors(cont_w);
    set_unvisited_colors(cont_r);

    try {
        for (const auto& ramp : cont_r) {
            const PackageSender* sender = dynamic_cast<const PackageSender*>(&ramp);
            has_reachable_storehouse(sender, kolor);
        }
    } catch (const std::logic_error&) {
        return false;
    }

    return true;

};
void Factory::do_deliveries(Time t){
    for(auto &ramp : cont_r)
        ramp.deliver_goods(t);
}

void Factory::do_work(Time t){
    for(auto &worker : cont_w)
        worker.do_work(t);
}

void do_package_passing(){
    for(auto &ramp :cont_r)
        ramp.send_package();
    for(auto &Worker :cont_w)
        Worker.send_package();
}
template<class Node>
void Factory::remove_receiver(NodeCollection<Node>& collection, ElementID id) {

    auto iter = collection.find_by_id(id);

    auto receiver_ptr = dynamic_cast<IPackageReceiver*>(iter);

    for (auto& ramp: cont_r) {
        auto& _preferences = ramp.receiver_preferences_.get_preferences();
        for (auto _preference: _preferences) {
            if (_preference.first == receiver_ptr) {
                ramp.receiver_preferences_.remove_receiver(receiver_ptr);
                break;
            }
        }
    }

    for (auto& worker: cont_w) {
        auto& _preferences = worker.receiver_preferences_.get_preferences();
        for (auto _preference: _preferences) {
            if (_preference.first == receiver_ptr) {
                worker.receiver_preferences_.remove_receiver(receiver_ptr);
                break;
            }
        }
    }
}
