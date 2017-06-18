#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif

#include "typedef.h"

//forward declaration
class MinimizationMethodInterface;
class MinimizationExpressionInterface;
class Solver;

class CLASS_DECLSPEC IntegratorInterface{
public:
	virtual ~IntegratorInterface(){}
	virtual void update(Solver *) = 0;

protected:
	IntegratorInterface(){}
};


class ExplicitIntegratorInterface : public IntegratorInterface {
public:
	virtual ~ExplicitIntegratorInterface(){}

protected:
	ExplicitIntegratorInterface() {}
};


class CLASS_DECLSPEC ForwardEuler : public ExplicitIntegratorInterface {
public:
	static ExplicitIntegratorInterface *Instance();
	void update(Solver *) override;

private:
	static ExplicitIntegratorInterface *instance__;
};








class ImplicitIntegratorInterface : public IntegratorInterface{
public:
	virtual ~ImplicitIntegratorInterface(){}
	virtual void setMinimizationMethod(MinimizationMethodInterface *) = 0;
	virtual void solveMinimization() = 0;
	virtual double evaluateEnergy(const VectorX &) const = 0;
	virtual void evaluateGradient(const VectorX &, VectorX &gradient) const = 0;
	virtual void evaluateHessian(const VectorX &, SpMat &) const = 0;
	virtual void evaluateLaplacian(SpMat &) const = 0;
	virtual void evaluateAppendedExpressionGradient(const SpMat &mDampingMatrix, const VectorX &x, VectorX &gradient) const = 0;
	virtual void evaluateAppendedExpressionHessian(const SpMat &mDampingMatrix, SpMat &hessian) const = 0;
	virtual void evaluateAppendedExpressionLaplacian(const SpMat &mDampingMatrix, SpMat &laplacian) const = 0;

protected:
	ImplicitIntegratorInterface(){}
};



class CLASS_DECLSPEC QuasiStatic : public ImplicitIntegratorInterface {
public:
	static ImplicitIntegratorInterface *Instance();

	void setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) override {mMinimizationMethod = minimizationMethod;}
	void solveMinimization() override;
	void update(Solver *) override;
	virtual double evaluateEnergy(const VectorX &) const override;
	void evaluateGradient(const VectorX &, VectorX &) const override;
	void evaluateHessian(const VectorX &, SpMat &) const override;
	void evaluateLaplacian(SpMat &) const override;
	void evaluateAppendedExpressionGradient(const SpMat &mDampingMatrix, const VectorX &x, VectorX &gradient) const override;
	void evaluateAppendedExpressionHessian(const SpMat &mDampingMatrix, SpMat &hessian) const override;
	void evaluateAppendedExpressionLaplacian(const SpMat &mDampingMatrix, SpMat &laplacian) const override;


private:
	friend class MinimizationMethodInterface;

private:
	static ImplicitIntegratorInterface *instance__;
	MinimizationMethodInterface *mMinimizationMethod;
	MinimizationExpressionInterface *mMinimizationExpression;
	Solver *mSolver;
};


class CLASS_DECLSPEC BackwardEuler : public ImplicitIntegratorInterface{
public:
	static ImplicitIntegratorInterface *Instance(const Solver *);
	
	BackwardEuler(const Solver *);
	~BackwardEuler();

	void setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) override {mMinimizationMethod = minimizationMethod;}
	void solveMinimization() override;
	void update(Solver *) override;
	double evaluateEnergy(const VectorX &) const override;
	void evaluateGradient(const VectorX &, VectorX &) const override;
	void evaluateHessian(const VectorX &, SpMat &) const override;
	void evaluateLaplacian(SpMat &) const override;
	void evaluateAppendedExpressionGradient(const SpMat &mDampingMatrix, const VectorX &x, VectorX &gradient) const override;
	void evaluateAppendedExpressionHessian(const SpMat &mDampingMatrix, SpMat &hessian) const override;
	void evaluateAppendedExpressionLaplacian(const SpMat &mDampingMatrix, SpMat &laplacian) const override;

private:
	static ImplicitIntegratorInterface *instance__;
	MinimizationMethodInterface *mMinimizationMethod;
	MinimizationExpressionInterface *mMinimizationExpression;
	const Solver *mSolver;
};


class CLASS_DECLSPEC ImplicitMidpoint : public ImplicitIntegratorInterface {
public:
	static ImplicitIntegratorInterface *Instance(const Solver *);

	ImplicitMidpoint(const Solver *);
	~ImplicitMidpoint();

	void setMinimizationMethod(MinimizationMethodInterface *minimizationMethod) override { mMinimizationMethod = minimizationMethod; }
	void solveMinimization() override;
	void update(Solver *) override;
	double evaluateEnergy(const VectorX &) const override;
	void evaluateGradient(const VectorX &, VectorX &) const override;
	void evaluateHessian(const VectorX &, SpMat &) const override;
	void evaluateLaplacian(SpMat &) const override;
	void evaluateAppendedExpressionGradient(const SpMat &mDampingMatrix, const VectorX &x, VectorX &gradient) const override;
	void evaluateAppendedExpressionHessian(const SpMat &mDampingMatrix, SpMat &hessian) const override;
	void evaluateAppendedExpressionLaplacian(const SpMat &mDampingMatrix, SpMat &laplacian) const override;

private:
	static ImplicitIntegratorInterface *instance__;
	MinimizationMethodInterface *mMinimizationMethod;
	MinimizationExpressionInterface *mMinimizationExpression;
	const Solver *mSolver;
};