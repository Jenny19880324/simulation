#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif

//forward declaration
class ImplicitIntegratorInterface;
class MinimizationExpressionInterface;


class CLASS_DECLSPEC MinimizationMethodInterface{
public:
	virtual ~MinimizationMethodInterface(){}
	virtual void solveMinimization(ImplicitIntegratorInterface *) = 0;
	virtual double evaluateEnergy() = 0;
	virtual void evaluateGradient() = 0;
	virtual double lineSearch() = 0;
	virtual void setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) = 0;

protected:
	MinimizationMethodInterface(){}
};


class CLASS_DECLSPEC NewtonsMethod : public MinimizationMethodInterface{
public:
	NewtonsMethod();
	~NewtonsMethod();
	
	static MinimizationMethodInterface *Instance();
	

	void solveMinimization(ImplicitIntegratorInterface *) override;
	double evaluateEnergy() override;
	void evaluateGradient() override;
	double lineSearch() override;
	void setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) override;

	void evaluateHessian();

private:
	static MinimizationMethodInterface *instance__;

	MinimizationExpressionInterface *mMinimizationExpression;

	bool mEnableLineSearch;
};


class CLASS_DECLSPEC ProjectiveDynamics : public MinimizationMethodInterface{
public:
	ProjectiveDynamics();
	~ProjectiveDynamics();
	
	static MinimizationMethodInterface *Instance();
	
	void solveMinimization(ImplicitIntegratorInterface *) override;
	double evaluateEnergy() override;
	void evaluateGradient() override;
	double lineSearch() override;
	void setMinimizationExpression(MinimizationExpressionInterface *minimizationExpression) override;

	void evaluateLaplacian();

private:
	static MinimizationMethodInterface *instance__;

	MinimizationExpressionInterface *mMinimizationExpression;

	bool mEnableLineSearch;
};