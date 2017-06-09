#include "integrator.h"
#include "minimizationMethod.h"
#include "simulation.h"
#include "minimizationExpression.h"

int main(int argc, const char **argv) {
	Simulation sim;
	sim.setIntegrator(BackwardEuler::Instance());

	BackwardEuler::Instance()->setMinimizationMethod(ProjectiveDynamics::Instance());

	ProjectiveDynamics::Instance()->setMinimizationExpression(RayleighDamping::Instance());
	

	
	sim.update();

}