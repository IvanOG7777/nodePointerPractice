//
// Created by elder on 1/26/2026.
//

#include <iostream>
#include <memory>
#include <vector>

#include "particle.h"
#include <random>
#include <thread>
#include <chrono>

class Firework {
public:
    enum SizeType {
        UNUSED = 0,
        SMALL,
        MEDIUM,
        LARGE,
        EXTRALARGE,
    };

    struct Payload {
        unsigned int type;
        unsigned int count;

        void set(unsigned int passedType, unsigned int passedCount) {
            type = passedType;
            count = passedCount;
        }

        Payload () : type(UNUSED), count(0) {}
        Payload (unsigned int type, unsigned int count) : type(type), count(count) {}
    };

    struct Rule {
        float minAge;
        float maxAge;

        unsigned int type;
        unsigned int payloadCount;

        std:: vector<Payload> payloads;

        void init (unsigned int passedPayloadCount) {
            payloadCount = passedPayloadCount;
            payloads.resize(payloadCount);
        }

        Rule() : minAge(0), maxAge(0), type(UNUSED), payloadCount(0) {}
        Rule(float minAge, float maxAge, unsigned int type, unsigned int payloadCount) : minAge(minAge), maxAge(maxAge), type(type), payloadCount(payloadCount) {}
    };

    struct FireworkNode {
        std:: shared_ptr<FireworkNode> left;
        std:: shared_ptr<FireworkNode> right;
        Particle particle{};
        float age;
        unsigned int type;
        std:: string name;

        FireworkNode(const std:: string& name) : left(nullptr), right(nullptr), age(0), type(UNUSED), name(name) {
            std:: cout << name << " node has been created" << std:: endl;
        }
        FireworkNode(const std::shared_ptr<FireworkNode> &left, const std::shared_ptr<FireworkNode> &right, const float age, const unsigned int type) : left(left), right(right), age(age), type(type) {}

        ~FireworkNode() {
            std:: cout << name << " node has been destroyed" << std:: endl;
        }
    };
private:
    std::shared_ptr<FireworkNode> root;

public:
    Firework(): root(nullptr){}
    std:: vector<std::shared_ptr<FireworkNode>> nodes;
    std:: vector<Rule> rules;

    void initRules() {
        rules.clear();
        rules.resize(5);

        rules[0].type = UNUSED;
        rules[0].init(0);

        rules[1].type = SMALL;
        rules[1].maxAge = 1.5f;
        rules[1].minAge = 0.5f;
        rules[1].init(0);

        rules[2].type = MEDIUM;
        rules[2].maxAge = 1.5f;
        rules[2].minAge = 0.5f;
        rules[2].init(1);
        rules[2].payloads[0].set(SMALL, 8);

        rules[3].type = LARGE;
        rules[3].maxAge = 1.5f;
        rules[3].minAge = 0.5f;
        rules[3].init(1);
        rules[3].payloads[0].set(MEDIUM, 4);

        rules[4].type = EXTRALARGE;
        rules[4].maxAge = 1.5f;
        rules[4].minAge = 0.5f;
        rules[4].init(2);
        rules[4].payloads[0].set(LARGE, 2);
        rules[4].payloads[1].set(MEDIUM, 4);
    }

    std::shared_ptr<FireworkNode> getRoot() {
        return root;
    }
};

int main() {
    std:: random_device gen;
    Firework firework;
    std:: cout << firework.getRoot().get() << std:: endl;

    return 0;
    firework.nodes.resize(100);
    firework.initRules();

    for (auto &rule : firework.rules) {
        std:: cout << "Rule type: " << rule.type << std:: endl;
        std:: cout << "Rule payloads: " << std:: endl;
        for (auto& payload : rule.payloads) {
            std:: cout << "     Payload type: " << payload.type << std:: endl;
            std:: cout << "     Payload count: " << payload.count << std:: endl;
            std:: cout << std:: endl;
        }
        std:: cout << std:: endl;
    }


    auto node1 = std::make_shared<Firework::FireworkNode>("Node1");
    auto node2 = std::make_shared<Firework::FireworkNode>("Node2");
    auto node3 = std::make_shared<Firework::FireworkNode>("Node3");
    std:: cout << std:: endl;

    node1->left = node2;
    node1->right = node3;

    std:: cout << "Left of node1 is: " << node1->left->name  << ": " << node1->left.get() << std::endl;
    std:: cout << "Right of node1 is: " << node1->right->name << ": "<< node1->right.get() << std::endl;

    int node1RefCount = node1.use_count();
    int node2RefCount = node2.use_count();
    int node3RefCount = node3.use_count();
    std:: cout << std:: endl;

    std:: cout << "Node1 references: " << node1RefCount << std::endl;
    std:: cout << "Node2 references: " << node2RefCount << std::endl;
    std:: cout << "Node3 references: " << node3RefCount << std::endl;
    std:: cout << std:: endl;

    std:: cout << "Address of node1: " << node1.get() << std:: endl;
    std:: cout << "Address of node2: " << node2.get() << std:: endl;
    std:: cout << "Address of node3: " << node3.get() << std:: endl;
    std:: cout << std:: endl;

    firework.nodes.push_back(node1);
    firework.nodes.push_back(node2);
    firework.nodes.push_back(node3);
    std:: cout << std:: endl;

    for (auto &node : firework.nodes) {
        std:: cout << node->name << std:: endl;
        std:: cout << "Address: " << node.get() << std:: endl;
    }
    std:: cout << std:: endl;
}
