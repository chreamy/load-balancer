/**
 * @file server.h
 * @brief Defines the Server class for handling individual requests in the load balancer
 */

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include "request.h"

using std::string;
using std::ostream;

/**
 * @brief Represents a server instance that can handle requests
 * 
 * The Server class simulates a server that can process one request at a time.
 * It maintains state about its current request, processing time, and status.
 * Each server has a unique identifier and can be active or inactive.
 */
class Server {
private:
    size_t server_num;    ///< Unique identifier for this server
    Request curr_request; ///< The request currently being processed
    size_t time;         ///< Time spent processing current request
    bool running;        ///< Whether the server is currently processing a request
    bool active;         ///< Whether the server is active in the server pool
    bool just_finished;  ///< Flag indicating if a request was just completed

public:
    /**
     * @brief Default constructor
     * 
     * Creates a server with default values. The server will be inactive
     * and not processing any requests.
     */
    Server();

    /**
     * @brief Construct a new Server with a specific identifier
     * @param server_num The unique identifier for this server
     */
    Server(const size_t& server_num);

    /**
     * @brief Assign a new request to this server
     * @param request The request to be processed
     */
    void setRequest(const Request& request);

    /**
     * @brief Process the current request for one time unit
     * @param os Output stream for logging (defaults to std::cout)
     * @return true if request processing is complete, false otherwise
     */
    bool handleCurrentRequest(ostream& os = std::cout);

    /**
     * @brief Output a message indicating request completion
     * @param os Output stream for logging (defaults to std::cout)
     */
    void printCompletionMessage(ostream& os = std::cout) const;

    /**
     * @brief Get the current request being processed
     * @return Constant reference to the current request
     */
    const Request& getRequest() const;

    /**
     * @brief Check if the server is currently processing a request
     * @return true if processing a request, false otherwise
     */
    bool isRunning() const;

    /**
     * @brief Check if the server is active in the server pool
     * @return true if server is active, false otherwise
     */
    bool isActive() const;

    /**
     * @brief Check if the server just completed a request
     * @return true if a request was just completed, false otherwise
     */
    bool justFinished() const;

    /**
     * @brief Set the active state of the server
     * @param state true to activate the server, false to deactivate
     */
    void setActive(bool state);

    /**
     * @brief Output operator overload for Server class
     * @param os Output stream to write to
     * @param server Server object to output
     * @return Reference to the output stream
     */
    friend ostream& operator<<(ostream& os, const Server& server);
};

#endif
