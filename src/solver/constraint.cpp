#include "constraint.h"

SpringConstraint::SpringConstraint(double stiffness, double restLength, unsigned int p1, unsigned p2):
mStiffness(stiffness), mRestLength(restLength), mP1(p1), mP2(p2){
}


double SpringConstraint::evaluateEnergy(const VectorX &x) const {

	Eigen::Vector3d p1 = x.block<3, 1>(3 * mP1, 0);
	Eigen::Vector3d p2 = x.block<3, 1>(3 * mP2, 0);

	double length = (p1 - p2).norm();

	return 0.5 * mStiffness * (length - mRestLength) * (length - mRestLength);

}


void SpringConstraint::evaluateGradient(const VectorX &x, VectorX &gradient) const {

	Eigen::Vector3d p1 = x.block<3, 1>(3 * mP1, 0);
	Eigen::Vector3d p2 = x.block<3, 1>(3 * mP2, 0);

	double length = (p1 - p2).norm();

	Eigen::Vector3d g1 = mStiffness * (length - mRestLength) * (p1 - p2).normalized();

	gradient.block<3, 1>(3 * mP1, 0) += g1;
	gradient.block<3, 1>(3 * mP2, 0) -= g1;
}


void SpringConstraint::evaluateHessian(const VectorX &x, std::vector<T> &triplets) const {

	Eigen::Vector3d p1 = x.block<3, 1>(3 * mP1, 0);
	Eigen::Vector3d p2 = x.block<3, 1>(3 * mP2, 0);

	double length = (p1 - p2).norm();

	Eigen::Matrix3d k = mStiffness * (Eigen::Matrix3d::Identity() - mRestLength / length * (Eigen::Matrix3d::Identity() - (p1 - p2) * (p1 - p2).transpose() / (length * length)));

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			triplets.push_back(T(3 * mP1 + row, 3 * mP1 + col,  k(row, col)));
			triplets.push_back(T(3 * mP1 + row, 3 * mP2 + col, -k(row, col)));
			triplets.push_back(T(3 * mP2 + row, 3 * mP1 + col, -k(row, col)));
			triplets.push_back(T(3 * mP2 + row, 3 * mP2 + col,  k(row, col)));
		}
	}

}

void SpringConstraint::evaluateLaplacian(const VectorX &x, std::vector<T> &triplets) const {

	triplets.push_back(T(3 * mP1 + 0, 3 * mP1 + 0, mStiffness));
	triplets.push_back(T(3 * mP1 + 1, 3 * mP1 + 1, mStiffness));
	triplets.push_back(T(3 * mP1 + 2, 3 * mP1 + 2, mStiffness));

	triplets.push_back(T(3 * mP1 + 0, 3 * mP2 + 0, -mStiffness));
	triplets.push_back(T(3 * mP1 + 1, 3 * mP2 + 1, -mStiffness));
	triplets.push_back(T(3 * mP1 + 2, 3 * mP2 + 2, -mStiffness));

	triplets.push_back(T(3 * mP2 + 0, 3 * mP1 + 0, -mStiffness));
	triplets.push_back(T(3 * mP2 + 1, 3 * mP1 + 1, -mStiffness));
	triplets.push_back(T(3 * mP2 + 2, 3 * mP1 + 2, -mStiffness));

	triplets.push_back(T(3 * mP2 + 0, 3 * mP2 + 0, mStiffness));
	triplets.push_back(T(3 * mP2 + 1, 3 * mP2 + 1, mStiffness));
	triplets.push_back(T(3 * mP2 + 2, 3 * mP2 + 2, mStiffness));

}

