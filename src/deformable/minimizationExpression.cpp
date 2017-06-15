#include <iostream>
#include "minimizationExpression.h"

MinimizationExpressionInterface *RayleighDamping::instance__ = 0;


MinimizationExpressionInterface *RayleighDamping::Instance() {
	if (instance__ == 0) {
		instance__ = new RayleighDamping();
	}
	return instance__;
}


double RayleighDamping::evaluateEnergy() {
	std::cout << "RayleighDamping evaluateEnergy" << std::endl;
	return 0;
}


void RayleighDamping::evaluateGradient() {
	std::cout << "RayleighDamping evaluateGradient" << std::endl;
}


void RayleighDamping::evaluateLaplacian() {
	std::cout << "RayleighDamping evaluateLaplacian" << std::endl;
}


void RayleighDamping::evaluateHessian() {
	std::cout << "RayleighDamping evaluateHessian" << std::endl;
};


double RayleighDamping::lineSearch() {
	evaluateEnergy();
	std::cout << "RayleighDamping lineSearch" << std::endl;
	return 0;
}





MinimizationExpressionInterface *NoDamping::instance__ = 0;


MinimizationExpressionInterface *NoDamping::Instance() {
	if (instance__ == 0) {
		instance__ = new NoDamping();
	}
	return instance__;
}


double NoDamping::evaluateEnergy() {
	std::cout << "NoDamping evaluateEnergy" << std::endl;
	return 0;
}


void NoDamping::evaluateGradient() {
	std::cout << "NoDamping evaluateGradient" << std::endl;
}


void NoDamping::evaluateLaplacian() {
	std::cout << "NoDamping evaluateLaplacian" << std::endl;
}


void NoDamping::evaluateHessian() {
	std::cout << "NoDamping evaluateHessian" << std::endl;
}


double NoDamping::lineSearch() {
	std::cout << "NoDamping lineSearch" << std::endl;
	evaluateEnergy();
	return 0;
}