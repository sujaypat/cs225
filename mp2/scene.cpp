#include "scene.h"
#include "image.h"
#include <iostream>
using namespace std;

Scene::Scene(int m){

  max = m;
  things = new Image *[max];
  x = new int[max];
  y = new int[max];

  for(int i = 0; i < max; i++){
    things[i] = null;
    x[i] = 0;
    y[i] = 0;
  }

}

Scene::~Scene(){

  

}

Scene::Scene(const Scene &source){



}

void Scene::changemaxlayers(int newmax){



}

void Scene::addpicture (const char *FileName, int index, int x, int y){



}

void Scene::changelayer (int index, int newindex){



}

void Scene::translate(int index, int xcoord, int ycoord){



}

void Scene::deletepicture(int index){



}

Image Scene::*getpicture (int index) const{



}

Image Scene::drawscene() const {



}
