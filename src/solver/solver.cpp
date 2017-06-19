#include "solver.h"
#include "integrator.h"


Solver::Solver(const VectorX &initialPositions, const VectorX &initialVelocities, const SpMat &massMatrix, const std::vector<ConstraintInterface *> &constraints, double h):
mCurrentPositions(initialPositions), mCurrentVelocities(initialVelocities), mMassMatrix(massMatrix), mConstraints(constraints), mSystemDimension(initialPositions.size()), mH(h) {}


void Solver::update() {
	mIntegrator->update();
}





