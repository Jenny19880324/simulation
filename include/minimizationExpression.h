#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif

class CLASS_DECLSPEC MinimizationExpressionInterface {
public:
	virtual ~MinimizationExpressionInterface() {}
	virtual double evaluateEnergy() = 0;
	virtual void evaluateGradient() = 0;
	virtual void evaluateLaplacian() = 0;
	virtual void evaluateHessian() = 0;
	virtual double lineSearch() = 0;

protected:
	MinimizationExpressionInterface() {}

};


class CLASS_DECLSPEC RayleighDamping : public MinimizationExpressionInterface {
public:
	static MinimizationExpressionInterface *Instance();

	virtual double evaluateEnergy() override;
	virtual void evaluateGradient() override;
	virtual void evaluateLaplacian() override;
	virtual void evaluateHessian() override;
	virtual double lineSearch() override;

protected:
	RayleighDamping() {}

private:
	
	static MinimizationExpressionInterface *instance__;
};


class CLASS_DECLSPEC NoDamping : public MinimizationExpressionInterface {
public:
	static MinimizationExpressionInterface *Instance();

	virtual double evaluateEnergy() override;
	virtual void evaluateGradient() override;
	virtual void evaluateLaplacian() override;
	virtual void evaluateHessian() override;
	virtual double lineSearch() override;

protected:
	NoDamping(){}

private:
	static MinimizationExpressionInterface *instance__;


};