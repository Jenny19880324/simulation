#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif

#include <vector>
#include "typedef.h"


class LineSearchInterface;
class ImplicitIntergratorInterface;
class Solver;


class CLASS_DECLSPEC MinimizationExpressionInterface {
public:
	virtual ~MinimizationExpressionInterface() {}
	virtual double evaluateEnergy(const VectorX &) const = 0;
	virtual void evaluateGradient(const VectorX &, VectorX &) const = 0;
	virtual void evaluateLaplacian(SpMat &) const = 0;
	virtual void evaluateHessian(const VectorX &, SpMat &) const = 0;
	virtual double lineSearch(const VectorX &, const VectorX &, const VectorX &) const = 0;

	virtual void setLineSearch(LineSearchInterface *) = 0;

protected:
	MinimizationExpressionInterface() {}

};


class CLASS_DECLSPEC RayleighDamping : public MinimizationExpressionInterface {
public:
	static MinimizationExpressionInterface *Instance(const Solver *);

	double evaluateEnergy(const VectorX &) const override;
	void evaluateGradient(const VectorX &, VectorX &) const override;
	void evaluateLaplacian(SpMat &) const override;
	void evaluateHessian(const VectorX &, SpMat &) const override;
	double lineSearch(const VectorX &, const VectorX &, const VectorX &) const override;

	void setLineSearch(LineSearchInterface *) override;

protected:
	RayleighDamping(const Solver *);

private:

	static MinimizationExpressionInterface *instance__;
	
	LineSearchInterface *mLineSearch;

	const Solver *mSolver;

	SpMat mDampingMatrix;

	double mDampingCoeff;
};


class CLASS_DECLSPEC NoDamping : public MinimizationExpressionInterface {
public:
	static MinimizationExpressionInterface *Instance(const Solver *);

	double evaluateEnergy(const VectorX &) const override;
	void evaluateGradient(const VectorX &, VectorX &) const override;
	void evaluateLaplacian(SpMat &) const override;
	void evaluateHessian(const VectorX &, SpMat &) const override;
	double lineSearch(const VectorX &, const VectorX &, const VectorX &) const override;

	void setLineSearch(LineSearchInterface *) override;

protected:
	NoDamping(const Solver *solver);

private:
	static MinimizationExpressionInterface *instance__;
	
	LineSearchInterface *mLineSearch;

	const Solver *mSolver;




};