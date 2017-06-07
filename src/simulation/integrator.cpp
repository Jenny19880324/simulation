#include <iostream>
#include "integrator.h"
#include "minimizationMethod.h"

ImplicitIntegratorInterface *QuasiStatic::instance__ = 0;

ImplicitIntegratorInterface *QuasiStatic::Instance(){
	if(instance__ == 0){
		instance__ = new QuasiStatic();
	}
	return instance__;
}

void QuasiStatic::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) {
	mMinimizationMethod = minimizationMethod;
}


void QuasiStatic::solveMinimization() {
	mMinimizationMethod->solveMinimization(this);
}


void QuasiStatic::update(Simulation *simulation){
	std::cout << "update QuasiStatic " << std::endl;
	solveMinimization();
}



ImplicitIntegratorInterface *BackwardEuler::instance__ = 0;


ImplicitIntegratorInterface *BackwardEuler::Instance(){
	if(instance__ == 0){
		instance__ = new BackwardEuler();
	}
	return instance__;
}


void BackwardEuler::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) {
	mMinimizationMethod = minimizationMethod;
}


void BackwardEuler::solveMinimization(){
	mMinimizationMethod->solveMinimization(this);
}


void BackwardEuler::update(Simulation *simulation){
	std::cout << "update BackwardEuler " << std::endl;
	solveMinimization();
}

