#ifdef _EXPORTING
	#define CLASS_DECLSPEC __declspec(dllexport)
#else
	#define CLASS_DECLSPEC __declspec(dllimport)
#endif


class CLASS_DECLSPEC LineSearchInterface {
public:
	virtual ~LineSearchInterface(){}
	virtual double lineSearch() = 0;

protected:
	LineSearchInterface() {}
};


class CLASS_DECLSPEC BacktrackingLineSearch : public LineSearchInterface {
public:
	static LineSearchInterface *Instance();

	virtual double lineSearch() override;

protected:
	BacktrackingLineSearch() {}

private:
	static LineSearchInterface *instance__;
};


class CLASS_DECLSPEC NoLineSearch : public LineSearchInterface {
public:
	static LineSearchInterface *Instance();

	virtual  double lineSearch() override;

protected:
	NoLineSearch(){}

private:
	static LineSearchInterface *instance__;
};