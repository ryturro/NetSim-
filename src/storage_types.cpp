#include "storage_types.hxx"

Package PackageQueue::pop() {
    if (QueueType_==PackageQueueType::LIFO) {
        Package package = std::move(PackageList_.back());
        PackageList_.pop_back();
        return package;
    }
    else {
        Package package = std::move(PackageList_.front());
        PackageList_.pop_front();
        return package;
    }

}