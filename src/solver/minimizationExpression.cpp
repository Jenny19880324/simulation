#include <iostream>
#include "minimizationExpression.h"
#include "lineSearch.h"
#include "constraint.h"
#include "solver.h"

MinimizationExpressionInterface *RayleighDamping::instance__ = 0;


MinimizationExpressionInterface *RayleighDamping::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new RayleighDamping(solver);
	}
	return instance__;
}


RayleighDamping::RayleighDamping(const Solver *solver) : mSolver(solver) {


}


double RayleighDamping::evaluateEnergy(const VectorX &x) const {
	std::cout << "RayleighDamping evaluateEnergy" << std::endl;
	//double energy = NoDamping::Instance()->evaluateEnergy(x);

	//VectorX vnp1 = 2 * (x - m_mesh->m_current_positions) - m_mesh->m_current_velocities * m_h;
	//VectorX vnp1 = 2.0 / mH * (x - mCurrentPositions) - mCurrentVelocities;
	//energy += 0.5 * mHSquare * vnp1.transpose() * mDampingMatrix * vnp1;

	return 0.0;
}


void RayleighDamping::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	std::cout << "RayleighDamping evaluateGradient" << std::endl;
}


void RayleighDamping::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	std::cout << "RayleighDamping evaluateHessian" << std::endl;
};


void RayleighDamping::evaluateLaplacian(const VectorX &x, SpMat &laplacian) const {
	std::cout << "RayleighDamping evaluateLaplacian" << std::endl;
}


double RayleighDamping::lineSearch(const VectorX &x, const VectorX &, const VectorX &) const {
	std::cout << "RayleighDamping lineSearch" << std::endl;
	return 0;
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
	std::cout << "NoDamping evaluateEnergy" << std::endl;

	double energy = 0.0;

	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	for (auto constraint : constraints) {
		energy += constraint->evaluateEnergy(x);
	}

	return energy;
}


void NoDamping::evaluateGradient(const VectorX &x, VectorX &gradient) const {
	std::cout << "NoDamping evaluateGradient" << std::endl;

	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	for (auto constraint : constraints) {
		constraint->evaluateGradient(x, gradient);
	}

}


void NoDamping::evaluateLaplacian(const VectorX &x, SpMat &laplacian) const {
	std::cout << "NoDamping evaluateLaplacian" << std::endl;

	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	std::vector<T> triplets;

	for (auto constraint : constraints) {
		constraint->evaluateLaplacian(x, triplets);
	}

	laplacian.setFromTriplets(triplets.begin(), triplets.end());
}


void NoDamping::evaluateHessian(const VectorX &x, SpMat &hessian) const {
	std::cout << "NoDamping evaluateHessian" << std::endl;

	const std::vector<ConstraintInterface *> &constraints = mSolver->getConstraints();

	std::vector<T> triplets;

	for (auto constraint : constraints) {
		constraint->evaluateHessian(x, triplets);
	}

	hessian.setFromTriplets(triplets.begin(), triplets.end());
}


double NoDamping::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	std::cout << "NoDamping lineSearch" << std::endl;
	return mLineSearch->lineSearch(x, gradient, descentDir);
}


void NoDamping::setLineSearch(LineSearchInterface *lineSearch) {
	mLineSearch = lineSearch;
}