#include <iostream>
#include "minimizationExpression.h"
#include "lineSearch.h"
#include "constraint.h"
#include "solver.h"
#include "integrator.h"



MinimizationExpressionInterface *PureConstraint::instance__ = 0;


MinimizationExpressionInterface *PureConstraint::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new PureConstraint(solver);
	}
	return instance__;
}


PureConstraint::PureConstraint(const Solver *solver) : mSolver(solver) {
}


double PureConstraint::evaluateEnergy(const VectorX &x) const {
	double energy = 0.0;

	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	for (auto constraint : constraints) {
		energy += constraint->evaluateEnergy(x);
	}

	return energy;
}


void PureConstraint::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	for (auto constraint : constraints) {
		constraint->evaluateGradient(x, gradient);
	}
}


void PureConstraint::evaluateLaplacian(SpMat &laplacian) const {
	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	std::vector<T> triplets;

	for (auto constraint : constraints) {
		constraint->evaluateLaplacian(triplets);
	}

	laplacian.setFromTriplets(triplets.begin(), triplets.end());
}


void PureConstraint::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	std::vector<T> triplets;

	for (auto constraint : constraints) {
		constraint->evaluateHessian(x, triplets);
	}

	hessian.setFromTriplets(triplets.begin(), triplets.end());
}


double PureConstraint::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	return mLineSearch->lineSearch(x, gradient, descentDir);
}


void PureConstraint::setLineSearch(LineSearchInterface *lineSearch) {
	mLineSearch = lineSearch;
}








MinimizationExpressionInterface *NoDamping::instance__ = 0;


MinimizationExpressionInterface *NoDamping::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new NoDamping(solver);
	}
	return instance__;
}


NoDamping::NoDamping(const Solver *solver): mSolver(solver) {
}


double NoDamping::evaluateEnergy(const VectorX &x) const {
	return 0.0;
}


void NoDamping::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	unsigned systemDimension = mSolver->getSystemDimension();
	gradient.resize(systemDimension);
	gradient.setZero();
}


void NoDamping::evaluateLaplacian(SpMat &laplacian) const {
	unsigned systemDimension = mSolver->getSystemDimension();
	laplacian.resize(systemDimension, systemDimension);
	laplacian.setZero();
}


void NoDamping::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	unsigned systemDimension = mSolver->getSystemDimension();
	hessian.resize(systemDimension, systemDimension);
	hessian.setZero();
}


double NoDamping::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	return mLineSearch->lineSearch(x, gradient, descentDir);
}


void NoDamping::setLineSearch(LineSearchInterface *lineSearch) {
	mLineSearch = lineSearch;
}






MinimizationExpressionInterface *RayleighDamping::instance__ = 0;


MinimizationExpressionInterface *RayleighDamping::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new RayleighDamping(solver);
	}
	return instance__;
}


RayleighDamping::RayleighDamping(const Solver *solver) : mSolver(solver), mDampingCoeff(0.1) {
	unsigned systemDimension = mSolver->getSystemDimension();
	mDampingMatrix.resize(systemDimension, systemDimension);

	PureConstraint::Instance(mSolver)->evaluateLaplacian(mDampingMatrix);

	//VectorX currentPositions = mSolver->getCurrentPositions();
	//PureConstraint::Instance(mSolver)->evaluateHessian(currentPositions, mDampingMatrix);

	mDampingMatrix *= mDampingCoeff;

	std::cout << "mDampingMatrix" << std::endl << mDampingMatrix << std::endl;
}


double RayleighDamping::evaluateEnergy(const VectorX &x) const {
	double h = mSolver->getH();
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();

	VectorX v = 2.0 / h * (x - currentPositions) - currentVelocities;

	double energy = 0.5 * h * v.transpose() * mDampingMatrix * v;

	return energy;
}


void RayleighDamping::evaluateGradient(const VectorX &x, VectorX &gradient) const {

	const ImplicitIntegratorInterface *integrator = dynamic_cast<const ImplicitIntegratorInterface *>(mSolver->getIntegrator());

	integrator->evaluateAppendedExpressionGradient(mDampingMatrix, x, gradient);
}


void RayleighDamping::evaluateHessian(const VectorX &x, SpMat &hessian) const {

	const ImplicitIntegratorInterface *integrator = dynamic_cast<const ImplicitIntegratorInterface *>(mSolver->getIntegrator());

	integrator->evaluateAppendedExpressionHessian(mDampingMatrix, hessian);

};


void RayleighDamping::evaluateLaplacian(SpMat &laplacian) const {

	const ImplicitIntegratorInterface *integrator = dynamic_cast<const ImplicitIntegratorInterface *>(mSolver->getIntegrator());

	integrator->evaluateAppendedExpressionLaplacian(mDampingMatrix, laplacian);
}


double RayleighDamping::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	return mLineSearch->lineSearch(x, gradient, descentDir);
}

void RayleighDamping::setLineSearch(LineSearchInterface *lineSearch) {
	mLineSearch = lineSearch;
}
