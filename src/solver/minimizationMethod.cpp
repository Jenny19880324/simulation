#include <iostream>
#include "minimizationMethod.h"
#include "minimizationExpression.h"
#include "constraint.h"
#include "integrator.h"
#include "solver.h"
#include "constant.h"

MinimizationMethodInterface *NewtonsMethod::instance__ = 0;


NewtonsMethod::NewtonsMethod(const Solver *solver) : mSolver(solver) {
}


NewtonsMethod::~NewtonsMethod() {

}


MinimizationMethodInterface *NewtonsMethod::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new NewtonsMethod(solver);
	}
	return instance__;
}


void NewtonsMethod::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression;
}


bool NewtonsMethod::solveMinimization(ImplicitIntegratorInterface *integrator, VectorX &x){
	unsigned systemDimension = mSolver->getSystemDimension();

	VectorX gradient(systemDimension); 
	VectorX descentDir(systemDimension);
	SpMat hessian(systemDimension, systemDimension);

	gradient.setZero();
	descentDir.setZero();
	hessian.setZero();
	

	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	double h = mSolver->getH();

	x = currentPositions + currentVelocities * h;

	 do {
		integrator->evaluateGradient(x, gradient);
		integrator->evaluateHessian(x, hessian);

		mSparseLinearSystemSolver.analyzePattern(hessian);
		mSparseLinearSystemSolver.factorize(hessian);
		descentDir = - mSparseLinearSystemSolver.solve(gradient);

		double stepSize = mMinimizationExpression->lineSearch(x, gradient, descentDir);

		if (stepSize < STEP_SIZE) {
			std::cout << "Line search is making no progress: step size is " << stepSize << std::endl;
			std::cout << "gradient = " << gradient.transpose() << std::endl;
			return false;
		}

		x += stepSize * descentDir;
	 } while (-descentDir.dot(gradient) > EXIT_CONDITION);

	 return true;
}





MinimizationMethodInterface *ProjectiveDynamics::instance__ = 0;

MinimizationMethodInterface *ProjectiveDynamics::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new ProjectiveDynamics(solver);
	}
	return instance__;
}


void ProjectiveDynamics::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression;
}




ProjectiveDynamics::ProjectiveDynamics(const Solver *solver) : mSolver(solver) {
}

ProjectiveDynamics::~ProjectiveDynamics() {

}



bool ProjectiveDynamics::solveMinimization(ImplicitIntegratorInterface *integrator, VectorX &x) {
	unsigned systemDimension = mSolver->getSystemDimension();

	VectorX gradient(systemDimension);
	VectorX descentDir(systemDimension);
	SpMat laplacian(systemDimension, systemDimension);

	gradient.setZero();
	descentDir.setZero();
	integrator->evaluateLaplacian(laplacian);

	mSparseLinearSystemSolver.analyzePattern(laplacian);
	mSparseLinearSystemSolver.factorize(laplacian);

	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	double h = mSolver->getH();

	x = currentPositions + currentVelocities * h;

	do {
		integrator->evaluateGradient(x, gradient);

		descentDir = -mSparseLinearSystemSolver.solve(gradient);

		double stepSize = mMinimizationExpression->lineSearch(x, gradient, descentDir);

		if (stepSize < STEP_SIZE) {
			std::cout << "Line search is making no progress: step size is " << stepSize << std::endl;
			std::cout << "gradient = " << gradient.transpose() << std::endl;
			return false;
		}

		x += stepSize * descentDir;
	} while (-descentDir.dot(gradient) > EXIT_CONDITION);

	return true;
}


