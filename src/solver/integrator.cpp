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


void QuasiStatic::evaluateLaplacian(SpMat &laplacian) const {
	return mMinimizationExpression->evaluateLaplacian(laplacian);
}

void QuasiStatic::evaluateAppendedExpressionGradient(const SpMat &mDampingMatrix, const VectorX &x, VectorX &gradient) const {
}

void QuasiStatic::evaluateAppendedExpressionHessian(const SpMat &mDampingMatrix, SpMat &hessian) const {
}


void QuasiStatic::evaluateAppendedExpressionLaplacian(const SpMat &mDampingMatrix, SpMat &laplacian) const {
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


void BackwardEuler::solveMinimization(){
	mMinimizationMethod->solveMinimization(this);
}


void BackwardEuler::update(Solver *solver){
	std::cout << "update BackwardEuler " << std::endl;
	solveMinimization();
}

double BackwardEuler::evaluateEnergy(const VectorX &x) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	const VectorX y = currentPositions + currentVelocities * h;

	double inertiaTerm = 0.5 * (x - y).transpose() * massMatrix * (x - y);

	return inertiaTerm + h * mMinimizationExpression->evaluateEnergy(x);
}


void BackwardEuler::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	const SpMat &massMatrix = mSolver->getMassMatrix(); 
	double h = mSolver->getH();

	const VectorX y = currentPositions + currentVelocities * h;
	
	mMinimizationExpression->evaluateGradient(x, gradient);

	gradient = massMatrix * (x - y) + h * h * gradient;
}


void BackwardEuler::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	mMinimizationExpression->evaluateHessian(x, hessian);
	hessian = massMatrix + h * h * hessian;
}


void BackwardEuler::evaluateLaplacian(SpMat &laplacian) const {
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	mMinimizationExpression->evaluateLaplacian(laplacian);
	laplacian = massMatrix + h * h * laplacian;
}

void BackwardEuler::evaluateAppendedExpressionGradient(const SpMat &mDampingMatrix, const VectorX &x, VectorX &gradient) const {
}

void BackwardEuler::evaluateAppendedExpressionHessian(const SpMat &mDampingMatrix, SpMat &hessian) const {
}


void BackwardEuler::evaluateAppendedExpressionLaplacian(const SpMat &mDampingMatrix, SpMat &laplacian) const {
}







ImplicitIntegratorInterface *ImplicitMidpoint::instance__ = 0;


ImplicitIntegratorInterface *ImplicitMidpoint::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new ImplicitMidpoint(solver);
	}
	return instance__;
}


ImplicitMidpoint::ImplicitMidpoint(const Solver *solver) : mSolver(solver){
}


ImplicitMidpoint::~ImplicitMidpoint() {
}


void ImplicitMidpoint::solveMinimization() {
	mMinimizationMethod->solveMinimization(this);
}


void ImplicitMidpoint::update(Solver *solver) {
	std::cout << "Implicit Midpoint update" << std::endl;
	solveMinimization();
}

double ImplicitMidpoint::evaluateEnergy(const VectorX &x) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	const VectorX y =  currentPositions + currentVelocities * h;

	double inertiaTerm = 0.5 * (x - y).transpose() * massMatrix * (x - y);

	return inertiaTerm + h * mMinimizationExpression->evaluateEnergy((x + currentPositions) / 2);
}


void ImplicitMidpoint::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	const VectorX y = currentPositions + currentVelocities * h;

	mMinimizationExpression->evaluateGradient((x + currentPositions) / 2, gradient);
	gradient = massMatrix * (x - y) +  h * h / 2 * gradient;
}

void ImplicitMidpoint::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	mMinimizationExpression->evaluateHessian((x + currentPositions) / 2, hessian);
	hessian = massMatrix + h * h / 4 * hessian;
}

void ImplicitMidpoint::evaluateLaplacian(SpMat &laplacian) const {
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	mMinimizationExpression->evaluateLaplacian(laplacian);
	laplacian = massMatrix + h * h / 4 * laplacian;
}

void ImplicitMidpoint::evaluateAppendedExpressionGradient(const SpMat &mDampingMatrix, const VectorX &x, VectorX &gradient) const {
	double h = mSolver->getH();
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();

	VectorX v = 2.0 / h * (x - currentPositions) - currentVelocities;

	gradient = 2 * h * mDampingMatrix * v;
}

void ImplicitMidpoint::evaluateAppendedExpressionHessian(const SpMat &mDampingMatrix, SpMat &hessian) const {
	hessian = 4 * mDampingMatrix;
}


void ImplicitMidpoint::evaluateAppendedExpressionLaplacian(const SpMat &mDampingMatrix, SpMat &laplacian) const {
	laplacian = 4 * mDampingMatrix;
}

