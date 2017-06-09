#include <iostream>
#include "minimizationMethod.h"
#include "minimizationExpression.h"

MinimizationMethodInterface *NewtonsMethod::instance__ = 0;


NewtonsMethod::NewtonsMethod() {
	mMinimizationExpression = NoDamping::Instance();
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
	
	evaluateGradient();
	evaluateHessian();
	lineSearch();

	/*
	while (exit condition is not satisfied) {
		solve the linear matrix
		lineSearch
	}
	*/
}


double NewtonsMethod::evaluateEnergy() {
	return mMinimizationExpression->evaluateEnergy();
}


void NewtonsMethod::evaluateGradient() {
	mMinimizationExpression->evaluateGradient();
}


double NewtonsMethod::lineSearch() {
	return mMinimizationExpression->lineSearch();
}


void NewtonsMethod::evaluateHessian() {
	mMinimizationExpression->evaluateHessian();
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
	
	evaluateGradient();
	evaluateLaplacian();
	lineSearch();
}


ProjectiveDynamics::ProjectiveDynamics() {
	mMinimizationExpression = NoDamping::Instance();
}

ProjectiveDynamics::~ProjectiveDynamics() {

}


double ProjectiveDynamics::evaluateEnergy() {
	return mMinimizationExpression->evaluateEnergy();
	
}


void ProjectiveDynamics::evaluateGradient() {
	mMinimizationExpression->evaluateGradient();
}


double ProjectiveDynamics::lineSearch() {
	mMinimizationExpression->lineSearch();
	return 0;
}


void ProjectiveDynamics::evaluateLaplacian() {
	mMinimizationExpression->evaluateLaplacian();
}

void ProjectiveDynamics::setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) {
	mMinimizationExpression = minimizationExpression;
}
