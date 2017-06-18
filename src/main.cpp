#include "integrator.h"
#include "minimizationMethod.h"
#include "solver.h"
#include "minimizationExpression.h"
#include "lineSearch.h"

int main(int argc, const char **argv) {
	Solver sim;
	sim.setIntegrator(BackwardEuler::Instance(&sim));

	BackwardEuler::Instance(&sim)->setMinimizationMethod(ProjectiveDynamics::Instance());

	ProjectiveDynamics::Instance()->setMinimizationExpression(RayleighDamping::Instance(&sim));

	RayleighDamping::Instance(&sim)->setLineSearch(NoLineSearch::Instance(BackwardEuler::Instance(&sim)));
	

	
	sim.update();

}