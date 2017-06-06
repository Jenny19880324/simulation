#include "simulation.h"

int main(int argc, const char **argv) {
	BackwardEuler integrator;
	integrator.setMinimizationMethod(ProjectiveDynamics::Instance());
	
	integrator.solveMinimization();
}