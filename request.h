/**
 * @file request.h
 * @brief Contains the definition of the Request class for network traffic simulation
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <ostream>

using std::string;
using std::ostream;
using std::move;

/**
 * @brief Models a network request in the load balancing system
 * 
 * This class simulates a network request by tracking its source and 
 * destination addresses, processing requirements, and completion status.
 * Each request is assigned a unique identifier for tracking purposes.
 */
class Request {
private:
    /**
     * @brief Source address of the network request
     * 
     * Represents the originating IP address in standard IPv4 format
     */
    string ipIn;

    /**
     * @brief Destination address for the network request
     * 
     * Represents the target IP address in standard IPv4 format
     */
    string ipOut;

    /**
     * @brief Time required to process this request
     * 
     * Measured in simulation time units (cycles). This value determines
     * how long a server needs to handle the request.
     */
    size_t duration;

    /**
     * @brief Global counter for generating unique request identifiers
     * 
     * Increments each time a new request is created to ensure unique IDs
     */
    static size_t next_id;

    /**
     * @brief Unique identifier assigned to this request instance
     * 
     * Generated automatically during construction using next_id
     */
    size_t id;

    /**
     * @brief Tracks whether this request has been fully processed
     * 
     * Set to true when processing is complete, false while pending or in progress
     */
    bool completed;

public:
    /**
     * @brief Initializes a request with default values
     * 
     * Creates an empty request with:
     * - Empty source and destination addresses
     * - Zero duration
     * - New unique ID
     * - Not completed status
     */
    Request();

    /**
     * @brief Creates a fully specified request
     * 
     * @param ipIn Source IP address of the request
     * @param ipOut Destination IP address of the request
     * @param duration Number of cycles needed to process this request
     * 
     * Initializes a request with provided network parameters and automatically
     * assigns a unique identifier
     */
    Request(const string& ipIn, const string& ipOut, size_t duration);

    /**
     * @brief Retrieves the processing time requirement
     * 
     * @return Number of cycles needed to complete this request
     * 
     * This value is used by servers to determine how long they need to
     * process the request before completion
     */
    const size_t& getDuration() const;

    /**
     * @brief Retrieves the request's unique identifier
     * 
     * @return The unique ID assigned to this request
     * 
     * Used for tracking and logging purposes throughout the system
     */
    size_t getId() const;

    /**
     * @brief Gets the total processing time needed
     * 
     * @return Number of cycles required for completion
     * 
     * Provides the time requirement for resource allocation planning
     */
    size_t getProcessTime() const;

    /**
     * @brief Checks the request's completion status
     * 
     * @return true if request processing is finished, false otherwise
     * 
     * Used to track request progress through the system
     */
    bool isCompleted() const;

    /**
     * @brief Updates the request status to completed
     * 
     * Called by servers when they finish processing the request
     * to update its status in the system
     */
    void complete();

    /**
     * @brief Formats the request details for output
     * 
     * @param os The output stream to write to
     * @param request The request object to format
     * @return Reference to the output stream
     * 
     * Creates a human-readable representation showing:
     * - Request ID
     * - Source IP
     * - Destination IP
     * - Processing duration
     */
    friend ostream& operator<<(ostream& os, const Request& request);
};

#endif // REQUEST_H
