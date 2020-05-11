#include "kdtree.h"
#include "iostream"

KDNode::KDNode()
    : leftChild(nullptr), rightChild(nullptr), axis(0), minCorner(), maxCorner(), particles()
{}

KDNode::~KDNode()
{
    delete leftChild;
    delete rightChild;
}

KDTree::KDTree()
    : root(nullptr)
{}

KDTree::~KDTree()
{
    delete root;
}

// Comparator functions you can use with std::sort to sort vec3s along the cardinal axes
bool xSort(glm::vec3* a, glm::vec3* b) { return a->x < b->x; }
bool ySort(glm::vec3* a, glm::vec3* b) { return a->y < b->y; }
bool zSort(glm::vec3* a, glm::vec3* b) { return a->z < b->z; }

void findCorner(const std::vector<glm::vec3*> &points, glm::vec3& minCorner, glm::vec3& maxCorner)
{
    minCorner = glm::vec3(points[0]->x, points[0]->y, points[0]->z);
    maxCorner = glm::vec3(points[0]->x, points[0]->y, points[0]->z);
    for(auto itr = points.begin(); itr != points.end(); itr++)
    {
        glm::vec3* tempPtr = *itr;
        float x = tempPtr->x;
        float y = tempPtr->y;
        float z = tempPtr->z;
        if(x > maxCorner.x)
        {
            maxCorner.x = x;
        }
        if(x < minCorner.x)
        {
            minCorner.x = x;
        }
        if(y > maxCorner.y)
        {
            maxCorner.y = y;
        }
        if(y < minCorner.y)
        {
            minCorner.y = y;
        }
        if(z > maxCorner.z)
        {
            maxCorner.z = z;
        }
        if(z < minCorner.z)
        {
            minCorner.z = z;
        }
    }
}

int findLeaves(KDNode *v)
{
    int counter = 0;
    if(v->particles.size() == 1)
    {
        return 1;
    }
    else
    {
        if(v->leftChild)
        {
            counter += findLeaves(v->leftChild);
        }
        if(v->rightChild)
        {
            counter += findLeaves(v->rightChild);
        }
        return counter;
    }
}

KDNode* KDTree::buildKdTree(const std::vector<glm::vec3 *> &points,int depth)
{
    if(points.size() == 1)
    {
        KDNode* currNode = new KDNode();
        currNode->minCorner = *points[0];
        currNode->maxCorner = *points[0];
        currNode->particles.push_back(points[0]);
        int depthFlag = depth % 3;
        currNode->axis = depthFlag;
        return currNode;
    }
    else
    {
        std::vector<glm::vec3 *> sortedPoints = points;
        std::vector<glm::vec3 *> setA;
        std::vector<glm::vec3 *> setB;
        glm::vec3 currMinCorner(0.f);
        glm::vec3 currMaxCorner(0.f);
        int depthFlag = depth % 3;
        if(depthFlag == 1)
        {
            // Along x axis.
            std::sort(sortedPoints.begin(), sortedPoints.end(), xSort);
            float xMedian = 0;

            // Get the median along x axis.
            int pSize = sortedPoints.size();
            int sizeFlag = pSize % 2;
            if(sizeFlag == 1)
            {
                // Odd:
                int idx = pSize / 2;
                xMedian = sortedPoints[idx]->x;
            }
            else
            {
                // Even:
                int idx2 = pSize / 2;
                int idx1 = idx2 - 1;
                xMedian = (sortedPoints[idx1]->x + sortedPoints[idx2]->x) / 2.f;
            }

            // Divide points to two sets.
            for(unsigned int i = 0; i < sortedPoints.size(); ++i)
            {
                float currValX = sortedPoints[i]->x;
                if(currValX < xMedian)
                {
                    setA.push_back(sortedPoints[i]);
                }
                else
                {
                    setB.push_back(sortedPoints[i]);
                }
            }
            currMaxCorner = *sortedPoints[sortedPoints.size() - 1];
            currMinCorner = *sortedPoints[0];
        }
        else if(depthFlag == 2)
        {
            // Along y axis.
            std::sort(sortedPoints.begin(), sortedPoints.end(), ySort);
            float yMedian = 0;

            // Get the median along x axis.
            int pSize = sortedPoints.size();
            int sizeFlag = pSize % 2;
            if(sizeFlag == 1)
            {
                // Odd:
                int idx = pSize / 2;
                yMedian = sortedPoints[idx]->y;
            }
            else
            {
                // Even:
                int idx2 = pSize / 2;
                int idx1 = idx2 - 1;
                yMedian = (sortedPoints[idx1]->y + sortedPoints[idx2]->y) / 2.f;
            }

            // Divide points to two sets.
            for(unsigned int i = 0; i < sortedPoints.size(); ++i)
            {
                float currValY = sortedPoints[i]->y;
                if(currValY < yMedian)
                {
                    setA.push_back(sortedPoints[i]);
                }
                else
                {
                    setB.push_back(sortedPoints[i]);
                }
            }
            currMaxCorner = *sortedPoints[sortedPoints.size() - 1];
            currMinCorner = *sortedPoints[0];
        }
        else
        {
            // Along z axis.
            std::sort(sortedPoints.begin(), sortedPoints.end(), zSort);
            float zMedian = 0;

            // Get the median along x axis.
            int pSize = sortedPoints.size();
            int sizeFlag = pSize % 2;
            if(sizeFlag == 1)
            {
                // Odd:
                int idx = pSize / 2;
                zMedian = sortedPoints[idx]->z;
            }
            else
            {
                // Even:
                int idx2 = pSize / 2;
                int idx1 = idx2 - 1;
                zMedian = (sortedPoints[idx1]->z + sortedPoints[idx2]->z) / 2.f;
            }

            // Divide points to two sets.
            for(unsigned int i = 0; i < sortedPoints.size(); ++i)
            {
                float currValZ = sortedPoints[i]->z;
                if(currValZ < zMedian)
                {
                    setA.push_back(sortedPoints[i]);
                }
                else
                {
                    setB.push_back(sortedPoints[i]);
                }
            }
            currMaxCorner = *sortedPoints[sortedPoints.size() - 1];
            currMinCorner = *sortedPoints[0];
        }

        // parent->leftChild = new KDNode();
        // parent->rightChild = new KDNode();
        // depthFlag: 1 -- X, 2 -- Y, 0 -- Z.
        KDNode* currNode = new KDNode();
        // currNode->minCorner = this->minCorner;
        // currNode->maxCorner = this->maxCorner;
        // currNode->minCorner = currMinCorner;
        // currNode->maxCorner = currMaxCorner;
        findCorner(points, currNode->minCorner, currNode->maxCorner);
        currNode->axis = (depthFlag + 2) % 3;
        if(!setA.empty())
        {
            currNode->leftChild = buildKdTree(setA, depth + 1);
        }
        if(!setB.empty())
        {
            currNode->rightChild = buildKdTree(setB, depth + 1);
        }
        return currNode;
    }
}

void KDTree::build(const std::vector<glm::vec3*> &points)
{
    //TODO
    // Set corner variables:
    if(points.empty())
    {
        return;
    }

    findCorner(points, minCorner, maxCorner);

    this->root = buildKdTree(points, 1);

    // int leavesNum = findLeaves(this->root->leftChild);

    // std::cout << "leavesNum: " << leavesNum << std::endl;
}

inline bool inSphere(glm::vec3 c, float r, glm::vec3 v)
{
    float rVSquare = (v.x - c.x) * (v.x - c.x) + (v.y - c.y) * (v.y - c.y) + (v.z - c.z) * (v.z - c.z);
    r = r * r;
    if(rVSquare <= r)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline float squared(float v) { return v * v; }
bool doesCubeIntersectSphere(glm::vec3 C1, glm::vec3 C2, glm::vec3 S, float R)
{
    float dist_squared = R * R;
    /* assume C1 and C2 are element-wise sorted, if not, do that now */
    if (S.x < C1.x) dist_squared -= squared(S.x - C1.x);
    else if (S.x > C2.x) dist_squared -= squared(S.x - C2.x);
    if (S.y < C1.y) dist_squared -= squared(S.y - C1.y);
    else if (S.y > C2.y) dist_squared -= squared(S.y - C2.y);
    if (S.z < C1.z) dist_squared -= squared(S.z - C1.z);
    else if (S.z > C2.z) dist_squared -= squared(S.z - C2.z);
    return dist_squared > 0;
}

// Between Sphere and cuboid.
inline IntersectState checkIntersection(glm::vec3 c, float r, glm::vec3& minCorner, glm::vec3& maxCorner)
{
    std::vector<glm::vec3> cuboidCorners;
    std::vector<float> tempX{minCorner.x, maxCorner.x};
    std::vector<float> tempY{minCorner.y, maxCorner.y};
    std::vector<float> tempZ{minCorner.z, maxCorner.z};

    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            for(int k = 0; k < 2; ++k)
            {
                cuboidCorners.push_back(glm::vec3(tempX[i], tempY[j], tempZ[k]));
            }
        }
    }

    // Check whether 8 points are all in sphere.
    int intersectionCounter = 0;
    for(int i = 0; i < 8; ++i)
    {
        if(inSphere(c, r, cuboidCorners[i]))
        {
            intersectionCounter++;
        }
    }

    if(intersectionCounter == 8)
    {
        return FullyContained;
    }
    else
    {
        if(doesCubeIntersectSphere(minCorner, maxCorner, c, r))
        {
            return PartlyIntersect;
        }
        else
        {
            return NoIntersect;
        }
    }
}

void KDTree::reportSubTree(KDNode *v, std::vector<glm::vec3> &reportedPoints)
{
    if(v->particles.size() == 1)
    {
        reportedPoints.push_back(*v->particles[0]);
    }
    else
    {
        if(v->leftChild)
        {
            reportSubTree(v->leftChild, reportedPoints);
        }
        if(v->rightChild)
        {
            reportSubTree(v->rightChild, reportedPoints);
        }
    }
}

void KDTree::searchKdTree(KDNode* v, std::vector<glm::vec3>& reportedPoints, glm::vec3 c, float r)
{
    if (v->particles.size() != 0 && (v->leftChild == nullptr && v->rightChild == nullptr))
    {
        if(glm::distance(*v->particles[0], c) <= r)
        {
            reportedPoints.push_back(*v->particles[0]);
        }
    }
    else
    {
        if(doesCubeIntersectSphere(v->leftChild->minCorner, v->leftChild->maxCorner, c, r))
        {
            searchKdTree(v->leftChild, reportedPoints, c, r);
        }
        if(doesCubeIntersectSphere(v->rightChild->minCorner, v->rightChild->maxCorner, c, r))
        {
            searchKdTree(v->rightChild, reportedPoints, c, r);
        }
    }

    /* Old version (backup):
    if(v->particles.size() == 1)
    {
        reportSubTree(v, reportedPoints);
    }
    else
    {
        if(v->leftChild)
        {
            IntersectState leftState = checkIntersection(c, r, v->leftChild->minCorner, v->leftChild->maxCorner);
            // std::cout << "leftState: " << leftState << std::endl;
            if(leftState == FullyContained)
            {
                reportSubTree(v->leftChild, reportedPoints);
            }
            else
            {
                if(leftState == PartlyIntersect)
                {
                    searchKdTree(v->leftChild, reportedPoints, c, r);
                }
            }
        }

        if(v->rightChild)
        {
            IntersectState rightState = checkIntersection(c, r, v->rightChild->minCorner, v->rightChild->maxCorner);
            // std::cout << "rightState: " << rightState << std::endl;
            if(rightState == FullyContained)
            {
                reportSubTree(v->rightChild, reportedPoints);
            }
            else
            {
                if(rightState == PartlyIntersect)
                {
                    searchKdTree(v->rightChild, reportedPoints, c, r);
                }
            }
        }
    }*/
}

std::vector<glm::vec3> KDTree::particlesInSphere(glm::vec3 c, float r)
{
    //TODO
    std::vector<glm::vec3> reportedPoints;
    searchKdTree(this->root, reportedPoints, c, r);
    // std::cout << "reportedpoints num: " << reportedPoints.size() << std::endl;
    return reportedPoints;
}

void clearTree(KDNode* iNode)
{
    if(iNode->particles.size() == 1)
    {
        delete iNode;
    }
    else
    {
        if(iNode->leftChild)
        {
            clearTree(iNode->leftChild);
        }
        if(iNode->rightChild)
        {
            clearTree(iNode->rightChild);
        }
        delete iNode;
    }
}

void KDTree::clear()
{

    delete root;
    // clearTree(root);
    root = nullptr;
}
