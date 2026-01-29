//
// Created by elder on 1/27/2026.
//

#include <iostream>
#include "fireworkNode.h"

constexpr float testDT = 0.016;

int main() {
    std:: random_device gen;
    Firework firework;

    firework.nodes.reserve(10);
    firework.nodes.resize(10);
    firework.initRules();

    firework.allocateNewNode("Node 1");
    firework.allocateNewNode("Node 2");
    firework.allocateNewNode("Node 3");
    firework.allocateNewNode("Node 4");
    firework.allocateNewNode("Node 5");

    for (auto &node : firework.nodes) {
        if (node == nullptr) continue;

        std:: cout << node->name << " address: " << node.get() << std::endl;
    }

    firework.addNodesFromVectorToTree();

    return 0;

    // adding to the tree
    for (auto &node : firework.nodes) {
        if (node == nullptr) continue;
        if (node->type == Firework:: UNUSED) continue;

        if (node->age <= 0.0f) {
            auto minAge = firework.rules[node->type].minAge;
            auto maxAge = firework.rules[node->type].maxAge;

            std::uniform_real_distribution<float> ageDistribution(minAge, maxAge);

            node->age = ageDistribution(gen);
        }
        firework.addNode(node);
    }


    int frame = 0;
    while (frame < 100) {
        for (std:: shared_ptr<Firework::FireworkNode> &node : firework.nodes) {
            if (node == nullptr) continue;
            if (node->type == Firework:: UNUSED) continue;

            if (node->age <= 0.0f) {
                std:: cout << node->name << ": has died switching type to UNUSED" << std:: endl;
                node.reset();
                // nodePtr->type = Firework:: UNUSED;
                continue;
            }
            std:: cout << node->name <<  " type: " << node->type << std:: endl;
            std:: cout << node->name << " age: " << node->age << std:: endl;
            std:: cout << node->name << " ref count: " << node.use_count() << std::endl;

            node->age -= testDT;


            std:: cout << std:: endl;
        }
        frame++;
        std:: cout << "Frame count: " << frame << std:: endl;
    }

    for (auto &node : firework.nodes) {
        if (node == nullptr) {
            std:: cout << "Node is null" << std:: endl;
            std:: cout << "Address of node: " << node.get() << std::endl;
            std:: cout << std:: endl;
            continue;
        }
        std:: cout << node->type << std:: endl;
    }

}