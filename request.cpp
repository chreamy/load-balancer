#include "request.h"

size_t Request::next_id = 0;

Request::Request() 
    : ipIn{string{}}, ipOut{string{}}, duration{0}, id{next_id++}, completed{false} {}

Request::Request(const string& ipIn, const string& ipOut, size_t duration)
    : ipIn{ipIn}, ipOut{ipOut}, duration{duration}, id{next_id++}, completed{false} {}

const size_t& Request::getDuration() const {
    return this->duration;
}

size_t Request::getId() const {
    return this->id;
}

size_t Request::getProcessTime() const {
    return this->duration;
}

bool Request::isCompleted() const {
    return this->completed;
}

void Request::complete() {
    this->completed = true;
}

ostream& operator<<(ostream& os, const Request& request) {
    os << "Request #" << request.id 
       << " From:" << request.ipIn 
       << " ➜ " << request.ipOut 
       << " Duration: " << request.duration;
    return os;
}
