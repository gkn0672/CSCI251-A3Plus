#ifndef MYGRAPHIC_H
#define MYGRAPHIC_H
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "algo.h"
void GenerateP2D(Point2D p);
void GenerateP3D(Point3D p);
void GenerateL2D(Line2D l);
void GenerateL3D(Line3D l);
Point2D Normalize(Point3D p);
#endif