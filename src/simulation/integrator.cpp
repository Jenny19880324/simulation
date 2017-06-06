#include <iostream>
#include "integrator.h"
#include "minimizationMethod.h"

void BackwardEuler::solveMinimization(){
	mMinimizationMethod->solveMinimization(this);
}

void BackwardEuler::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) {
	mMinimizationMethod = minimizationMethod;
}