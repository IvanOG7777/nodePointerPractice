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

    std:: cout << "Address of node1: " << node1.get() << " ref count: " << node1.use_count() << std::endl;
    std:: cout << "Address of node2: " << node2.get() << " ref count: " << node2.use_count() << std::endl;
    std:: cout << "Address of node3: " << node3.get() << " ref count: " << node3.use_count() << std::endl;
    std:: cout << "Address of node4: " << node4.get() << std::endl;
    std:: cout << "Address of node5: " << node5.get() << std::endl;
    std:: cout << "Address of node6: " << node6.get() << std::endl;

    firework.nodes[0] = node1;
    firework.nodes[1] = node2;
    firework.nodes[2] = node3;
    firework.nodes[3] = node4;
    firework.nodes[4] = node5;
    firework.nodes[5] = node6;
    std:: cout << std:: endl;

    std:: cout << "Address of node1 in vector: " << firework.nodes[0].get() << std::endl;
    std:: cout << "Address of node2 in vector: " << firework.nodes[1].get() << std::endl;
    std:: cout << "Address of node3 in vector: " << firework.nodes[2].get() << std::endl;

    std:: cout << std:: endl;

    for (auto &node : firework.nodes) {
        std:: cout << "Address: " <<  node.get() << std:: endl;
        std:: cout << "Type:" << std:: endl;
    }


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

    std::weak_ptr<Firework::FireworkNode> weakNode1 = node1;

    auto weak = weakNode1.lock();

    firework.nodes[0].reset();

    std:: cout << "Node1 ref count: " << node1.use_count() <<  std:: endl;

    return 0;

    int frame = 0;
    while (frame < 100) {
        for (std:: weak_ptr<Firework::FireworkNode> node : firework.nodes) {
            auto nodePtr = node.lock();
            if (nodePtr == nullptr) continue;
            if (nodePtr->type == Firework:: UNUSED) continue;

            if (nodePtr->age <= 0.0f) {
                std:: cout << nodePtr->name << ": has died switching type to UNUSED" << std:: endl;
                node.reset();
                // nodePtr->type = Firework:: UNUSED;
                break;
            }
            std:: cout << nodePtr->name <<  " type: " << nodePtr->type << std:: endl;
            std:: cout << nodePtr->name << " age: " << nodePtr->age << std:: endl;
            std:: cout << nodePtr->name << " ref count: " << nodePtr.use_count() << std::endl;

            nodePtr->age -= testDT;


            std:: cout << std:: endl;
        }
        frame++;
        std:: cout << "Frame count: " << frame << std:: endl;
    }

    std:: cout << "Node1 ref count: " << node1.use_count() << std::endl;
    std:: cout << "Node2 ref count: " << node2.use_count() << std::endl;
    std:: cout << "Node3 ref count: " << node3.use_count() << std::endl;
    std:: cout << "Node4 ref count: " << node4.use_count() << std::endl;
    std:: cout << "Node5 ref count: " << node5.use_count() << std::endl;
    std:: cout << "Node6 ref count: " << node6.use_count() << std::endl;


    for (auto &node : firework.nodes) {
        if (node == nullptr) {
            std:: cout << "Node is null" << std:: endl;
            continue;
        }
        std:: cout << node->type << std:: endl;
    }

}