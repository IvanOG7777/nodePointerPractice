//
// Created by elder on 1/27/2026.
//

#include <iostream>
#include "fireworkNode.h"

int main() {
    std:: random_device gen;
    Firework firework;

    firework.nodes.reserve(10);
    firework.nodes.resize(10);
    firework.initRules();

    auto node1 = std::make_shared<Firework::FireworkNode>("Node1");
    node1->particle.setPosition(30,34,0);
    node1->type = Firework:: EXTRALARGE;
    auto node2 = std::make_shared<Firework::FireworkNode>("Node2");
    node2->particle.setPosition(505,46,0);
    node2->type = Firework:: LARGE;
    auto node3 = std::make_shared<Firework::FireworkNode>("Node3");
    node3->particle.setPosition(521,232,0);
    node3->type = Firework:: MEDIUM;
    std:: cout << std:: endl;

    auto node4 = std::make_shared<Firework::FireworkNode>("Node4");
    node4->particle.setPosition(83,34,0);
    node4->type = Firework:: EXTRALARGE;
    auto node5 = std::make_shared<Firework::FireworkNode>("Node5");
    node5->particle.setPosition(64,44,0);
    node5->type = Firework:: LARGE;
    auto node6 = std::make_shared<Firework::FireworkNode>("Node6");
    node6->particle.setPosition(5,94,0);
    node6->type = Firework:: MEDIUM;
    std:: cout << std:: endl;

    std:: cout << "Address of node1: " << node1.get() << std::endl;
    std:: cout << "Address of node2: " << node2.get() << std::endl;
    std:: cout << "Address of node3: " << node3.get() << std::endl;
    std:: cout << "Address of node4: " << node4.get() << std::endl;
    std:: cout << "Address of node5: " << node5.get() << std::endl;
    std:: cout << "Address of node6: " << node6.get() << std::endl;

    if (firework.getRoot() == nullptr) {
        std:: cout << "Root is nullptr" << std:: endl;
    } else {
        std:: cout << "Root is not nullptr" << std:: endl;
    }

    firework.nodes[0] = node1;
    firework.nodes[1] = node2;
    firework.nodes[2] = node3;
    firework.nodes[3] = node4;
    firework.nodes[4] = node5;
    firework.nodes[5] = node6;
    std:: cout << std:: endl;



    // adding to the tree
    for (auto &node : firework.nodes) {
        if (node == nullptr) continue;
        if (node->type == Firework:: UNUSED) continue;
        firework.addNode(node);
    }

    if (firework.getRoot() == nullptr) {
        std:: cout << "Root is nullptr" << std:: endl;
    } else {
        std:: cout << "Root is not nullptr" << std:: endl;
    }

    std::shared_ptr<Firework::FireworkNode> bestNode = firework.findNearestNeighbor(node1);

    std:: cout << "Closest node to node1 is: " << bestNode->name << std::endl;

}