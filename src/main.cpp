#include "integrator.h"
#include "minimizationMethod.h"
#include "simulation.h"
#include "rayleighDamping.h"

int main(int argc, const char **argv) {
	Simulation sim;
	sim.setIntegrator(BackwardEuler::Instance());

	BackwardEuler::Instance()->setMinimizationMethod(NewtonsMethod::Instance());

	NewtonsMethod::Instance()->setMinimizationExpression(RayleighDamping::Instance());
	

	
	sim.update();

}