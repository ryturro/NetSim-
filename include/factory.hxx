#ifndef NETSIM_FACTORY_HXX
#define NETSIM_FACTORY_HXX

#include "nodes.hxx"
#include "storage_types.hxx"

class NodeCollection{
public:
    using container = std::list<Node>;

    using const_iterator = ontainer::const_iterator;

    using iterator = ontainer::iterator;

    void add(node: Node&&) {container.emplace_back(std::move(node))}

    void remove_by_id(id: ElementID) {Kontyner.remove_if([id](const Node& elem) { return elem.get_id() == id; })}

    NodeCollection<Node>::iterator find_by_id(id: ElementID){
    return std::find_if(Kontyner.begin(), Kontyner.end(), [id](const Node& node) { 
        return node.get_id() == id; 
    });
    }

    NodeCollection<Node>::const_iterator find_by_id(id: ElementID){
    return std::find_if(Kontyner.begin(), Kontyner.end(), [id](const Node& node) { 
        return node.get_id() == id; 
    });
    }

    iterator begin() {return Kontyner.begin();}

    iterator end() {return Kontyner.end();}

    const_iterator cbegin() const {return Kontyner.cbegin();}

    const_iterator cend() const {return Kontyner.cend();}

private:
    container Kontyner
};
#endif //NETSIM_FACTORY_HXX