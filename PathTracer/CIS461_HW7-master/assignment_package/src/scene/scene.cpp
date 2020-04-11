#include <scene/scene.h>

#include <scene/geometry/cube.h>
#include <scene/geometry/sphere.h>
#include <scene/geometry/mesh.h>
#include <scene/geometry/squareplane.h>
#include <scene/geometry/csg.h>
#include <scene/materials/mattematerial.h>
#include <scene/lights/diffusearealight.h>
#include <scene/lights/pointlight.h>
#include <scene/lights/spotlight.h>
#include <scene/lights/distantlight.h>


Scene::Scene()
{}

void Scene::SetCamera(const Camera &c)
{
    camera = Camera(c);
    camera.create();
    film.SetDimensions(c.width, c.height);
    mCameraPtr = &camera;
}

void Scene::SetThinLensCamera(const ThinLensCamera &c)
{
    tlCamera = ThinLensCamera(c);
    tlCamera.create();

    camera = Camera(c);

    camera.create();

    film.SetDimensions(c.width, c.height);
    mCameraPtr = &tlCamera;
}

bool Scene::Intersect(const Ray &ray, Intersection *isect) const
{
    bool result = false;
    for(std::shared_ptr<Primitive> p : primitives)
    {
        Intersection testIsect;
        if(p->Intersect(ray, &testIsect))
        {
            if(testIsect.t < isect->t || isect->t < 0)
            {
                *isect = testIsect;
                result = true;
            }
        }
    }
    return result;
}

// Long cube



void Scene::CreateTestScene()
{
    //Floor
    //Area light
    //Figure in front of light

    auto matteWhite = std::make_shared<MatteMaterial>(Color3f(0.725, 0.71, 0.68), 0, nullptr, nullptr);
    auto matteRed = std::make_shared<MatteMaterial>(Color3f(0.63, 0.065, 0.05), 0, nullptr, nullptr);
    auto matteGreen = std::make_shared<MatteMaterial>(Color3f(0.14, 0.45, 0.091), 0, nullptr, nullptr);

    // Floor, which is a large white plane
    auto floor = std::make_shared<SquarePlane>();
    floor->transform = Transform(Vector3f(0,-2.5,0), Vector3f(-90,0,0), Vector3f(10,10,1));
    auto floorPrim = std::make_shared<Primitive>(floor);
    floorPrim->material = matteWhite;
    floorPrim->name = QString("Floor");

    // Left wall, which is a large red plane
    auto leftWall = std::make_shared<SquarePlane>();
    leftWall->transform = Transform(Vector3f(5,2.5,0), Vector3f(0,-90,0), Vector3f(10,10,1));
    auto leftWallPrim = std::make_shared<Primitive>(leftWall);
    leftWallPrim->material = matteRed;
    leftWallPrim->name = QString("Left Wall");

    // Right wall, which is a large green plane
    auto rightWall = std::make_shared<SquarePlane>();
    rightWall->transform = Transform(Vector3f(-5,2.5,0), Vector3f(0,90,0), Vector3f(10,10,1));
    auto rightWallPrim = std::make_shared<Primitive>(rightWall);
    rightWallPrim->material = matteGreen;
    rightWallPrim->name = QString("Right Wall");

    // Back wall, which is a large white plane
    auto backWall = std::make_shared<SquarePlane>();
    backWall->transform = Transform(Vector3f(0,2.5,5), Vector3f(0,180,0), Vector3f(10,10,1));
    auto backWallPrim = std::make_shared<Primitive>(backWall);
    backWallPrim->material = matteWhite;
    backWallPrim->name = QString("Back Wall");

    // Ceiling, which is a large white plane
    auto ceiling = std::make_shared<SquarePlane>();
    ceiling->transform = Transform(Vector3f(0,7.5,0), Vector3f(90,0,0), Vector3f(10,10,1));
    auto ceilingPrim = std::make_shared<Primitive>(ceiling);
    ceilingPrim->material = matteWhite;
    ceilingPrim->name = QString("Ceiling");

    // Long cube
    auto longCube = std::make_shared<Cube>();
    longCube->transform = Transform(Vector3f(2, 0, 3), Vector3f(0, 27.5, 0), Vector3f(3, 6, 3));
    auto longCubePrim = std::make_shared<Primitive>(longCube);
    longCubePrim->material = matteWhite;
    longCubePrim->name = QString("Long Cube");

    // Short cube
    auto shortCube = std::make_shared<Cube>();
    shortCube->transform = Transform(Vector3f(-2, -1, 0.75), Vector3f(0, -17.5, 0), Vector3f(3, 3, 3));
    auto shortCubePrim = std::make_shared<Primitive>(shortCube);
    shortCubePrim->material = matteWhite;
    shortCubePrim->name = QString("Short Cube");


/*
    auto longCube = std::make_shared<Cube>();
    longCube->transform = Transform(Vector3f(0, 0, 0), Vector3f(0, 27.5, 0), Vector3f(3, 6, 3));
    auto longCubePrim = std::make_shared<Primitive>(longCube);
    longCubePrim->material = matteWhite;
    longCubePrim->name = QString("Long Cube");

    auto sphere = std::make_shared<Sphere>();
    sphere->transform = Transform(Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(3, 3, 3));
    auto spherePrim = std::make_shared<Primitive>(sphere);
    spherePrim->material = matteWhite;
    spherePrim->name = QString("Sphere");
 */
/*
    // CSG:
    auto longCube1 = std::make_shared<Cube>();
    longCube1->transform = Transform(Vector3f(0, 0, 0), Vector3f(90, 0, -27.5), Vector3f(3, 6, 3));
    auto csgCube1 = std::make_shared<CSGNode>();
    csgCube1->mType = GEOMETRY;
    csgCube1->selfGeo =longCube1.get();

    auto longCube2 = std::make_shared<Cube>();
    longCube2->transform = Transform(Vector3f(0, 0, 0), Vector3f(90, 0, 62.5), Vector3f(3, 6, 3));
    auto csgCube2 = std::make_shared<CSGNode>();
    csgCube2->mType = GEOMETRY;
    csgCube2->selfGeo =longCube2.get();
*/
    // Large sphere:
    /*auto sphere = std::make_shared<Sphere>();
    sphere->transform = Transform(Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(3, 3, 3));
    auto csgSphere = std::make_shared<CSGNode>();
    csgSphere->mType = GEOMETRY;
    csgSphere->selfGeo = sphere.get();

    auto longCube3 = std::make_shared<Cube>();
    longCube3->transform = Transform(Vector3f(0, 0, 0), Vector3f(0, 27.5, 0), Vector3f(3, 6, 3));
    auto csgCube3 = std::make_shared<CSGNode>();
    csgCube3->mType = GEOMETRY;
    csgCube3->selfGeo =longCube3.get();


    auto csgLeftDiffer = std::make_shared<CSGNode>();
    csgLeftDiffer->mType = UNION;
    csgLeftDiffer->leftChild = csgCube2.get();
    csgLeftDiffer->rightChild = csgCube3.get();


    auto csgRightUnion = std::make_shared<CSGNode>();
    csgRightUnion->mType = UNION;
    csgRightUnion->leftChild = csgCube2.get();
    csgRightUnion->rightChild = csgCube1.get();


    auto csgRoot = std::make_shared<CSGNode>();
    csgRoot->mType = INTERSECT;
    csgRoot->leftChild = csgLeftDiffer.get();
    csgRoot->rightChild = csgSphere.get();

    auto csgPrim = std::make_shared<Primitive>(csgRoot);
    csgPrim->material = matteWhite;
    csgPrim->name = QString("csg Primitive");


    CSGShapes.append(csgCube2);
    CSGShapes.append(csgCube3);

    CSGShapes.append(longCube2);
    CSGShapes.append(longCube3);

    CSGShapes.append(csgLeftDiffer);

    CSGShapes.append(sphere);
    CSGShapes.append(csgSphere);
*/
/*
    auto longCube1 = std::make_shared<Cube>();
    longCube1->transform = Transform(Vector3f(0, 0, 0), Vector3f(90, 0, -27.5), Vector3f(3, 6, 3));
    auto longCubePrim1 = std::make_shared<Primitive>(longCube1);
    longCubePrim1->material = matteWhite;
    longCubePrim1->name = QString("Long Cube");

    auto longCube2 = std::make_shared<Cube>();
    longCube2->transform = Transform(Vector3f(0, 0, 0), Vector3f(90, 0, 62.5), Vector3f(3, 6, 3));
    auto longCubePrim2 = std::make_shared<Primitive>(longCube2);
    longCubePrim2->material = matteWhite;
    longCubePrim2->name = QString("Long Cube");
*/


    // auto csgCube1 = std::make_shared<CSGNode>();
    // csgCube1->mType = GEOMETRY;
    // csgCube1->selfGeo =longCube1.get();

    // Light source, which is a diffuse area light with a large plane as its shape
    auto lightSquare = std::make_shared<SquarePlane>();
    // lightSquare->transform = Transform(Vector3f(0,7.45f,0), Vector3f(90,0,0), Vector3f(3, 3, 1));
    // auto lightSource = std::make_shared<DiffuseAreaLight>(lightSquare->transform, Color3f(17,12,4) * 2.f, lightSquare);
    // auto lightPrim = std::make_shared<Primitive>(lightSquare, nullptr, lightSource);

    // auto pointLightSource = std::make_shared<PointLight>(lightSquare->transform, Color3f(17,12,4) * 4.f);
    // auto SpotLightSource = std::make_shared<SpotLight>(lightSquare->transform, Color3f(17,12,4) * 4.f, 30, 25);
    // lightPrim->name = QString("Light Source");

    auto distantLightSource = std::make_shared<DistantLight>(Transform(Point3f(16, 20, -20), Vector3f(0,0,0), Vector3f(1, 1, 1)), Color3f(17,12,4) * 30.f, Vector3f(-0.2, -0.2, 1), 100.f);

    primitives.append(floorPrim);
    // primitives.append(lightPrim);
    primitives.append(leftWallPrim);
    primitives.append(rightWallPrim);
    primitives.append(backWallPrim);
    primitives.append(ceilingPrim);
    // primitives.append(longCubePrim2);
    // primitives.append(longCubePrim1);
    // primitives.append(longCubePrim);
    // primitives.append(spherePrim);

    // primitives.append(csgPrim);
    primitives.append(longCubePrim);
    primitives.append(shortCubePrim);

    // lights.append(lightSource);
    // lights.append(pointLightSource);
    // lights.append(SpotLightSource);
    lights.append(distantLightSource);


    for(std::shared_ptr<Primitive> p : primitives)
    {
        p->shape->create();
    }

    camera = Camera(400, 400, Point3f(0, 5.5, -30), Point3f(0,2.5,0), Vector3f(0,1,0));
    camera.near_clip = 0.1f;
    camera.far_clip = 100.0f;
    camera.fovy = 19.5f;
    camera.create();
    camera.RecomputeAttributes();
    film = Film(400, 400);
    mCameraPtr = &camera;
}

void Scene::Clear()
{
    // These lists contain shared_ptrs
    // so the pointers will be freed
    // if appropriate when we clear the lists.
    primitives.clear();
    lights.clear();
    materials.clear();
    camera = Camera();
    film = Film();
}
