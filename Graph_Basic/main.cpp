#include <iostream>
#include <vector>
#include "../code/LinkedInNetwork.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    LinkedInNetwork* graph = new LinkedInNetwork();
    // string name = "name";
    // graph->addProfessional(name);

    graph->addProfessional("Jackson");
    graph->addProfessional("Marley");
    graph->addProfessional("Presley");
    graph->addProfessional("Dylan");
    graph->addProfessional("Lennon");
    graph->addProfessional("McCartney");

    graph->addConnection("Marley", "Dylan");
    graph->addConnection("Dylan", "Lennon");
    graph->addConnection("McCartney","Lennon");
    graph->addConnection("Lennon","Presley");
    graph->addConnection("Presley","Dylan");

    // graph->breadthFirstTraverse("Marley");

    //graph->suggestProfessionalsWithinKthOrder("Presley",1);

    vector <string> connections = graph->suggestProfessionalsWithinKthOrder("Dylan", 2);

    int numConnections = connections.size();
    if (numConnections > 0) {
        cout << "[GRADER] The professionals within kth order are: ";
        for (int i = 0; i < numConnections - 1; i++) cout << connections[i] << ",";
        cout << connections[numConnections - 1] << "\n";
    } else {
        cout << "[GRADER] No reachable connections.\n";
    }
    return 0;
}
