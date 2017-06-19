#include <iostream>
#include <Eigen/dense>
#include "solver.h"
#include "integrator.h"


Solver::Solver(const VectorX &initialPositions, const VectorX &initialVelocities, const SpMat &massMatrix, const std::vector<ConstraintInterface *> &constraints, double h):
mCurrentPositions(initialPositions), mCurrentVelocities(initialVelocities), mMassMatrix(massMatrix), mConstraints(constraints), mSystemDimension(initialPositions.size()), mH(h) {}


void Solver::update() {

	bool converged = true;

	//TODO remove this assignment
	mSteps = 100;

	for (unsigned i = 0; i < mSteps && converged; i++) {
		converged = mIntegrator->update();

		Eigen::Vector3d angularMomentum = Eigen::Vector3d::Zero();
		computeAngularMomentum(mCurrentPositions, mCurrentVelocities, angularMomentum);
		std::cout << "mCurrentPositions = " << mCurrentPositions.transpose() << std::endl;
		std::cout << "mCurrentVelocities = " << mCurrentVelocities.transpose() << std::endl;
		std::cout << "angularMomentum = " << angularMomentum.transpose() << std::endl;
	}
	


}


void Solver::computeAngularMomentum(const VectorX &x, const VectorX &v, Eigen::Vector3d &angularMomentum) {
	unsigned numVertices = mSystemDimension / 3;

	for (unsigned i = 0; i < numVertices; i++) {
		double mass = mMassMatrix.coeff(3 * i, 3 * i);

		Eigen::Vector3d r = x.block<3, 1>(3 * i, 0);
		Eigen::Vector3d p = mass * v.block<3, 1>(3 * i, 0);

		angularMomentum += r.cross(p);
	}
}





