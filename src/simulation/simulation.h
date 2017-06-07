class IntegratorInterface;


class Simulation{
public:
	Simulation(){}
	~Simulation(){}
	
	void update();
	void setIntegrator(IntegratorInterface *);

private:
	friend class IntegratorInterface;
	
private:
	IntegratorInterface *mIntegrator;
};