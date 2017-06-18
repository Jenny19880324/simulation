#ifdef _EXPORTING
	#define CLASS_DECLSPEC __declspec(dllexport)
#else
	#define CLASS_DECLSPEC __declspec(dllimport)
#endif

#include <vector>
#include "typedef.h"

class CLASS_DECLSPEC ConstraintInterface{
public:
	virtual ~ConstraintInterface(){}
	virtual double evaluateEnergy(const VectorX &) const = 0;
	virtual void evaluateGradient(const VectorX &, VectorX &) const = 0;
	virtual void evaluateHessian(const VectorX &, std::vector<T> &) const = 0;
	virtual void evaluateLaplacian(std::vector<T> &) const = 0;

protected:
	ConstraintInterface(){}
};


class CLASS_DECLSPEC SpringConstraint : public ConstraintInterface{
public:
	SpringConstraint(double stiffness, double restLength, unsigned int p1, unsigned p2);
	~SpringConstraint(){}
	
	double evaluateEnergy(const VectorX &) const override;
	void evaluateGradient(const VectorX &, VectorX &) const override;
	void evaluateHessian(const VectorX &, std::vector<T> &) const override;
	void evaluateLaplacian(std::vector<T> &) const override;
	
private:
	double mStiffness;
	double mRestLength;
	unsigned int mP1, mP2;
};