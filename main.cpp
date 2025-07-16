#include <iostream>
#include <string>
#include <fstream>
#include "load_balancer.h"

using std::cout;
using std::cin;
using std::string;
using std::ofstream;

int main() {
    srand(0);
    
    cout << "# of servers: ";
    string input;
    getline(cin, input);
    size_t num_servers = stoul(input);
    cout << "# of clock cycles: ";
    getline(cin, input);
    size_t runtime = stoul(input);

    cout << "Starting simulation...\n";
    cout << "Output will be written to simulation_log.txt\n\n";

    ofstream outFile("simulation_log.txt");
    if (!outFile) {
        cout << "Error: Could not open output file\n";
        return 1;
    }

    outFile << "Starting load balancer with:\n"
            << "- " << num_servers << " servers\n"
            << "- Initial queue size: " << (num_servers * 100) << "\n"
            << "- Runtime: " << runtime << " cycles\n";

    LoadBalancer loadbalancer(runtime, num_servers, num_servers * 100);
    loadbalancer.run(outFile);
    outFile << "\nSimulation complete.\n\n";
    loadbalancer.printLog(outFile);

    outFile.close();
    cout << "Simulation complete. Check simulation_log.txt for results.\n";

    return 0;
}
