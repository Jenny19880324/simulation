#ifdef _EXPORTING
	#define CLASS_DECLSPEC __declspec(dllexport)
#else
	#define CLASS_DECLSPEC __declspec(dllimport)
#endif

class IntegratorInterface;


class CLASS_DECLSPEC Simulation{
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