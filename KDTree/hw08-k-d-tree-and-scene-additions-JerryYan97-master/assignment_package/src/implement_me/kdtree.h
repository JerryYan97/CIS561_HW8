#pragma once
#include <ignore_me/la.h>

enum IntersectState {
    NoIntersect, PartlyIntersect, FullyContained
};

class KDNode
{
public:
    KDNode();
    ~KDNode();

    KDNode* leftChild;
    KDNode* rightChild;
    unsigned int axis; // Which axis split this node represents
    glm::vec3 minCorner, maxCorner; // The world-space bounds of this node
    std::vector<glm::vec3*> particles; // A collection of pointers to the particles contained in this node.
};

class KDTree
{
public:
    KDTree();
    ~KDTree();

    KDNode* buildKdTree(const std::vector<glm::vec3*> &points, int depth);
    void build(const std::vector<glm::vec3*> &points);
    void clear();

    void searchKdTree(KDNode* v, std::vector<glm::vec3>& reportedPoints,glm::vec3 c, float r);
    void reportSubTree(KDNode* v, std::vector<glm::vec3>& reportedPoints);
    std::vector<glm::vec3> particlesInSphere(glm::vec3 c, float r); // Returns all the points contained within a sphere with center c and radius r


    KDNode* root;
    glm::vec3 minCorner, maxCorner; // For visualization purposes
};
