#include <iostream>
#include "minimizationMethod.h"
#include "minimizationExpression.h"
#include "constraint.h"
#include "integrator.h"
#include "solver.h"
#include "constant.h"

MinimizationMethodInterface *NewtonsMethod::instance__ = 0;


NewtonsMethod::NewtonsMethod() {
}


NewtonsMethod::~NewtonsMethod() {

}


MinimizationMethodInterface *NewtonsMethod::Instance() {
	if (instance__ == 0) {
		instance__ = new NewtonsMethod();
	}
	return instance__;
}

void NewtonsMethod::solveMinimization(ImplicitIntegratorInterface *integrator){
	std::cout << "Newton's method : solve minimization" << std::endl;
	
	VectorX gradient;
	SpMat hessian;
	VectorX descentDir;

	VectorX x = mSolver->getCurrentPositions() + mSolver->getCurrentVelocities() * mSolver->getH();

	while (-descentDir.dot(gradient) > EXIT_CONDITION) {
		integrator->evaluateGradient(x, gradient);
		integrator->evaluateHessian(x, hessian);

		mSparseLinearSystemSolver.analyzePattern(hessian);
		mSparseLinearSystemSolver.factorize(hessian);
		descentDir = - mSparseLinearSystemSolver.solve(gradient);
		mMinimizationExpression->lineSearch(x, gradient, descentDir);

	}
	


	/*
	while (exit condition is not satisfied) {
		solve the linear matrix
		lineSearch
	}
	*/
}

void NewtonsMethod::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression;
}




MinimizationMethodInterface *ProjectiveDynamics::instance__ = 0;

MinimizationMethodInterface *ProjectiveDynamics::Instance() {
	if (instance__ == 0) {
		instance__ = new ProjectiveDynamics();
	}
	return instance__;
}


void ProjectiveDynamics::solveMinimization(ImplicitIntegratorInterface *integrator){
	std::cout << "ProjectiveDynamics : solve minimization" << std::endl;

}


ProjectiveDynamics::ProjectiveDynamics() {
}

ProjectiveDynamics::~ProjectiveDynamics() {

}


void ProjectiveDynamics::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression;
}
