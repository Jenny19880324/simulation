//forward declaration
class ImplicitIntegratorInterface;


class MinimizationMethodInterface{
public:
	virtual ~MinimizationMethodInterface(){}
	virtual void solveMinimization(ImplicitIntegratorInterface *) = 0;

protected:
	MinimizationMethodInterface(){}
};


class NewtonsMethod : public MinimizationMethodInterface{
public:
	NewtonsMethod(){}
	~NewtonsMethod(){}
	
	static MinimizationMethodInterface *Instance();
	
	void solveMinimization(ImplicitIntegratorInterface *) override;

private:
	static MinimizationMethodInterface *mInstance;
};


class ProjectiveDynamics : public MinimizationMethodInterface{
public:
	ProjectiveDynamics(){}
	~ProjectiveDynamics(){}
	
	static MinimizationMethodInterface *Instance();
	
	void solveMinimization(ImplicitIntegratorInterface *) override;

private:
	static MinimizationMethodInterface *mInstance;
};