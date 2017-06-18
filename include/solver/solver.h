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
	Solver(const VectorX &initialPositions, const VectorX &initialVelocities, const SpMat &massMatrix, const std::vector<ConstraintInterface *> &constraints);
	~Solver(){}
	
	void update();
	void setIntegrator(IntegratorInterface *integrator) { mIntegrator = integrator; }
	void setH(double h) { mH = h; }
	void setCurrentPositions(const VectorX &currentPositions) { mCurrentPositions = currentPositions; }
	void setCurrentVelocities(const VectorX &currentVelocities) { mCurrentVelocities = currentVelocities; }
	void setY(const VectorX &y) { mY = y; }
	void setMassMatrix(const SpMat &massMatrix) { mMassMatrix = massMatrix; }
	void setConstraints(const std::vector<ConstraintInterface *> &constraints) { mConstraints = constraints; }


	const IntegratorInterface *getIntegrator() const { return mIntegrator; }
	double getH() const { return mH;}
	const VectorX &getCurrentPositions() const { return mCurrentPositions; }
	const VectorX &getCurrentVelocities() const { return mCurrentVelocities; }
	const VectorX &getY() const { return mY; }
	const SpMat &getMassMatrix() const { return mMassMatrix; }
	const std::vector<ConstraintInterface *> &getConstraints() const { return mConstraints; }
	
private:
	IntegratorInterface *mIntegrator;

	double mH;

	VectorX mCurrentPositions;

	VectorX mCurrentVelocities;

	VectorX mY;

	SpMat mMassMatrix;

	std::vector<ConstraintInterface *> mConstraints;
};
