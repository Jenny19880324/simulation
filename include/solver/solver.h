#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif

#include <vector>
#include "typedef.h"

class IntegratorInterface;
class ConstraintInterface;


class CLASS_DECLSPEC Solver{
public:
	Solver(const VectorX &initialPositions, const VectorX &initialVelocities, const SpMat &massMatrix, const std::vector<ConstraintInterface *> &constraints, double h = 0.033);
	~Solver(){}
	
	void setIntegrator(IntegratorInterface *integrator) { mIntegrator = integrator; }
	void setH(double h) { mH = h; }
	void setCurrentPositions(const VectorX &currentPositions) { mCurrentPositions = currentPositions; }
	void setCurrentVelocities(const VectorX &currentVelocities) { mCurrentVelocities = currentVelocities; }
	void setMassMatrix(const SpMat &massMatrix) { mMassMatrix = massMatrix; }
	void setConstraints(const std::vector<ConstraintInterface *> &constraints) { mConstraints = constraints; }


	const IntegratorInterface *getIntegrator() const { return mIntegrator; }
	const VectorX &getCurrentPositions() const { return mCurrentPositions; }
	const VectorX &getCurrentVelocities() const { return mCurrentVelocities; }
	const SpMat &getMassMatrix() const { return mMassMatrix; }
	const std::vector<ConstraintInterface *> &getConstraints() const { return mConstraints; }
	unsigned getSystemDimension() const { return mSystemDimension; }
	double getH() const { return mH; }

	void update();
	void computeAngularMomentum(const VectorX &, const VectorX &, Eigen::Vector3d &);
	double computeHamiltonian(const VectorX &, const VectorX &);
	
private:
	IntegratorInterface *mIntegrator;

	unsigned mSystemDimension;

	unsigned mSteps;

	double mH;

	VectorX mCurrentPositions;

	VectorX mCurrentVelocities;

	SpMat mMassMatrix;

	std::vector<ConstraintInterface *> mConstraints;
};
