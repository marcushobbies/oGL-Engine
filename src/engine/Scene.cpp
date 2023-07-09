#include "engine/Scene.h"

Scene::Scene(){
    currentObjectCount = 0;
}

unsigned long Scene::addObject(Object object){
    objects.push_back(object);
    currentObjectCount++;
    return currentObjectCount;
}

void Scene::init(){
    ambientLightStrength = 1.0f; //Default ambient light at max.
    if(drawLightObjects){
        for(Light light : lights){
            lightDebugObjects.push_back(LightDebugObject(&light));
        }
    }
}

void Scene::render(Camera camera){
    for(Object obj : objects){
        obj.calculateLightingFromScene(camera, ambientLightStrength, lights, lights.size());
        obj.render(camera.getView(), camera.getProjection());
    }
    if(drawLightObjects){
        for(LightDebugObject lDO : lightDebugObjects){
            lDO.render(camera.getView(), camera.getProjection());
        }
    }
}

void Scene::update(){
    for(Object obj : objects){
        obj.update();
    }
    if(drawLightObjects){
        for(LightDebugObject lDO : lightDebugObjects){
            lDO.update();
        }
    }
}

void Scene::cleanUp(){
    for(Object obj : objects){
        obj.cleanUp();
    }
    if(drawLightObjects){
        for(LightDebugObject lDO : lightDebugObjects){
            lDO.cleanUp();
        }
    }
    objects.clear();
    lightDebugObjects.clear();
    lights.clear();
}