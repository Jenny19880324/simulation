//forward declaration
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