#include <iostream>
#include "minimizationMethod.h"

MinimizationMethodInterface *NewtonsMethod::instance__ = 0;

MinimizationMethodInterface *NewtonsMethod::Instance() {
	if (instance__ == 0) {
		instance__ = new NewtonsMethod();
	}
	return instance__;
}

void NewtonsMethod::solveMinimization(ImplicitIntegratorInterface *integrator){
	std::cout << "Newton's method : solve minimization" << std::endl;
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
