#include <iostream>
#include "minimizationExpression.h"
#include "lineSearch.h"
#include "constraint.h"
#include "solver.h"
#include "integrator.h"

MinimizationExpressionInterface *RayleighDamping::instance__ = 0;


MinimizationExpressionInterface *RayleighDamping::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new RayleighDamping(solver);
	}
	return instance__;
}


RayleighDamping::RayleighDamping(const Solver *solver) : mSolver(solver), mDampingCoeff(1.0) {
	unsigned systemDimension = mSolver->getSystemDimension();
	mDampingMatrix.resize(systemDimension, systemDimension);

	NoDamping::Instance(mSolver)->evaluateLaplacian(mDampingMatrix);

	mDampingMatrix *= mDampingCoeff;

	std::cout << "mDampingMatrix" << std::endl << mDampingMatrix << std::endl;
}


double RayleighDamping::evaluateEnergy(const VectorX &x) const {
	double energy = NoDamping::Instance(mSolver)->evaluateEnergy(x);

	double h = mSolver->getH();
	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();

	VectorX v = 2.0 / h * (x - currentPositions) - currentVelocities;

	double appendedEnergy = 0.5 * h * h * v.transpose() * mDampingMatrix * v;
	//std::cout << "mDampingMatrix = " << std::endl << mDampingMatrix << std::endl;
	//std::cout << "v = " << v.transpose() << std::endl;
	//std::cout << "appendedEnergy = " << appendedEnergy << std::endl;
	energy += appendedEnergy;

	return energy;
}


void RayleighDamping::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	NoDamping::Instance(mSolver)->evaluateGradient(x, gradient);

	VectorX appendedGradient; 

	const ImplicitIntegratorInterface *integrator = dynamic_cast<const ImplicitIntegratorInterface *>(mSolver->getIntegrator()); 
	
	integrator->evaluateAppendedExpressionGradient(mDampingMatrix, x, appendedGradient);

	gradient += appendedGradient;
}


void RayleighDamping::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	NoDamping::Instance(mSolver)->evaluateHessian(x, hessian);

	SpMat appendedHessian;

	const ImplicitIntegratorInterface *integrator = dynamic_cast<const ImplicitIntegratorInterface *>(mSolver->getIntegrator());

	integrator->evaluateAppendedExpressionHessian(mDampingMatrix, appendedHessian);

	hessian += appendedHessian;

};


void RayleighDamping::evaluateLaplacian(SpMat &laplacian) const {
	NoDamping::Instance(mSolver)->evaluateLaplacian(laplacian);

	SpMat appendedLaplacian;

	const ImplicitIntegratorInterface *integrator = dynamic_cast<const ImplicitIntegratorInterface *>(mSolver->getIntegrator());

	integrator->evaluateAppendedExpressionLaplacian(mDampingMatrix, laplacian);

	laplacian += appendedLaplacian;
}


double RayleighDamping::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	return mLineSearch->lineSearch(x, gradient, descentDir);
}

void RayleighDamping::setLineSearch(LineSearchInterface *lineSearch) {
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
	double energy = 0.0;

	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	for (auto constraint : constraints) {
		energy += constraint->evaluateEnergy(x);
	}

	return energy;
}


void NoDamping::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	for (auto constraint : constraints) {
		constraint->evaluateGradient(x, gradient);
	}

}


void NoDamping::evaluateLaplacian(SpMat &laplacian) const {
	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	std::vector<T> triplets;

	for (auto constraint : constraints) {
		constraint->evaluateLaplacian(triplets);
	}

	laplacian.setFromTriplets(triplets.begin(), triplets.end());
}


void NoDamping::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	std::vector<T> triplets;

	for (auto constraint : constraints) {
		constraint->evaluateHessian(x, triplets);
	}

	hessian.setFromTriplets(triplets.begin(), triplets.end());
}


double NoDamping::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	return mLineSearch->lineSearch(x, gradient, descentDir);
}


void NoDamping::setLineSearch(LineSearchInterface *lineSearch) {
	mLineSearch = lineSearch;
}