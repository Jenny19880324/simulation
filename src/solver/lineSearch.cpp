#include <iostream>
#include "lineSearch.h"
#include "integrator.h"
#include "solver.h"
#include "constant.h"

LineSearchInterface *BacktrackingLineSearch::instance__ = 0;

LineSearchInterface *BacktrackingLineSearch::Instance(const ImplicitIntegratorInterface *integrator) {
	if (instance__ == 0) {
		instance__ = new BacktrackingLineSearch(integrator);
	}
	return instance__;
}

BacktrackingLineSearch::BacktrackingLineSearch(const ImplicitIntegratorInterface *integrator) : mIntegrator(integrator), mRho(0.01), mC(0.8) {
}


double BacktrackingLineSearch::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	double alpha = 1.0;

	//Armijo Condition
	double energy = mIntegrator->evaluateEnergy(x);

	double descent = gradient.dot(descentDir);

	while (mIntegrator->evaluateEnergy(x + alpha * descentDir) >= energy + alpha * mRho * descent && alpha >= STEP_SIZE) {
		alpha *= mC;
	}

	return alpha;
}




LineSearchInterface *NoLineSearch::instance__ = 0;


LineSearchInterface *NoLineSearch::Instance(const ImplicitIntegratorInterface *integrator) {
	if (instance__ == 0) {
		instance__ = new NoLineSearch(integrator);
	}
	return instance__;
}


NoLineSearch::NoLineSearch(const ImplicitIntegratorInterface *integrator) : mIntegrator(integrator) {
}


double NoLineSearch::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	return 1.0;
}