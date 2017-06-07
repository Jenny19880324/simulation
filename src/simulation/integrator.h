//forward declaration
class MinimizationMethodInterface;
class Simulation;

class IntegratorInterface{
public:
	virtual ~IntegratorInterface(){}
	virtual void update(Simulation *) = 0;

protected:
	IntegratorInterface(){}
};


class ImplicitIntegratorInterface : public IntegratorInterface{
public:
	virtual ~ImplicitIntegratorInterface(){}
	virtual void setMinimizationMethod(MinimizationMethodInterface *) = 0;
	virtual void solveMinimization() = 0;

protected:
	ImplicitIntegratorInterface(){}
};

class QuasiStatic : public ImplicitIntegratorInterface {
public:
	static ImplicitIntegratorInterface *Instance();

	void setMinimizationMethod(MinimizationMethodInterface *) override;
	void solveMinimization() override;
	void update(Simulation *) override;

private:
	friend class MinimizationMethodInterface;

private:
	static ImplicitIntegratorInterface *instance__;
	MinimizationMethodInterface *mMinimizationMethod;
};

class BackwardEuler : public ImplicitIntegratorInterface{
public:
	static ImplicitIntegratorInterface *Instance();
	
	BackwardEuler(){}
	~BackwardEuler(){}

	void setMinimizationMethod(MinimizationMethodInterface *) override;
	void solveMinimization() override;
	void update(Simulation *) override;

private:
	friend class MinimizationMethodInterface;

private:
	static ImplicitIntegratorInterface *instance__;
	MinimizationMethodInterface *mMinimizationMethod;

};