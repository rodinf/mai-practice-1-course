/*
  Rodin Fedor m3o-121b-20
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "imgutils.cpp"

#define PHYS_G 9.8

double 
  ENERGY_LOSS = 0.5,
  H_0,
  V_0,
  finalSimulationTime; // max 1.0

const double
  MAX_SIMULATE_TIME = 1000,
  TIME_STEP = 0.01,
  H_THRESHOLD = 0.01, // using small value can cause long-time calculation
  Vx_THRESHOLD = 0.0001,
  Vy_THRESHOLD = 0.0001; // cannot be 0

struct TypicalBall
{
  double
    h_0,
    v_0;
};

struct TypicalPoletPoint {
  double
    h,
    l,
    t;
  int 
    collision = 0,
    h_max = 0;
  TypicalPoletPoint* nextPoint;
};

void simulatePolet(TypicalPoletPoint *_PoletPoint, TypicalBall *_Ball, double startTime, double endTime, double intervalTime)
{
  _PoletPoint->h = _Ball->h_0 - PHYS_G * pow(startTime, 2) / 2;
  _PoletPoint->t = startTime;

  double 
    collision_timestamp = 0,
    Vx = _Ball->v_0,
    Vy_max,
    h_max = __DBL_MAX__;

  /* Шар брошен горизонтально */
  
  for(double dt = startTime + intervalTime; dt <= endTime; dt += intervalTime) 
  {
    _PoletPoint->nextPoint = new TypicalPoletPoint;
    _PoletPoint = _PoletPoint->nextPoint;
    
    _PoletPoint->h = _Ball->h_0 - PHYS_G * pow(dt, 2) / 2;
    _PoletPoint->l = Vx * dt;
    _PoletPoint->t = dt;

    _PoletPoint->nextPoint = NULL;

    if((_Ball->h_0 - PHYS_G * pow(dt + intervalTime, 2) / 2) < 0) { 
      _PoletPoint->collision = 1;
      Vy_max = PHYS_G * dt;
      collision_timestamp = dt;
      break;
    }
  }

  /* Шар отскакивает */ 

  while (h_max > H_THRESHOLD)
  {
    int h_max_trigger = 0; 

    Vx *= (1 - ENERGY_LOSS);
    Vy_max *= (1 - ENERGY_LOSS);

    if(Vx < Vx_THRESHOLD || Vy_max < Vy_THRESHOLD)
      return;

    for(double dt = 0; dt < endTime - collision_timestamp; dt += intervalTime)
    {

      if(dt + collision_timestamp + 1 > endTime)
        return;

      double prev_h = _PoletPoint->h;

      TypicalPoletPoint *_PoletPoint_prev = _PoletPoint;

      _PoletPoint->nextPoint = new TypicalPoletPoint;
      _PoletPoint = _PoletPoint->nextPoint;

      _PoletPoint->h = Vy_max * dt - PHYS_G * pow(dt, 2) / 2;
      _PoletPoint->l = _PoletPoint_prev->l + Vx * dt;
      _PoletPoint->t = dt + collision_timestamp;

      if(_PoletPoint->h < prev_h && _PoletPoint_prev->collision == 0 && h_max_trigger == 0) {
        h_max = prev_h;
        h_max_trigger = 1;
        _PoletPoint_prev->h_max = 1;
      }
      else if(_PoletPoint->h > prev_h) {
        h_max_trigger = 0;
      }

      if(_PoletPoint->h < 0) {
        _PoletPoint->collision = 1;
        collision_timestamp += dt;
        break;
      }
    }
  }

  finalSimulationTime = collision_timestamp;
}

void printPolet(TypicalPoletPoint *_PoletPoint)
{
  printf("Height, h\tRange, l\tTime, t\n------------\t------------\t------------\n");
  while (_PoletPoint != NULL)
  {
    printf("h = %f\tl = %f\tt = %f", _PoletPoint->h, _PoletPoint->l, _PoletPoint->t);

    _PoletPoint->h_max ? printf(" < max\n") : printf("\n");

    if(_PoletPoint->collision == 1)
      printf("\ncollision at t = %f\n\n", _PoletPoint->t);
    _PoletPoint = _PoletPoint->nextPoint;
  }
}

void freePoletPoints(TypicalPoletPoint *_PoletPoint)
{
  TypicalPoletPoint *_PoletTempPtr = _PoletPoint->nextPoint;

  while (_PoletPoint != NULL)
  {
    _PoletTempPtr = _PoletPoint;
    _PoletPoint = _PoletPoint->nextPoint;
    delete _PoletTempPtr;
  }	
}

void saveSimulationToPnm(TypicalPoletPoint* _PoletPoint, Image* img)
{
	const int l_scale = 100;
	const double h_scale = 10;

	TypicalPoletPoint* _PoletPoint_current = _PoletPoint;

	while (_PoletPoint_current->nextPoint != NULL)
	{
		setPointImage(img, abs((int)(l_scale * _PoletPoint_current->t)), abs(img->my - (int)(h_scale * _PoletPoint_current->h)), 1);
		_PoletPoint_current = _PoletPoint_current->nextPoint;
	}

	saveImage(img, "polet.pnm");
	
  printf("\nImage saved successfully: polet.pnm\n");
}

int main() 
{
  H_0 = 10;
  V_0 = 5;

  TypicalPoletPoint* Polet = new TypicalPoletPoint;

  TypicalBall* Ball = new TypicalBall;
  Ball->h_0 = H_0;
  Ball->v_0 = V_0;

  printf("\n");
   
  simulatePolet(Polet, Ball, 0, MAX_SIMULATE_TIME, TIME_STEP);
  
  printPolet(Polet);
  printf("-----\n");
  printf("Energy loss: %f\nSimulation time: %f\nSimulation time step: %f\n", ENERGY_LOSS, finalSimulationTime, TIME_STEP);

  Image* image = new Image;

  createImage(image, 1000, 100);
  
  saveSimulationToPnm(Polet, image);

  freePoletPoints(Polet);
  
  return 0;
}

