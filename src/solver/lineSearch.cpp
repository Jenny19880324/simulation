#include <iostream>
#include "lineSearch.h"
#include "integrator.h"
#include "solver.h"

LineSearchInterface *BacktrackingLineSearch::instance__ = 0;

LineSearchInterface *BacktrackingLineSearch::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new BacktrackingLineSearch(solver);
	}
	return instance__;
}

BacktrackingLineSearch::BacktrackingLineSearch(const Solver *solver) : mSolver(solver) {
}


double BacktrackingLineSearch::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	std::cout << "Backtracking LineSearch" << std::endl;

	double alpha = 1.0;

	//Armijo Condition
	const ImplicitIntegratorInterface *integrator = dynamic_cast<const ImplicitIntegratorInterface *>(mSolver->getIntegrator());

	double energy = integrator->evaluateEnergy(x);

	double descent = gradient.dot(descentDir);

	while (integrator->evaluateEnergy(x + alpha * descentDir) < energy + alpha * mRho * descent) {
		alpha *= mC;
	}

	return alpha;
}




LineSearchInterface *NoLineSearch::instance__ = 0;


LineSearchInterface *NoLineSearch::Instance(const Solver *solver) {
	if (instance__ == 0) {
		instance__ = new NoLineSearch(solver);
	}
	return instance__;
}


NoLineSearch::NoLineSearch(const Solver *solver) : mSolver(solver) {
}


double NoLineSearch::lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const {
	std::cout << "NoLineSearch" << std::endl;
	return 1.0;
}