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
	Solver(){}
	~Solver(){}
	
	void update();
	void setIntegrator(IntegratorInterface *);

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
