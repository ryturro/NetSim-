#ifndef NETSIM_FACTORY_HXX
#define NETSIM_FACTORY_HXX

#include "nodes.hxx"

template<class Node>

class NodeCollection{
public:

    using container = std::list<Node>;

    using const_iterator = container::const_iterator;

    using iterator = container::iterator;

    void add(Node&& node) {container.emplace_back(std::move(node))}

    void remove_by_id(ElementID id) {Kontyner.remove_if([id](const Node& elem) { return elem.get_id() == id; })}

    NodeCollection<Node>::iterator find_by_id(ElementID id){
    return std::find_if(Kontyner.begin(), Kontyner.end(), [id](const Node& node) { 
        return node.get_id() == id; 
    });+
    }

    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const {
    return std::find_if(Kontyner.begin(), Kontyner.end(), [id](const Node& node) { 
        return node.get_id() == id; 
    });
    }

    iterator begin() {return Kontyner.begin();}

    iterator end() {return Kontyner.end();}

    const_iterator cbegin() const {return Kontyner.cbegin();}

    const_iterator cend() const {return Kontyner.cend();}

private:
    container Kontyner;
};

class Factory{
public:
    void add_ramp(Ramp&& ramp) {ramp_kontyner.add(std::move(ramp));}

    void add_worker(Worker&& worker) {worker_kontyner.add(std::move(worker));}

    void add_storehouse(Storehouse&& storehouse) {storehouse_kontyner.add(std::move(storehouse));}

    void remove_ramp(ElementID id) {ramp_kontyner.remove_by_id(id);}

    void remove_worker(ElementID id);

    void remove_storehouse(ElementID id);

    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramp_kontyner.find_by_id(id);}
    
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return ramp_kontyner.find_by_id(id);}

    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return worker_kontyner.find_by_id(id);}
    
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return worker_kontyner.find_by_id(id);}

    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {return storehouse_kontyner.find_by_id(id);}
    
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return storehouse_kontyner.find_by_id(id);}

    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramp_kontyner.cbegin();}

    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramp_kontyner.cbegin();}

    NodeCollection<Worker>::const_iterator worker_cbegin() const {return worker_kontyner.cbegin();}

    NodeCollection<Worker>::const_iterator worker_cend() const {return worker_kontyner.cbegin();}

    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return storehouse_kontyner.cbegin();}

    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return storehouse_kontyner.cbegin();}
    
    bool is_consistent() const;

    void do_deliveries(Time);

    void do_package_passing();

    void do_work(Time);
private:
    template<class Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id);

    NodeCollection<Ramp> ramp_kontyner;
    NodeCollection<Worker> worker_kontyner;
    NodeCollection<Storehouse> storehouse_kontyner;
};

#endif //NETSIM_FACTORY_HXX
