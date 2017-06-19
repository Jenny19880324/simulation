#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif

#include<Eigen/SparseCholesky>
#include "typedef.h"

//forward declaration
class ImplicitIntegratorInterface;
class MinimizationExpressionInterface;
class ConstraintInterface;
class Solver;


class CLASS_DECLSPEC MinimizationMethodInterface{
public:
	virtual ~MinimizationMethodInterface(){}
	virtual bool solveMinimization(ImplicitIntegratorInterface *, VectorX &x) = 0;
	virtual void setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) = 0;

protected:
	MinimizationMethodInterface(){}
};


class CLASS_DECLSPEC NewtonsMethod : public MinimizationMethodInterface{
public:
	NewtonsMethod(const Solver *);
	~NewtonsMethod();
	
	static MinimizationMethodInterface *Instance(const Solver *);
	

	bool solveMinimization(ImplicitIntegratorInterface *, VectorX &x) override;
	void setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) override;
	void evaluateHessian(const std::vector<ConstraintInterface *> &, SpMat &hessian);

private:
	static MinimizationMethodInterface *instance__;

	MinimizationExpressionInterface *mMinimizationExpression;

	const Solver *mSolver;

	Eigen::SimplicialLLT<SpMat, Eigen::Upper> mSparseLinearSystemSolver;

};


class CLASS_DECLSPEC ProjectiveDynamics : public MinimizationMethodInterface{
public:
	ProjectiveDynamics(const Solver *);
	~ProjectiveDynamics();
	
	static MinimizationMethodInterface *Instance(const Solver *);
	
	bool solveMinimization(ImplicitIntegratorInterface *, VectorX &x) override;
	void setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) override;
	void evaluateLaplacian(const std::vector<ConstraintInterface *> &, SpMat &hessian);

private:
	static MinimizationMethodInterface *instance__;

	MinimizationExpressionInterface *mMinimizationExpression;

	const Solver *mSolver;

};