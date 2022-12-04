#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Router {
private:
    int id;
    vector<pair<Router*, int>> neighbors;
    vector<vector<int>> routingTable;

public:
    explicit Router(int id) {
        this->id = id;
    }

    int getId() const {
        return id;
    }

    void addNeighbor(Router* neighbor, int cost) {
        neighbors.emplace_back(neighbor, cost);
    }

    void printRoutingTable() {
        cout << endl << "Routing table of router " << id << ": " << endl;
        for (auto & i : routingTable) {
            for (int j : i) {
                cout << setw(4) << j << " ";
            }
            cout << endl;
        }
    }

    int getCost(int destination) {
        for (auto & i : neighbors) {
            if (i.first->getId() == destination) {
                return i.second;
            }
        }
        return -1;
    }

    void buildDistanceVector(int numberOfRouters) {
        routingTable = vector<vector<int>>(numberOfRouters, vector<int>(numberOfRouters, -1));
        for (int i = 0; i < numberOfRouters; i++) {
            if (i == id) {
                routingTable[id][i] = 0;
            } else {
                routingTable[id][i] = getCost(i);
            }
        }
    }

    void changeRoutingTableValue(int row, int column, int value) {
        routingTable[row][column] = value;
    }

    int getRoutingTableValue(int row, int column) {
        return routingTable[row][column];
    }

    vector<pair<Router*, int>> getNeighbors() {
        return neighbors;
    }
};

class VectorDistanceRouting {
private:
    vector<Router*> routers;

public:
    void addRouter(Router* router) {
        routers.push_back(router);
    }

    void printRouters() {
        cout << "Routers: ";
        for (auto & router : routers) {
            cout << router->getId() << " ";
        }
        cout << endl;
    }

    void printRoutingTables() {
        for (auto & router : routers) {
            router->printRoutingTable();
        }
    }

    void buildRoutingTables() {
        // Build distance vector for each router
        for (auto & router : routers) {
            router->buildDistanceVector((int)routers.size());
        }

        // Build routing tables for each router
        for (auto & router : routers) {
            for (auto & neighbor : router->getNeighbors()) {
                // Copy distance vector of neighbor to routing table of router
                for (int i = 0; i < (int)routers.size(); i++) {
                    router->changeRoutingTableValue(neighbor.first->getId(), i, neighbor.first->getRoutingTableValue(neighbor.first->getId(), i));
                }
                // Update routing table of router
                for (int i = 0; i < (int)routers.size(); i++) {
                    if (router->getRoutingTableValue(neighbor.first->getId(), i) != -1) {
                        if (router->getRoutingTableValue(router->getId(), i) == -1) {
                            router->changeRoutingTableValue(router->getId(), i, router->getRoutingTableValue(neighbor.first->getId(), i) + neighbor.second);
                        } else {
                            router->changeRoutingTableValue(router->getId(), i, min(router->getRoutingTableValue(router->getId(), i), router->getRoutingTableValue(neighbor.first->getId(), i) + neighbor.second));
                        }
                    }
                }
            }
        }

        // Verify minimum distance
        for (int i = 0; i < (int)routers.size(); i++) {
            for (int j = 0; j < (int)routers.size(); j++) {
                int minValue = 1000000;
                for (auto & router : routers) {
                    if (router->getRoutingTableValue(i, j) != -1) {
                        minValue = min(minValue, router->getRoutingTableValue(i, j));
                    }
                }
                for (auto & router : routers) {
                    router->changeRoutingTableValue(i, j, minValue);
                }
            }
        }

        // Check minimum from x to y and y to x to be the same
        for (int i = 0; i < (int)routers.size(); i++) {
            for (int j = 0; j < (int)routers.size(); j++) {
                if (i != j) {
                    for (auto & router : routers) {
                        if (router->getRoutingTableValue(i, j) != -1) {
                            int minValue = min(router->getRoutingTableValue(i, j), router->getRoutingTableValue(j, i));
                            router->changeRoutingTableValue(i, j, minValue);
                            router->changeRoutingTableValue(j, i, minValue);
                        }
                    }
                }
            }
        }
    }
};

int main() {
    VectorDistanceRouting vdr;

    auto* r0 = new Router(0);
    auto* r1 = new Router(1);
    auto* r2 = new Router(2);
    auto* r3 = new Router(3);
    auto* r4 = new Router(4);
    auto* r5 = new Router(5);
    auto* r6 = new Router(6);
    auto* r7 = new Router(7);
    auto* r8 = new Router(8);

    // TORUS 1D
    /*
    r0->addNeighbor(r1, 1);
    r1->addNeighbor(r2, 1);
    r2->addNeighbor(r3, 2);
    r3->addNeighbor(r4, 3);
    r4->addNeighbor(r5, 5);
    r5->addNeighbor(r6, 8);
    r6->addNeighbor(r7, 13);
    r7->addNeighbor(r8, 21);
    r8->addNeighbor(r0, 34);

    r1->addNeighbor(r0, 1);
    r2->addNeighbor(r1, 1);
    r3->addNeighbor(r2, 2);
    r4->addNeighbor(r3, 3);
    r5->addNeighbor(r4, 5);
    r6->addNeighbor(r5, 8);
    r7->addNeighbor(r6, 13);
    r8->addNeighbor(r7, 21);
    r0->addNeighbor(r8, 34);

    vdr.addRouter(r0);
    vdr.addRouter(r1);
    vdr.addRouter(r2);
    vdr.addRouter(r3);
    vdr.addRouter(r4);
    vdr.addRouter(r5);
    vdr.addRouter(r6);
    vdr.addRouter(r7);
    vdr.addRouter(r8);

    vdr.printRouters();
    vdr.buildRoutingTables();
    vdr.printRoutingTables();
    */

    // TORUS 2D

    r0->addNeighbor(r6, 144);
    r0->addNeighbor(r1, 1);
    r0->addNeighbor(r3, 3);
    r0->addNeighbor(r2, 2);

    r1->addNeighbor(r7, 233);
    r1->addNeighbor(r2, 1);
    r1->addNeighbor(r4, 377);
    r1->addNeighbor(r0, 1);

    r2->addNeighbor(r8, 987);
    r2->addNeighbor(r0, 2);
    r2->addNeighbor(r5, 1597);
    r2->addNeighbor(r1, 1);

    r3->addNeighbor(r0, 3);
    r3->addNeighbor(r4, 5);
    r3->addNeighbor(r6, 21);
    r3->addNeighbor(r5, 13);

    r4->addNeighbor(r1, 377);
    r4->addNeighbor(r5, 8);
    r4->addNeighbor(r7, 610);
    r4->addNeighbor(r3, 5);

    r5->addNeighbor(r2, 1597);
    r5->addNeighbor(r3, 13);
    r5->addNeighbor(r8, 2584);
    r5->addNeighbor(r4, 8);

    r6->addNeighbor(r3, 21);
    r6->addNeighbor(r7, 34);
    r6->addNeighbor(r0, 144);
    r6->addNeighbor(r8, 89);

    r7->addNeighbor(r4, 610);
    r7->addNeighbor(r8, 55);
    r7->addNeighbor(r1, 233);
    r7->addNeighbor(r6, 34);

    r8->addNeighbor(r5, 2584);
    r8->addNeighbor(r6, 89);
    r8->addNeighbor(r2, 987);
    r8->addNeighbor(r7, 55);

    vdr.addRouter(r0);
    vdr.addRouter(r1);
    vdr.addRouter(r2);
    vdr.addRouter(r3);
    vdr.addRouter(r4);
    vdr.addRouter(r5);
    vdr.addRouter(r6);
    vdr.addRouter(r7);
    vdr.addRouter(r8);

    vdr.printRouters();
    vdr.buildRoutingTables();
    vdr.printRoutingTables();

    
    return 0;
}
