class MinimizationMethodInterface;

class IntegratorInterface{
public:
	virtual ~IntegratorInterface(){}

protected:
	IntegratorInterface(){}
};


class ImplicitIntegratorInterface : public IntegratorInterface{
public:
	virtual ~ImplicitIntegratorInterface(){}
	virtual void setMinimizationMethod(MinimizationMethodInterface *) = 0;

protected:
	ImplicitIntegratorInterface(){}
};


class BackwardEuler : public ImplicitIntegratorInterface{
public:
	BackwardEuler(){}
	~BackwardEuler(){}

	void setMinimizationMethod(MinimizationMethodInterface *) override;
	void solveMinimization();

private:
	friend class MinimizationMethodInterface;

private:
	MinimizationMethodInterface *mMinimizationMethod;

};


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