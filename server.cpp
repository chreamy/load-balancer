#include "server.h"


Server::Server()
    : server_num{0},
      curr_request{},
      time{0},
      running{false},
      active{false},
      just_finished{false} {}

Server::Server(const size_t& server_num)
    : server_num{server_num},
      curr_request{},
      time{0},
      running{false},
      active{false},
      just_finished{false} {}

void Server::setRequest(const Request& request) {
    curr_request = request;
    time = 0;
    running = true;
    just_finished = false;
}

bool Server::handleCurrentRequest(ostream& os) {
    if (just_finished) {
        just_finished = false;  // Reset for next cycle
        return false;
    }

    // Only print handling message if we're not about to finish
    if (time + 1 < curr_request.getProcessTime()) {
        os << "┌─[" << *this << "]─────────────────────────\n";
        os << "├─➤ Processing " << curr_request << " Remaining: " << (curr_request.getProcessTime() - time - 1) << " cycles\n";
    }

    if (++time >= curr_request.getProcessTime()) {
        running = false;
        just_finished = true;
        return true;
    }
    return false;
}

void Server::printCompletionMessage(ostream& os) const {
    os << "✓─[" << *this << "]─────────────────────────\n";
    os << "  ├─➤ Completed Request #" << curr_request.getId() << "\n";
    os << "  └─➤ Total time: " << time << " cycles\n";
}

const Request& Server::getRequest() const {
    return curr_request;
}

bool Server::isRunning() const {
    return running;
}

bool Server::isActive() const {
    return active;
}

bool Server::justFinished() const {
    return just_finished;
}

void Server::setActive(bool state) {
    active = state;
}

ostream& operator<<(ostream& os, const Server& server) {
    os << "Server-" << server.server_num;
    return os;
} 