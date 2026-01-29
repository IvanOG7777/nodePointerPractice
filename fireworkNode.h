#pragma once

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

        Payload() : type(UNUSED), count(0) {
        }

        Payload(unsigned int type, unsigned int count) : type(type), count(count) {
        }
    };

    struct Rule {
        float minAge;
        float maxAge;

        unsigned int type;
        unsigned int payloadCount;

        std::vector<Payload> payloads;

        void init(unsigned int passedPayloadCount) {
            payloadCount = passedPayloadCount;
            payloads.resize(payloadCount);
        }

        Rule() : minAge(0), maxAge(0), type(UNUSED), payloadCount(0) {
        }

        Rule(float minAge, float maxAge, unsigned int type, unsigned int payloadCount) : minAge(minAge), maxAge(maxAge),
            type(type), payloadCount(payloadCount) {
        }
    };

    struct FireworkNode {
        std::shared_ptr<FireworkNode> left;
        std::shared_ptr<FireworkNode> right;
        Particle particle{};
        float age;
        unsigned int type;
        std::string name;

        FireworkNode() : left(nullptr), right(nullptr), age(0), type(UNUSED) {}

        FireworkNode(const std::string &name) : left(nullptr), right(nullptr), age(0), type(UNUSED), name(name) {
            std::cout << name << " node has been created" << std::endl;
        }

        FireworkNode(const std::shared_ptr<FireworkNode> &left, const std::shared_ptr<FireworkNode> &right,
                     const float age, const unsigned int type) : left(left), right(right), age(age), type(type) {
        }

        ~FireworkNode() {
            std::cout << name << " node has been destroyed" << std::endl;
        }
    };

private:
    std::shared_ptr<FireworkNode> root;

    void findNearestNeighborHelper(std::weak_ptr<FireworkNode> &current, std::weak_ptr<FireworkNode> &target,
                                   std::weak_ptr<FireworkNode> &bestNode, float &bestDistance, int depth);

    static float distance2(std::weak_ptr<FireworkNode> &node1, std::weak_ptr<FireworkNode> &node2);

public:
    Firework() : root(nullptr) {}

    std::vector<std::shared_ptr<FireworkNode> > nodes;
    std::vector<Rule> rules;

    void initRules();

    void addNode(std::shared_ptr<FireworkNode> &node);

    std::weak_ptr<FireworkNode> findNearestNeighbor(std::shared_ptr<FireworkNode> &target);

    FireworkNode *getRoot() const;
};
