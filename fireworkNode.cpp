//
// Created by elder on 1/26/2026.
//

#include <memory>
#include <vector>

#include "particle.h"

#include "fireworkNode.h"


void Firework::initRules() {
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

void Firework::addNode(std::shared_ptr<FireworkNode> &node) {
    if (root == nullptr) {
        root = node;
        return;
    }

    int depth = 0;
    std::shared_ptr<FireworkNode> current = root;

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
                current = current->left;
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
                current = current->left;
            }
        }
        depth++;
    }
}

float Firework::distance2(std::shared_ptr<FireworkNode>& node1, std::shared_ptr<FireworkNode> &node2) {
    float xSum = node1->particle.getPosition().x - node2->particle.getPosition().x;
    float ySum = node1->particle.getPosition().y - node2->particle.getPosition().y;

    float xSquared = xSum * xSum;
    float ySquared = ySum * ySum;

    return xSquared + ySquared;
}

//References of the shared_ptr will be pointing to the actual FireworkNode struct
void Firework::findNearestNeighborHelper(std::shared_ptr<FireworkNode> &current, std::shared_ptr<FireworkNode>*target,
                                         std::shared_ptr<FireworkNode> &bestNode, float &bestDistance, int depth) {
    if (current == nullptr) {
        return;
    }

    int axis = depth % 2;
    float currentDistance = distance2(current, *target);

    if (currentDistance > 0.0f && currentDistance < bestDistance) {
        bestDistance = currentDistance;
        bestNode = current;
    }

    float targetValueAxis = (axis % 2 == 0) ? target->get()->particle.getPosition().x : target->get()->particle.getPosition().y;
    float currentValueAxis = (axis % 2 == 0) ? current->particle.getPosition().x : current->particle.getPosition().y;

    std::shared_ptr<FireworkNode> nearChild = (targetValueAxis < currentValueAxis) ? current->left : current->right;
    std::shared_ptr<FireworkNode> farChild = (targetValueAxis < currentValueAxis) ? current->right : current->left;

    findNearestNeighborHelper(nearChild, target, bestNode, bestDistance, depth + 1);

    float difference = targetValueAxis - currentValueAxis;
    float differenceSquared = difference * difference;

    if (differenceSquared < bestDistance) {
        findNearestNeighborHelper(farChild, target, bestNode, bestDistance, depth + 1);
    }
}

std::shared_ptr<Firework::FireworkNode> Firework::findNearestNeighbor(std::shared_ptr<FireworkNode> &target) {
        if (root == nullptr) {
            std:: cout << "Tree is null returning target" << std:: endl;
            return target;
        }

        float bestDistance = std::numeric_limits<float>::infinity();
        std::shared_ptr<FireworkNode> bestNode = root;

        findNearestNeighborHelper(root, &target, bestNode, bestDistance, 0);

        std:: cout << "Address of bestNode in function: " << bestNode.get() << std::endl;

        return bestNode;
}


Firework::FireworkNode *Firework::getRoot() const {
    return root.get();
}
