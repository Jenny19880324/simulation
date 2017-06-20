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

bool ForwardEuler::update() {
	return true;
}










ImplicitIntegratorInterface *QuasiStatic::instance__ = 0;

ImplicitIntegratorInterface *QuasiStatic::Instance(Solver *solver){
	if(instance__ == 0){
		instance__ = new QuasiStatic(solver);
	}
	return instance__;
}


QuasiStatic::QuasiStatic(Solver *solver) : mSolver(solver) {
}


QuasiStatic::~QuasiStatic(){
}

void QuasiStatic::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) { 
	mMinimizationMethod = minimizationMethod; 
}


void QuasiStatic::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression)  { 
	mMinimizationExpression = minimizationExpression; 
	mMinimizationMethod->setMinimizationExpression(minimizationExpression);
}


bool QuasiStatic::solveMinimization(VectorX &x) {
	return mMinimizationMethod->solveMinimization(this, x);
}


bool QuasiStatic::update(){
	std::cout << "update QuasiStatic " << std::endl;

	VectorX x;
	return solveMinimization(x);
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


ImplicitIntegratorInterface *BackwardEuler::Instance(Solver *solver){
	if(instance__ == 0){
		instance__ = new BackwardEuler(solver);
	}
	return instance__;
}


BackwardEuler::BackwardEuler(Solver *solver) : mSolver(solver){
}


BackwardEuler::~BackwardEuler() {
}


void BackwardEuler::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) {
	mMinimizationMethod = minimizationMethod;
}


void BackwardEuler::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression;
	mMinimizationMethod->setMinimizationExpression(minimizationExpression);
}


bool BackwardEuler::solveMinimization(VectorX &x){
	return mMinimizationMethod->solveMinimization(this, x);
}


bool BackwardEuler::update(){
	std::cout << "update BackwardEuler " << std::endl;

	VectorX x;
	return solveMinimization(x);
}

double BackwardEuler::evaluateEnergy(const VectorX &x) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	const VectorX y = currentPositions + currentVelocities * h;

	double inertiaTerm = 0.5 * (x - y).transpose() * massMatrix * (x - y);

	return inertiaTerm + h * h * mMinimizationExpression->evaluateEnergy(x);
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


ImplicitIntegratorInterface *ImplicitMidpoint::Instance(Solver *solver) {
	if (instance__ == 0) {
		instance__ = new ImplicitMidpoint(solver);
	}
	return instance__;
}


ImplicitMidpoint::ImplicitMidpoint(Solver *solver) : mSolver(solver){
}


ImplicitMidpoint::~ImplicitMidpoint() {
}


void ImplicitMidpoint::setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) { 
	mMinimizationMethod = minimizationMethod;
}


void ImplicitMidpoint::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression; 
	mMinimizationMethod->setMinimizationExpression(minimizationExpression);
}


bool ImplicitMidpoint::solveMinimization(VectorX &x) {
	return mMinimizationMethod->solveMinimization(this, x);
}


bool ImplicitMidpoint::update() {
	VectorX x;
	if (!solveMinimization(x)) {
		return false;
	}

	const VectorX &previousPositions = mSolver->getCurrentPositions();
	const VectorX &previousVelocities = mSolver->getCurrentVelocities();
	double h = mSolver->getH();

	VectorX v = (x - previousPositions) * 2 / h - previousVelocities;

	mSolver->setCurrentPositions(x);
	mSolver->setCurrentVelocities(v);

	return true;
}


double ImplicitMidpoint::evaluateEnergy(const VectorX &x) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	const VectorX y =  currentPositions + currentVelocities * h;

	double inertiaTerm = 0.5 * (x - y).transpose() * massMatrix * (x - y);

	double energy = NoDamping::Instance(mSolver)->evaluateEnergy((x + currentPositions) / 2);

	double dampingEnergy = mMinimizationExpression->evaluateEnergy(x);

	return inertiaTerm + h * h * energy + h * h * dampingEnergy;
}


void ImplicitMidpoint::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	const VectorX y = currentPositions + currentVelocities * h;

	NoDamping::Instance(mSolver)->evaluateGradient((x + currentPositions) / 2, gradient);

	VectorX dampingGradient;
	mMinimizationExpression->evaluateGradient(x, dampingGradient);

	gradient = massMatrix * (x - y) +  h * h / 2 * gradient + h * h * dampingGradient;
}


void ImplicitMidpoint::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const SpMat &massMatrix = mSolver->getMassMatrix();
	double h = mSolver->getH();

	NoDamping::Instance(mSolver)->evaluateHessian((x + currentPositions) / 2, hessian);

	SpMat dampingHessian;

	mMinimizationExpression->evaluateHessian(x, dampingHessian);
	hessian = massMatrix + h * h / 4 * hessian + h * h *dampingHessian;
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

	gradient = 2 * mDampingMatrix * v;
}


void ImplicitMidpoint::evaluateAppendedExpressionHessian(const SpMat &mDampingMatrix, SpMat &hessian) const {
	double h = mSolver->getH();
	hessian = 4 * mDampingMatrix / h;
}


void ImplicitMidpoint::evaluateAppendedExpressionLaplacian(const SpMat &mDampingMatrix, SpMat &laplacian) const {
	double h = mSolver->getH();
	laplacian = 4 * h * mDampingMatrix;
}

