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

    void addNode(std:: shared_ptr<FireworkNode> &node) {
        if (root == nullptr) {
            root = node;
            return;
        }

        int depth = 0;
        std:: shared_ptr<FireworkNode> current = root;

        while (true) {
            if (depth % 2 == 0) {
                if (node->particle.getPosition().x >= current->particle.getPosition().x) {
                    if (current->right == nullptr) {
                        current->right = node;
                        return;
                    }
                    current = current->right;
                } else if (node->particle.getPosition().x <= current->particle.getPosition().x) {
                    if (current->left == nullptr) {
                        current->left = node;
                        return;
                    }
                }
            } else if (depth % 2 == 1) {
                if (node->particle.getPosition().y >= current->particle.getPosition().y) {
                    if (current->right == nullptr) {
                        current->right = node;
                        return;
                    }
                    current = current->right;
                } else if (node->particle.getPosition().y <= current->particle.getPosition().y) {
                    if (current->left == nullptr) {
                        current->left = node;
                        return;
                    }
                }
            }
            depth++;
        }
    }

    FireworkNode *getRoot() {
        return root.get();
    }
};

int main() {
    std:: random_device gen;
    Firework firework;

    firework.nodes.resize(100);
    firework.initRules();

    auto node1 = std::make_shared<Firework::FireworkNode>("Node1");
    node1->particle.setPosition(30,34,0);
    auto node2 = std::make_shared<Firework::FireworkNode>("Node2");
    node2->particle.setPosition(12,46,0);
    auto node3 = std::make_shared<Firework::FireworkNode>("Node3");
    node3->particle.setPosition(52,22,0);
    std:: cout << std:: endl;

    std:: cout << "Address of node1: " << node1.get() << std::endl;
    std:: cout << "Address of node2: " << node2.get() << std::endl;
    std:: cout << "Address of node3: " << node3.get() << std::endl;

    if (firework.getRoot() == nullptr) {
        std:: cout << "Root is nullptr" << std:: endl;
    } else {
        std:: cout << "Root is not nullptr" << std:: endl;
    }

    firework.nodes.push_back(node1);
    firework.nodes.push_back(node2);
    firework.nodes.push_back(node3);
    std:: cout << std:: endl;

    

    for (auto &node : firework.nodes) {
        if (node == nullptr) continue;
        std:: cout << node->name << " address: " << node.get() << std:: endl;
        firework.addNode(node);
    }
    std:: cout << std:: endl;

    std:: cout << "Address of root node: " << firework.getRoot() << std:: endl;
    std:: cout << "Address of root-left: " << firework.getRoot()->left.get() << std:: endl;
    std:: cout << "Address of root-right: " << firework.getRoot()->right.get() << std:: endl;
    std:: cout << std:: endl;
}
