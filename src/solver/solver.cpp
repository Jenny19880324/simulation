#include "solver.h"
#include "integrator.h"

void Solver::update() {
	mIntegrator->update(this);
}

void Solver::setIntegrator(IntegratorInterface *integrator){
	mIntegrator = integrator;
}




