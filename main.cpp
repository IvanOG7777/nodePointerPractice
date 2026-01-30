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

    firework.initRules();

    firework.allocateNewNode("Node 1", static_cast<Firework::SizeType>(1));
    firework.allocateNewNode("Node 2", static_cast<Firework::SizeType>(2));
    firework.allocateNewNode("Node 3", static_cast<Firework::SizeType>(3));
    firework.allocateNewNode("Node 4", static_cast<Firework::SizeType>(4));
    firework.allocateNewNode("Node 5", static_cast<Firework::SizeType>(1));


    int frameCount = 0;
    while (!firework.hasActiveNodes()) {

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
            }

            std:: cout << node->name << " age: " << node->age << '\n';
            node->age -= testDT;

            if (node->age <= 0.0f) {
                std:: cout << node->name << " has died adding its children" << '\n';
                for (size_t i = 0; i < firework.rules[node->type].payloads.size(); i++) {
                    for (size_t j = 0; j < firework.rules[node->type].payloads[i].count; j++) {
                        std:: string name;

                        switch (firework.rules[node->type].payloads[i].type) {
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
                        firework.allocateNewNode(name, static_cast<Firework::SizeType>(firework.rules[node->type].payloads[i].type));
                    }
                }
                node.reset();
            }
        }
        frameCount++;
    }

    std:: cout << "Does vector have any active nodes?: " << (!firework.hasActiveNodes() ? "True" : "False") << '\n';

    for (auto &node: firework.nodes) {
        std::  cout << node.get() << '\n';
    }
    std:: cout << "Total added nodes: " << firework.addedNodeCount << '\n';
}