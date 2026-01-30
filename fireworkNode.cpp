//
// Created by elder on 1/26/2026.
//

#include <memory>
#include <vector>
#include <queue>

#include "particle.h"

#include "fireworkNode.h"


Firework::Firework() {
    nodes.reserve(10);
    nodes.resize(10);
    nodeCount = 0;
}

void Firework::initRules() {
    rules.clear();
    rules.resize(5);

    rules[0].type = UNUSED;
    rules[0].init(0);

    rules[1].type = SMALL;
    rules[1].maxAge = 1.5f;
    rules[1].minAge = 0.5f;
    rules[1].maxPos = {500, 432, 0};
    rules[1].minPos = {234, 232, 0};
    rules[1].init(0);

    rules[2].type = MEDIUM;
    rules[2].maxAge = 1.5f;
    rules[2].minAge = 0.5f;
    rules[2].maxPos = {634, 732, 0};
    rules[2].minPos = {434, 932, 0};
    rules[2].init(1);
    rules[2].payloads[0].set(SMALL, 8);

    rules[3].type = LARGE;
    rules[3].maxAge = 1.5f;
    rules[3].minAge = 0.5f;
    rules[3].maxPos = {334, 732, 0};
    rules[3].minPos = {523, 252, 0};
    rules[3].init(1);
    rules[3].payloads[0].set(MEDIUM, 4);

    rules[4].type = EXTRALARGE;
    rules[4].maxAge = 1.5f;
    rules[4].minAge = 0.5f;
    rules[4].maxPos = {187, 732, 0};
    rules[4].minPos = {23, 223, 0};
    rules[4].init(2);
    rules[4].payloads[0].set(LARGE, 2);
    rules[4].payloads[1].set(MEDIUM, 4);
}

void Firework::addNode(std::shared_ptr<FireworkNode> &node) {
    if (root == nullptr) {
        root = node;
        std:: cout << node->name << " has been added" << std:: endl;
        return;
    }

    int depth = 0;
    std::shared_ptr<FireworkNode> current = root;

    while (true) {
        if (depth % 2 == 0) {
            if (node->particle.getPosition().x >= current->particle.getPosition().x) {
                if (current->right == nullptr) {
                    current->right = node;
                    std:: cout << node->name << " has been added" << std:: endl;
                    return;
                }
                current = current->right;
            } else if (node->particle.getPosition().x <= current->particle.getPosition().x) {
                if (current->left == nullptr) {
                    current->left = node;
                    std:: cout << node->name << " has been added" << std:: endl;
                    return;
                }
                current = current->left;
            }
        } else if (depth % 2 == 1) {
            if (node->particle.getPosition().y >= current->particle.getPosition().y) {
                if (current->right == nullptr) {
                    current->right = node;
                    std:: cout << node->name << " has been added" << std:: endl;
                    return;
                }
                current = current->right;
            } else if (node->particle.getPosition().y <= current->particle.getPosition().y) {
                if (current->left == nullptr) {
                    current->left = node;
                    std:: cout << node->name << " has been added" << std:: endl;
                    return;
                }
                current = current->left;
            }
        }
        depth++;
    }
}

float Firework::distance2(std::weak_ptr<FireworkNode>& node1, std::weak_ptr<FireworkNode> &node2) {

    auto nodePtr1 = node1.lock();
    auto nodePtr2 = node2.lock();

    if (nodePtr1 == nullptr || nodePtr2 == nullptr) {
        return 0.0f;
    }

    float xSum = nodePtr1->particle.getPosition().x - nodePtr2->particle.getPosition().x;
    float ySum = nodePtr1->particle.getPosition().y - nodePtr2->particle.getPosition().y;

    float xSquared = xSum * xSum;
    float ySquared = ySum * ySum;

    return xSquared + ySquared;
}

//References of the shared_ptr will be pointing to the actual FireworkNode struct
void Firework::findNearestNeighborHelper(std::weak_ptr<FireworkNode> &current, std::weak_ptr<FireworkNode> &target,
                                         std::weak_ptr<FireworkNode> &bestNode, float &bestDistance, int depth) {

    auto currentPtr = current.lock();
    auto targetPtr = target.lock();
    auto bestNodePtr = bestNode.lock();

    if (currentPtr == nullptr) {
        return;
    }

    int axis = depth % 2;
    float currentDistance = distance2(current, target);

    if (currentDistance > 0.0f && currentDistance < bestDistance) {
        bestDistance = currentDistance;
        bestNode = current;
    }

    float targetValueAxis = (axis % 2 == 0) ? targetPtr->particle.getPosition().x : targetPtr->particle.getPosition().y;
    float currentValueAxis = (axis % 2 == 0) ? currentPtr->particle.getPosition().x : currentPtr->particle.getPosition().y;

    std::weak_ptr<FireworkNode> nearChild = (targetValueAxis < currentValueAxis) ? currentPtr->left : currentPtr->right;
    std::weak_ptr<FireworkNode> farChild = (targetValueAxis < currentValueAxis) ? currentPtr->right : currentPtr->left;

    findNearestNeighborHelper(nearChild, target, bestNode, bestDistance, depth + 1);

    float difference = targetValueAxis - currentValueAxis;
    float differenceSquared = difference * difference;

    if (differenceSquared < bestDistance) {
        findNearestNeighborHelper(farChild, target, bestNode, bestDistance, depth + 1);
    }
}

std::weak_ptr<Firework::FireworkNode> Firework::findNearestNeighbor(std::shared_ptr<FireworkNode> &target) {
        if (root == nullptr) {
            std:: cout << "Tree is null returning target" << std:: endl;
            return target;
        }

        float bestDistance = std::numeric_limits<float>::infinity();

        std::weak_ptr<FireworkNode> bestNode = root;
        std:: weak_ptr<FireworkNode> current = root;
        std:: weak_ptr<FireworkNode> targetPtr = target;

        findNearestNeighborHelper(current, targetPtr, bestNode, bestDistance, 0);

        std:: cout << "Address of bestNode in function: " << bestNode.lock().get() << std::endl;

        return bestNode;
}


// looking for the first slot that is null to assign newly created node within the vector
void Firework::allocateNewNode(std:: string nodeName, Firework::SizeType type) {

    if (nodeCount >= nodes.size()) {
        std:: cout << "Nodes is full no space for new node. Returning" << std:: endl;
        return;
    }

    auto newNode = std::make_shared<FireworkNode>();
    newNode->name = nodeName;
    newNode->type = type;

    std:: cout << "Adding: " << nodeName << " to the vector of nodes" << std:: endl;

    nodes[nodeCount++] = newNode;
}

void Firework::addNodesFromVectorToTree() {
    for (auto &node : nodes) {
        if (node == nullptr) continue;

        addNode(node);
    }
}

void Firework::printByDepth() {
    if (root == nullptr) {
        std:: cout << "No nodes in tree returning" << std:: endl;
        return;
    }

    std:: weak_ptr<FireworkNode> current = root;
    int depth = 0;
    std:: queue<std::weak_ptr<FireworkNode>> queue;
    queue.push(current);

    while (!queue.empty()) {
        size_t length = queue.size();
        std:: cout << "Depth: " << depth << std::endl;
        auto node = queue.front().lock();
        for (size_t i = 0; i < length; i++) {
            if (node->left != nullptr) {
                queue.push(node->left);
            }
            if (node->right != nullptr) {
                queue.push(node->right);
            }
            std:: cout << " " << node->name << " ";
            queue.pop();
        }
        depth++;
    }

}



Firework::FireworkNode *Firework::getRoot() const {
    return root.get();
}
