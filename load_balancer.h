/**
 * @file load_balancer.h
 * @brief Defines the LoadBalancer class for managing server load distribution
 */

#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <cstdlib>
#include "server.h"

using std::vector;
using std::queue;
using std::string;
using std::tuple;
using std::ostream;
using std::get;

/**
 * @brief A load balancer that distributes requests across multiple servers
 * 
 * The LoadBalancer class manages a pool of servers and distributes incoming requests
 * among them using a simple round-robin algorithm. It simulates network traffic by
 * generating random requests and assigning them to available servers.
 */
class LoadBalancer {
private:
    size_t runtime;      ///< Total simulation runtime in seconds
    size_t clock;        ///< Current simulation time
    size_t max_servers;  ///< Maximum number of servers allowed
    vector<Server> servers;  ///< Pool of available servers
    vector<tuple<Request, Server, size_t>> handled;  ///< Log of handled requests with completion times
    queue<Request> requests;  ///< Queue of pending requests

    /**
     * @brief Generate a random number between min and max inclusive
     * @param min Minimum value
     * @param max Maximum value
     * @return Random number between min and max
     */
    size_t random(size_t min, size_t max);

    /**
     * @brief Generate a random IP address string
     * @return Random IP address in format "xxx.xxx.xxx.xxx"
     */
    string generateIP();

    /**
     * @brief Generate a specified number of random requests
     * @param num_requests Number of requests to generate
     * @param os Optional output stream for logging
     */
    void generateRequests(size_t num_requests, ostream* os = nullptr);

    /**
     * @brief Initialize the server pool with a specified number of servers
     * @param num_servers Number of servers to create
     */
    void createServers(size_t num_servers);

    /**
     * @brief Assign a pending request to a specific server
     * @param server Reference to the server that will handle the request
     */
    void assignRequest(Server& server);

public:
    /**
     * @brief Construct a new Load Balancer
     * @param runtime Total simulation runtime in seconds
     * @param num_servers Number of servers to initialize
     * @param num_requests Number of requests to generate
     */
    LoadBalancer(size_t runtime, size_t num_servers, size_t num_requests);

    /**
     * @brief Run the load balancer simulation
     * @param os Output stream for logging (defaults to std::cout)
     */
    void run(ostream& os = std::cout);

    /**
     * @brief Print the simulation results and statistics
     * @param os Output stream for logging (defaults to std::cout)
     */
    void printLog(ostream& os = std::cout) const;
};

#endif
