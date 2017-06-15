#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif


//forward declaration
class MinimizationMethodInterface;
class Simulation;

class CLASS_DECLSPEC IntegratorInterface{
public:
	virtual ~IntegratorInterface(){}
	virtual void update(Simulation *) = 0;

protected:
	IntegratorInterface(){}
};


class CLASS_DECLSPEC ExplicitIntegratorInterface : public IntegratorInterface {
public:
	virtual ~ExplicitIntegratorInterface(){}

protected:
	ExplicitIntegratorInterface() {}
};


class CLASS_DECLSPEC ForwardEuler : public ExplicitIntegratorInterface {
public:
	static ExplicitIntegratorInterface *Instance();
	void update(Simulation *) override;

private:
	static ExplicitIntegratorInterface *instance__;
};


class CLASS_DECLSPEC ExplicitMidpoint : public ExplicitIntegratorInterface {
public:
	static ExplicitIntegratorInterface *Instance();
	void update(Simulation *) override;

private:
	static ExplicitIntegratorInterface *instance__;
};


class CLASS_DECLSPEC ExplicitSymplectic : public ExplicitIntegratorInterface {
public:
	static ExplicitIntegratorInterface *Instance();
	void update(Simulation *) override;

private:
	static ExplicitIntegratorInterface *instance__;
};


class CLASS_DECLSPEC RungeKutta4 : public ExplicitIntegratorInterface {
public:
	static ExplicitIntegratorInterface *Instance();
	void update(Simulation *) override;

private:
	static ExplicitIntegratorInterface *instance__;
};


class CLASS_DECLSPEC AdaptiveRungeKutta : public ExplicitIntegratorInterface {
public:
	static ExplicitIntegratorInterface *Instance();
	void update(Simulation *) override;

private:
	static ExplicitIntegratorInterface *instance__;
};








class CLASS_DECLSPEC ImplicitIntegratorInterface : public IntegratorInterface{
public:
	virtual ~ImplicitIntegratorInterface(){}
	virtual void setMinimizationMethod(MinimizationMethodInterface *) = 0;
	virtual void solveMinimization() = 0;

protected:
	ImplicitIntegratorInterface(){}
};



class CLASS_DECLSPEC QuasiStatic : public ImplicitIntegratorInterface {
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


class CLASS_DECLSPEC BackwardEuler : public ImplicitIntegratorInterface{
public:
	static ImplicitIntegratorInterface *Instance();
	
	BackwardEuler();
	~BackwardEuler();

	void setMinimizationMethod(MinimizationMethodInterface *) override;
	void solveMinimization() override;
	void update(Simulation *) override;

private:
	friend class MinimizationMethodInterface;

private:
	static ImplicitIntegratorInterface *instance__;
	MinimizationMethodInterface *mMinimizationMethod;

};


class CLASS_DECLSPEC BDF2 : public ImplicitIntegratorInterface {
public:
	static ImplicitIntegratorInterface *Instance();

	BDF2();
	~BDF2();


	void setMinimizationMethod(MinimizationMethodInterface *) override;
	void solveMinimization() override;
	void update(Simulation *) override;

private:
	friend class MinimizationMethodInterface;

private:
	static ImplicitIntegratorInterface *instance__;
	MinimizationMethodInterface *mMinimizationMethod;

	



};