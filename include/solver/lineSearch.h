#ifdef _EXPORTING
	#define CLASS_DECLSPEC __declspec(dllexport)
#else
	#define CLASS_DECLSPEC __declspec(dllimport)
#endif


#include "typedef.h"

class ImplicitIntegratorInterface;


class CLASS_DECLSPEC LineSearchInterface {
public:
	virtual ~LineSearchInterface(){}
	virtual double lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const = 0;

protected:
	LineSearchInterface() {}
};


class CLASS_DECLSPEC BacktrackingLineSearch : public LineSearchInterface {
public:
	static LineSearchInterface *Instance(const ImplicitIntegratorInterface *);

	virtual double lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const override;

protected:
	BacktrackingLineSearch(const ImplicitIntegratorInterface *);

private:
	static LineSearchInterface *instance__;

	const ImplicitIntegratorInterface *mIntegrator;

	double mRho;  //to determine how much the energy should decrease
	double mC;    //to scale down step size
};


class CLASS_DECLSPEC NoLineSearch : public LineSearchInterface {
public:
	static LineSearchInterface *Instance(const ImplicitIntegratorInterface *);

	virtual  double lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const override;

protected:
	NoLineSearch(const ImplicitIntegratorInterface *);

private:
	static LineSearchInterface *instance__;

	const ImplicitIntegratorInterface *mIntegrator;
};