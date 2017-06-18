#include <iostream>
#include "integrator.h"
#include "minimizationMethod.h"
#include "minimizationExpression.h"
#include "solver.h"

ExplicitIntegratorInterface *ForwardEuler::instance__ = 0;

ExplicitIntegratorInterface *ForwardEuler::Instance() {
	if (instance__ == 0) {
		instance__ = new ForwardEuler();
	}
	return instance__;
}

void ForwardEuler::update(Solver *sim) {

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


void QuasiStatic::update(Solver *solver){
	std::cout << "update QuasiStatic " << std::endl;
	solveMinimization();
}


double QuasiStatic::evaluateEnergy(const VectorX &x) const {
	return mMinimizationExpression->evaluateEnergy(x);
}


void QuasiStatic::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	return mMinimizationExpression->evaluateGradient(x, gradient);
}


void QuasiStatic::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	return mMinimizationExpression->evaluateHessian(x, hessian);
}


void QuasiStatic::evaluateLaplacian(const VectorX &x, SpMat &laplacian) const {
	return mMinimizationExpression->evaluateHessian(x, laplacian);
}



ImplicitIntegratorInterface *BackwardEuler::instance__ = 0;


ImplicitIntegratorInterface *BackwardEuler::Instance(const Solver *solver){
	if(instance__ == 0){
		instance__ = new BackwardEuler(solver);
	}
	return instance__;
}


BackwardEuler::BackwardEuler(const Solver *solver) : mSolver(solver){
}


BackwardEuler::~BackwardEuler() {
}

void BackwardEuler::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) {
	mMinimizationMethod = minimizationMethod;
}


void BackwardEuler::solveMinimization(){
	mMinimizationMethod->solveMinimization(this);
}


void BackwardEuler::update(Solver *solver){
	std::cout << "update BackwardEuler " << std::endl;
	solveMinimization();
}

double BackwardEuler::evaluateEnergy(const VectorX &x) const {
	const VectorX &y = mSolver->getY();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	double inertiaTerm = 0.5 * (x - y).transpose() * massMatrix * (x - y);
	return inertiaTerm + h * mMinimizationExpression->evaluateEnergy(x);
}


void BackwardEuler::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	const VectorX &y = mSolver->getY();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	mMinimizationExpression->evaluateGradient(x, gradient);
	gradient = massMatrix * (x - y) + h * h * gradient;
}


void BackwardEuler::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	const VectorX &y = mSolver->getY();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	mMinimizationExpression->evaluateHessian(x, hessian);
	hessian = massMatrix + h * h * hessian;
}


void BackwardEuler::evaluateLaplacian(const VectorX &x, SpMat &laplacian) const {
	const VectorX &y = mSolver->getY();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	mMinimizationExpression->evaluateHessian(x, laplacian);
	laplacian = massMatrix + h * h * laplacian;
}



