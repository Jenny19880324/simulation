#include "solver.h"
#include "integrator.h"


Solver::Solver(const VectorX &initialPositions, const VectorX &initialVelocities, const SpMat &massMatrix, const std::vector<ConstraintInterface *> &constraints, double h):
mCurrentPositions(initialPositions), mCurrentVelocities(initialVelocities), mMassMatrix(massMatrix), mConstraints(constraints){}


void Solver::update() {
	mIntegrator->update(this);
}





