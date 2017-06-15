#include <iostream>
#include "integrator.h"
#include "minimizationMethod.h"
ExplicitIntegratorInterface *ForwardEuler::instance__ = 0;

ExplicitIntegratorInterface *ForwardEuler::Instance() {
	if (instance__ == 0) {
		instance__ = new ForwardEuler();
	}
	return instance__;
}

void ForwardEuler::update(Simulation *sim) {

}



ExplicitIntegratorInterface *ExplicitSymplectic::instance__ = 0;

ExplicitIntegratorInterface *ExplicitSymplectic::Instance() {
	if (instance__ == 0) {
		instance__ = new ExplicitSymplectic();
	}
	return instance__;
}

void ExplicitSymplectic::update(Simulation *sim) {

}

ExplicitIntegratorInterface *ExplicitMidpoint::instance__ = 0;

ExplicitIntegratorInterface *ExplicitMidpoint::Instance() {
	if (instance__ == 0) {
		instance__ = new ExplicitMidpoint();
	}
	return instance__;
}

void ExplicitMidpoint::update(Simulation *sim) {

}

ExplicitIntegratorInterface *RungeKutta4::instance__ = 0;

ExplicitIntegratorInterface *RungeKutta4::Instance() {
	if (instance__ == 0) {
		instance__ = new RungeKutta4();
	}
	return instance__;
}

void RungeKutta4::update(Simulation *sim) {

}


ExplicitIntegratorInterface *AdaptiveRungeKutta::instance__ = 0;

ExplicitIntegratorInterface *AdaptiveRungeKutta::Instance() {
	if (instance__ == 0) {
		instance__ = new AdaptiveRungeKutta();
	}
	return instance__;
}

void AdaptiveRungeKutta::update(Simulation *sim) {

}









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


BackwardEuler::BackwardEuler() {

}


BackwardEuler::~BackwardEuler() {

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





ImplicitIntegratorInterface *BDF2::instance__ = 0;


ImplicitIntegratorInterface *BDF2::Instance() {
	if (instance__ == 0) {
		instance__ = new BDF2();
	}
	return instance__;
}


BDF2::BDF2() {

}


BDF2::~BDF2() {

}

void BDF2::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) {
	mMinimizationMethod = minimizationMethod;
}


void BDF2::solveMinimization() {
	mMinimizationMethod->solveMinimization(this);
}


void BDF2::update(Simulation *simulation) {
	std::cout << "update BDF2 " << std::endl;
	solveMinimization();
}


