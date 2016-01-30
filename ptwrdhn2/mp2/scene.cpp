#include "scene.h"
#include "image.h"
#include <iostream>
using namespace std;


Scene::Scene (int m){
  max = m;
  layers = new Image *[max];
  yvals = new int[max];
  xvals = new int[max];
  for (int i = 0; i < m; i++){ 
      layers[i] = NULL;
      yvals[i] = 0;
      xvals[i] = 0;
    }
}


Scene::~Scene(){
  _clear();
}


Scene::Scene(const Scene &source){
  _copy(source);
}


const Scene & Scene::operator=(const Scene &source){
  if (this != &source) {
    _clear();
    _copy(source);
  }
  return *this;
}


void Scene::changemaxlayers(int newmax){
  if (newmax < max){
      for (int i = newmax; i < max; i++){
	  if (layers[i] == NULL){
	      cout<< "invalid new max" << endl;
	      return;
            }
        }
    }


  Image **nlayers = new Image *[newmax];
  int *nxvals = new int[newmax];
  int *nyvals = new int[newmax];


  for (int i =0; i < newmax; i++){
      nlayers[i] = NULL;
      nxvals[i] = 0;
      nyvals[i] = 0;
  }

  int smaller = (newmax<max)?newmax:max;

  for (int i = 0; i< smaller;i++){
      *nlayers[i] = *layers[i];
      nxvals[i] = xvals[i];
      nyvals[i] = yvals[i];
  }

  _clear();


  layers = nlayers;
  xvals = nxvals;
  yvals = nyvals;

}


void Scene::addpicture(const char *FileName, int index, int x, int y){

  if (index < max && index >=0){

      Image *image = new Image();
      image->readFromFile(FileName);

      if (layers[index] != NULL)
	delete layers[index];
        
      layers[index] = image;
        

      xvals[index] = x;
      yvals[index] = y;
    } 
  else
    cout<< "index out of bounds" << endl;
}


void Scene::changelayer (int index, int newindex){   
  if((index >=0 && index < max)&&(newindex >=0 && newindex <max)){
      if (index == newindex)
	return;

      if(layers[newindex]!=NULL)
	delete layers[newindex];

      layers[newindex] = layers[index];
      layers[index] = NULL;

      xvals[newindex] = xvals[index];
      yvals[newindex] = yvals[index];
      xvals[index] = 0;
      yvals[index] = 0;
    } else
    cout <<"invalid index" <<endl;   
}


void Scene::translate(int index, int xval, int yval){

  if ((index>=0&&index<max)&&(layers[index]!=NULL)){
      xvals[index] = xval;
      yvals[index] = yval;
    } else
    cout<<"invalid index" <<endl;
}


void Scene::deletepicture(int index){

  if ((index>=0&&index<max)&&(layers[index]!=NULL)){
      delete layers[index];
      layers[index] = NULL;
      xvals[index] = 0;
      yvals[index] = 0;
    }
  else
    cout <<"invalid index"<<endl;

}


Image * Scene::getpicture(int index) const{

  if ((index < max) && (index >=0)){
      return layers[index];
    }
  else{   
      cout<<"invalid index"<<endl;
      return NULL;
    }
}


Image Scene::drawscene() const{

  unsigned long min_height = 0;
  unsigned long min_width = 0;
  for(int i = 0; i < max; i++){
      if(layers[i] != NULL)
        {
	  cout << "Layer number: "<< i << endl;
	  if(min_height < (layers[i]->height() + yvals[i]))
	    min_height = layers[i]->height() + yvals[i];
	  if(min_width < (layers[i]->width() + xvals[i]))
	    min_width = layers[i]->width() + xvals[i];
        }
    }

  Image res;
  res.resize(min_width,min_height);
    
    
  for(int index = 0; index < max;index++){
      if (layers[index] != NULL){
	  for(size_t x = 0; x < layers[index]->width(); x++){
	      for(size_t y = 0; y < layers[index]->height(); y++){
		  *res(xvals[index]+x,yvals[index]+y) = *(*layers[index])(x,y);
              }
          }
      }
  }
    
  return res;
}

void Scene::_copy(const Scene & other){
  max = other.max;
  layers = new Image *[max];
  xvals = new int[max];
  yvals = new int[max];
  for (int i = 0;i < max; i++){
      if (other.layers[i] != NULL) {
	layers[i] = new Image(*(other.layers[i]));
      }
      else
	layers[i] = NULL;
            
      xvals[i] = other.xvals[i];
      yvals[i] = other.yvals[i];
    }
}

void Scene::_clear(){
  for (int i=0;i<max;i++){
      delete layers[i];
    }
  delete [] layers;
  delete [] xvals;
  delete [] yvals;
}
