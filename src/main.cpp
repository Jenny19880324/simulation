#include "integrator.h"
#include "minimizationMethod.h"
#include "solver.h"
#include "minimizationExpression.h"
#include "lineSearch.h"
#include "constraint.h"
#include <iostream>

int main(int argc, const char **argv) {
	VectorX initialPositions(6, 1);
	VectorX initialVelocities(6, 1);
	SpMat massMatrix(6, 6);
	std::vector<ConstraintInterface *> constraints;

	constraints.push_back(new SpringConstraint(1.0, 1.0, 1, 2));

	initialPositions.setZero();
	initialVelocities.setZero();
	initialPositions.coeffRef(3, 1) = 1.0;
	massMatrix.coeffRef(0, 0) = 1.0;
	massMatrix.coeffRef(1, 1) = 1.0;
	massMatrix.coeffRef(2, 2) = 1.0;
	massMatrix.coeffRef(3, 3) = 1.0;
	massMatrix.coeffRef(4, 4) = 1.0;
	massMatrix.coeffRef(5, 5) = 1.0;

	std::cout << "initialPositions" << std::endl << initialPositions << std::endl;
	std::cout << "initialVelocities" << std::endl << initialVelocities << std::endl;
	std::cout << "massMatrix" << std::endl << massMatrix << std::endl;




	Solver sim(initialPositions, initialVelocities, massMatrix, constraints);

	sim.setIntegrator(BackwardEuler::Instance(&sim));

	BackwardEuler::Instance(&sim)->setMinimizationMethod(ProjectiveDynamics::Instance());

	ProjectiveDynamics::Instance()->setMinimizationExpression(RayleighDamping::Instance(&sim));

	RayleighDamping::Instance(&sim)->setLineSearch(NoLineSearch::Instance(BackwardEuler::Instance(&sim)));
	

	
	sim.update();

}