#include "integrator.h"
#include "minimizationMethod.h"
#include "simulation.h"

int main(int argc, const char **argv) {
	Simulation sim;
	sim.setIntegrator(BackwardEuler::Instance());

	BackwardEuler::Instance()->setMinimizationMethod(NewtonsMethod::Instance());
	

	
	sim.update();

}