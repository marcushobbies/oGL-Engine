#include "engine/Scene.h"

Scene::Scene(){
    currentObjectCount = 0;
}

unsigned long Scene::addObject(Object object){
    objects.push_back(object);
    currentObjectCount++;
}

void Scene::init(){
    ambientLightStrength = 1.0f; //Default ambient light at max.
}

void Scene::render(Camera camera){
    for(Object obj : objects){
        obj.calculateLightingFromScene(camera, ambientLightStrength);
        obj.render(camera.getView(), camera.getProjection());
    }
}

void Scene::update(){
    for(Object obj : objects){
        obj.update();
    }
}

void Scene::cleanUp(){
    for(Object obj : objects){
        obj.cleanUp();
    }
    objects.clear();
}