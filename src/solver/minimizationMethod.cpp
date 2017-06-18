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

void NewtonsMethod::solveMinimization(ImplicitIntegratorInterface *integrator){
	std::cout << "Newton's method : solve minimization" << std::endl;
	
	VectorX gradient;
	SpMat hessian;
	VectorX descentDir;

	const VectorX &currentPositions = mSolver->getCurrentPositions();
	const VectorX &currentVelocities = mSolver->getCurrentVelocities();
	double h = mSolver->getH();

	VectorX x = currentPositions + currentVelocities * h;

	while (-descentDir.dot(gradient) > EXIT_CONDITION) {
		integrator->evaluateGradient(x, gradient);
		integrator->evaluateHessian(x, hessian);

		mSparseLinearSystemSolver.analyzePattern(hessian);
		mSparseLinearSystemSolver.factorize(hessian);
		descentDir = - mSparseLinearSystemSolver.solve(gradient);
		mMinimizationExpression->lineSearch(x, gradient, descentDir);

	}
	
}

void NewtonsMethod::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression;
}




MinimizationMethodInterface *ProjectiveDynamics::instance__ = 0;

MinimizationMethodInterface *ProjectiveDynamics::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new ProjectiveDynamics(solver);
	}
	return instance__;
}


void ProjectiveDynamics::solveMinimization(ImplicitIntegratorInterface *integrator){
	std::cout << "ProjectiveDynamics : solve minimization" << std::endl;

}


ProjectiveDynamics::ProjectiveDynamics(const Solver *solver) : mSolver(solver) {
}

ProjectiveDynamics::~ProjectiveDynamics() {

}


void ProjectiveDynamics::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression;
}
