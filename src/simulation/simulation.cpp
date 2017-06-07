#include "simulation.h"
#include "integrator.h"

void Simulation::update() {
	mIntegrator->update(this);
}

void Simulation::setIntegrator(IntegratorInterface *integrator){
	mIntegrator = integrator;
}




