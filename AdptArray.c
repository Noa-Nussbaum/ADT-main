// Sources:
// I used a file about ADT from one of the exercise classes last term
// I also used the solutions from the C course test last term

#include <string.h>
#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef struct AdptArray_{
  PElement* ArrElements;
  int size;
  COPY_FUNC copy;
  DEL_FUNC delete;
  PRINT_FUNC print;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete,PRINT_FUNC print){
  // Initiate new array
  PAdptArray array;
  array = (PAdptArray)malloc(sizeof(AdptArray));
  if(array==NULL){
    return NULL;
  }
  array->ArrElements=NULL;
  array->size=0;
  array->copy=copy;
  array->delete=delete;
  array->print=print;

  return array;
}

void DeleteAdptArray(PAdptArray array){
  if(array!=NULL){
  for(int i=0;i<array->size;i++){
    if(array->ArrElements[i]){
      array->delete(array->ArrElements[i]);
    }
  }
  }
  free(array->ArrElements);
  free(array);
}

Result SetAdptArrayAt(PAdptArray array, int index, PElement element){
  // Create copy
  PElement newArray=NULL; 
  // If the index is greater than the current size, create larger array and copy existing elements
  if(index>=array->size){
    newArray = (PAdptArray*)calloc((index+1),sizeof(PElement));
    if(newArray==NULL){
      return FAIL;
    }
    // Move elements from original to new array address
    memcpy(newArray,array->ArrElements,array->size*sizeof(PElement));
    free(array->ArrElements);
    array->ArrElements=newArray;
  }

  // Delete existing element at index
  
  // array->delete((array->ArrElements)[index]);
  if((array->ArrElements)[index]!=NULL){
    array->delete((array->ArrElements)[index]);
  }
  // Put new element at index using copy function
  (array->ArrElements)[index]=array->copy(element);
  // Update size
  if(index>=array->size){
    array->size=index+1;
  }
  return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray array, int index){
  if(array->ArrElements==NULL){
    return NULL;
  }
  PElement object;

  if(array->ArrElements[index]!=NULL){
    object = array->copy(array->ArrElements[index]);
  }
  else{
    return NULL;
  }
  return object;
}

int GetAdptArraySize(PAdptArray array){
  if(array->ArrElements==NULL){
    return -1;
  }
  return array->size;
}

void PrintDB(PAdptArray array){
  if(array->ArrElements!=NULL){
    for(int i=0; i<array->size;i++){
      if(array->ArrElements[i]!=NULL){
        array->print(array->ArrElements[i]);
      }
    }
  }
}

