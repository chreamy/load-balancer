#include "load_balancer.h"

LoadBalancer::LoadBalancer(size_t runtime, size_t num_servers, size_t num_requests) 
    : runtime{runtime},
      clock{0},
      max_servers{num_servers}
       {
    generateRequests(num_requests, nullptr);
    createServers(num_servers);
}

size_t LoadBalancer::random(size_t min, size_t max) {
    return min + rand() % (max - min + 1);
}

string LoadBalancer::generate_IP() {
    return std::to_string(random(1, 255)) + "." + 
           std::to_string(random(0, 255)) + "." + 
           std::to_string(random(0, 255)) + "." + 
           std::to_string(random(1, 255));
}


void LoadBalancer::generateRequests(size_t num_requests, ostream* os) {
    size_t num_generated = 0;
    for (size_t i = 0; i < num_requests; ++i) {
        Request request{generate_IP(), generate_IP(), random(2, 16)};
        requests.push(request);
        ++num_generated;
    }
    
    if (os != nullptr) {
        *os << "\n╔════════════════ NEW REQUESTS ═══════════════╗\n";
        *os << "║ Added " << num_generated << " new requests to the queue\n";
        *os << "║ Current queue size: " << requests.size() << "\n";
        *os << "╚═════════════════════════════════════════════╝\n\n";
    }
}

void LoadBalancer::createServers(size_t num_servers) {
    for (size_t i = 0; i < num_servers; ++i) {
        servers.emplace_back(i);
    }
}

void LoadBalancer::assignRequest(Server& server) {
    server.setRequest(requests.front());
    requests.pop();
}

void LoadBalancer::run(ostream& os) {
    for (Server& server : this->servers) {
        server.setActive(true);
        this->assignRequest(server);
    }


    while (++this->clock <= this->runtime) {
        string cycle_str = std::to_string(this->clock);
        
        os << "\n┌─ CYCLE " << cycle_str << "\n";
        
        // Process current servers
        for (Server& server : this->servers) {
            if (server.isRunning()) {
                if (server.handleCurrentRequest(os)) {
                    // Server just finished its request
                    server.printCompletionMessage(os);
                    this->handled.emplace_back(server.getRequest(), server, this->clock);
                    if (this->requests.empty()) {
                        server.setActive(false);
                        os << "  ⚠ " << server << " deactivated (no requests in queue)\n";
                    } else {
                        this->assignRequest(server);
                    }
                }
            } else if (!server.justFinished()) {  // Don't process if just finished
                if (!server.isActive() && !this->requests.empty()) {
                    server.setActive(true);
                    os << "  ↑ " << server << " reactivated\n";
                    this->assignRequest(server);
                }
            }
        }

        if (this->random(0, 100) == 0) {
            this->generateRequests(this->random(max_servers, max_servers*10), &os);
            
            for (Server& server : this->servers) {
                if (!server.isActive() && !this->requests.empty()) {
                    server.setActive(true);
                    os << "  ↑ " << server << " reactivated due to new requests\n";
                    this->assignRequest(server);
                }
            }
        }

        os << "└───────────────────────────────────\n";
    }
}

void LoadBalancer::printLog(ostream& os) const {
    os << "\n╔════════════════ FINAL STATS ═══════════════╗\n";
    os << "║ Total requests processed: " << handled.size() << "\n";
    os << "║ Average requests per cycle: " << (float)handled.size() / runtime << "\n";
    os << "║ Final server count: " << servers.size() << "\n";
    os << "║ Requests in queue: " << requests.size() << "\n";
    os << "╚═════════════════════════════════════════════╝\n";
} 