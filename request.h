/**
 * @file request.h
 * @brief Defines the Request class for handling simulation requests
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <ostream>

using std::string;
using std::ostream;
using std::move;

/**
 * @brief Represents a request with IP information and duration.
 */
class Request {
private:
    /**
     * @brief The incoming IP address.
     */
    string ipIn;

    /**
     * @brief The outgoing IP address.
     */
    string ipOut;

    /**
     * @brief The duration of the request in seconds
     */
    size_t duration;

    /**
     * @brief Static counter for unique request IDs
     */
    static size_t next_id;

    /**
     * @brief The unique identifier for this request
     */
    size_t id;

    /**
     * @brief Flag indicating if request is completed
     */
    bool completed;

public:
    /**
     * @brief Default constructor for Request.
     */
    Request() : ipIn{string{}}, ipOut{string{}}, duration{0}, id{next_id++}, completed{false} {}

    /**
     * @brief Parameterized constructor for Request.
     * @param ipIn The incoming IP address.
     * @param ipOut The outgoing IP address.
     * @param duration The duration of the request in seconds.
     */
    Request(const string& ipIn, const string& ipOut, size_t duration) 
        : ipIn{ipIn}, ipOut{ipOut}, duration{duration}, id{next_id++}, completed{false} {}

    /**
     * @brief Get the duration of the request.
     * @return A constant reference to the duration.
     */
    const size_t& getDuration() const {
        return this->duration;
    }

    /**
     * @brief Get the ID of the request.
     * @return The request's unique identifier.
     */
    size_t getId() const {
        return this->id;
    }

    /**
     * @brief Get the processing time of the request.
     * @return The request's duration.
     */
    size_t getProcessTime() const {
        return this->duration;
    }

    /**
     * @brief Check if the request is completed.
     * @return True if completed, false otherwise.
     */
    bool isCompleted() const {
        return this->completed;
    }

    /**
     * @brief Mark the request as completed.
     */
    void complete() {
        this->completed = true;
    }

    /**
     * @brief Overload the << operator to display the Request object as a string.
     * @param os The output stream.
     * @param request The Request object to display.
     * @return The output stream with the Request object representation.
     */
    friend ostream& operator<<(ostream& os, const Request& request) {
        os << "Request #" << request.id 
           << " From:" << request.ipIn 
           << " ➜ " << request.ipOut 
           << " Duration: " << request.duration;
        return os;
    } 
};

#endif // REQUEST_H
