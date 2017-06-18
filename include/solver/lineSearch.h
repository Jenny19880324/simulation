#ifdef _EXPORTING
	#define CLASS_DECLSPEC __declspec(dllexport)
#else
	#define CLASS_DECLSPEC __declspec(dllimport)
#endif


#include "typedef.h"

class ImplicitIntegratorInterface;
class Solver;

class CLASS_DECLSPEC LineSearchInterface {
public:
	virtual ~LineSearchInterface(){}
	virtual double lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const = 0;

protected:
	LineSearchInterface() {}
};


class CLASS_DECLSPEC BacktrackingLineSearch : public LineSearchInterface {
public:
	static LineSearchInterface *Instance(const Solver *);

	virtual double lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const override;

protected:
	BacktrackingLineSearch(const Solver *);

private:
	static LineSearchInterface *instance__;

	const Solver *mSolver;

	double mRho;  //to determine how much the energy should decrease
	double mC;    //to scale down step size
};


class CLASS_DECLSPEC NoLineSearch : public LineSearchInterface {
public:
	static LineSearchInterface *Instance(const Solver *);

	virtual  double lineSearch(const VectorX &x, const VectorX &gradient, const VectorX &descentDir) const override;

protected:
	NoLineSearch(const Solver *);

private:
	static LineSearchInterface *instance__;

	const Solver *mSolver;
};