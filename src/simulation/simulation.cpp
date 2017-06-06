#include <iostream>
#include "simulation.h"

void BackwardEuler::solveMinimization(){
	mMinimizationMethod->solveMinimization(this);
}

void BackwardEuler::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) {
	mMinimizationMethod = minimizationMethod;
}

MinimizationMethodInterface *NewtonsMethod::mInstance = 0;

MinimizationMethodInterface *NewtonsMethod::Instance() {
	if (mInstance == 0) {
		mInstance = new NewtonsMethod();
	}
	return mInstance;
}

void NewtonsMethod::solveMinimization(ImplicitIntegratorInterface *integrator){
	std::cout << "Newton's method : solve minimization" << std::endl;
}



MinimizationMethodInterface *ProjectiveDynamics::mInstance = 0;

MinimizationMethodInterface *ProjectiveDynamics::Instance() {
	if (mInstance == 0) {
		mInstance = new ProjectiveDynamics();
	}
	return mInstance;
}

void ProjectiveDynamics::solveMinimization(ImplicitIntegratorInterface *integrator){
	std::cout << "ProjectiveDynamics : solve minimization" << std::endl;
}



