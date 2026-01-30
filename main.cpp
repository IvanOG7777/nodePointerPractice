//
// Created by elder on 1/27/2026.
//

#include <iostream>
#include "fireworkNode.h"

constexpr float testDT = 0.016;

int main() {
    std:: random_device ageGen;
    std:: random_device posGen;
    Firework firework;

    firework.nodes.reserve(20);
    firework.nodes.resize(20);
    firework.initRules();

    firework.allocateNewNode("Node 1", static_cast<Firework::SizeType>(1));
    firework.allocateNewNode("Node 2", static_cast<Firework::SizeType>(2));
    firework.allocateNewNode("Node 3", static_cast<Firework::SizeType>(3));
    firework.allocateNewNode("Node 4", static_cast<Firework::SizeType>(4));
    firework.allocateNewNode("Node 5", static_cast<Firework::SizeType>(1));

    for (auto &node : firework.nodes) {
        if (node == nullptr) continue;

        std:: cout << node->name << " address: " << node.get() << std::endl;
        std:: cout << node->name << " position: ";
        node->particle.printPosition();
    }

    // assigning random age and position
    for (auto &node : firework.nodes) {
        if (node == nullptr) continue;
        if (node->type == Firework:: UNUSED) continue;

        if (node->age <= 0.0f) {
            auto minAge = firework.rules[node->type].minAge;
            auto maxAge = firework.rules[node->type].maxAge;

            std::uniform_real_distribution<float> ageDistribution(minAge, maxAge);

            node->age = ageDistribution(ageGen);
        }

        if (node->particle.getPosition().x == 0 && node->particle.getPosition().y == 0) {
            auto minPos = firework.rules[node->type].minPos;
            auto maxPos = firework.rules[node->type].maxPos;

            std::uniform_real_distribution<float> posXDistribution(minPos.x, maxPos.x);
            std::uniform_real_distribution<float> posYDistribution(minPos.y, maxPos.y);

            node->particle.setPosition(posXDistribution(posGen), posYDistribution(posGen), 0);

            std:: cout << "Particle position: ";
            node->particle.printPosition();
        }
    }

    firework.addNodesFromVectorToTree();

    for (auto &node : firework.nodes) {
        if (node == nullptr) continue;

        if (node->left != nullptr) {
            std:: cout << "Left of : " << node->name << " is: " << node->left->name << std:: endl;
        } else if (node->right != nullptr) {
            std:: cout << "Right of : " << node->name << " is: " << node->right->name << std:: endl;
        } else {
            std:: cout << node->name << " has no children nodes: " << std:: endl;
        }
        std:: cout << std:: endl;
    }


    while (firework.nodes[1]->age >= 0.0f) {
        firework.nodes[1]->age -= testDT;
        if (firework.nodes[1]->age <= 0.0f) {
            std:: cout << firework.nodes[0]->name << " has died adding its children" << std:: endl;
            for (size_t i = 0; i < firework.rules[firework.nodes[1]->type].payloads.size(); i++) {
                for (size_t j = 0; j < firework.rules[firework.nodes[1]->type].payloads[i].count; j++) {
                    std:: string name;

                    switch (firework.rules[firework.nodes[1]->type].payloads[i].type) {
                        case Firework::UNUSED:
                            name = "UNUSED";
                            break;
                        case Firework::SMALL:
                            name = "SMALL";
                            break;
                        case Firework::MEDIUM:
                            name = "MEDIUM";
                            break;
                        case Firework::LARGE:
                            name = "LARGE";
                            break;
                        case Firework::EXTRALARGE:
                            name = "EXTRALARGE";
                            break;
                        default:
                            name = "UNKNOWN";
                    }
                    firework.allocateNewNode(name, static_cast<Firework::SizeType>(firework.rules[firework.nodes[1]->type].payloads[i].type));
                }
            }
            break;
        }
    }

    return 0;

    int frame = 0;
    while (frame < 100) {
        for (std:: shared_ptr<Firework::FireworkNode> &node : firework.nodes) {
            if (node == nullptr) continue;
            if (node->type == Firework:: UNUSED) continue;

            if (node->age <= 0.0f) {
                std:: cout << node->name << ": has died switching type to UNUSED" << std:: endl;
                for (size_t i = 0; i < firework.rules[node->type].payloadCount; i++) {
                    std:: string name;

                    auto type = firework.rules[node->type].payloads[i].type;

                    switch (static_cast<Firework::SizeType>(type)) {
                        case Firework:: UNUSED:
                            name = "UNUSED";
                            break;
                        case Firework:: SMALL:
                            name = "SMALL";
                            break;
                        case Firework:: MEDIUM:
                            name = "MEDIUM";
                            break;
                        case Firework:: LARGE:
                            name = "LARGE";
                            break;
                        case Firework:: EXTRALARGE:
                            name = "EXTRALARGE";
                            break;
                        default:
                            name = "UNKNOWN";
                            break;
                    }
                    firework.allocateNewNode(name, static_cast<Firework::SizeType>(type));
                }
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

    return 0;

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