#include <iostream>
#include "lineSearch.h"

LineSearchInterface *BacktrackingLineSearch::instance__ = 0;

LineSearchInterface *BacktrackingLineSearch::Instance() {
	if (instance__ == 0) {
		instance__ = new BacktrackingLineSearch();
	}
	return instance__;
}


double BacktrackingLineSearch::lineSearch() {
	std::cout << "Backtracking LineSearch" << std::endl;
	return 0.0;
}


LineSearchInterface *NoLineSearch::instance__ = 0;

LineSearchInterface *NoLineSearch::Instance() {
	if (instance__ == 0) {
		instance__ = new NoLineSearch();
	}
	return instance__;
}

double NoLineSearch::lineSearch() {
	std::cout << "NoLineSearch" << std::endl;
	return 1.0;
}