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

  Image ** newlayers = new Image*[newmax];
  int *new_x=new int[newmax];
  int *new_y=new int[newmax];
  if(newlayers!= NULL && newmax>max && new_x!=NULL && new_y!=NULL)
    {
      for(int i=0; i<max; i++)
	newlayers[i]= layers[i];
        
      for(int i=max; i<newmax; i++)
        newlayers[i]=NULL;
        
       
      for(int i=0; i<max; i++)
        {
	  new_x[i]=xvals[i];
	  new_y[i]=yvals[i];
        }
      for(int i=max; i<newmax; i++)
        {
	  new_x[i]=0;
	  new_y[i]=0;
        }
      max=newmax;
    }
  else if(newmax==max)
    return;
  else
    cout <<"invalid newmax" <<endl;
        
  delete[] layers;
  layers=newlayers;
  newlayers=NULL;
  delete[] newlayers;

  delete[] xvals;
  xvals=new_x;
  new_x=NULL;
  delete[] new_x;

  delete[] yvals;
  yvals=new_y;
  new_y=NULL;
  delete[] new_y;
  
  _clear();

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
  layers = NULL;
  xvals = NULL;
  yvals = NULL;
}
