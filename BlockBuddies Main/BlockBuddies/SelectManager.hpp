#ifndef SELECTMANAGER_HPP
#define SELECTMANAGER_HPP

#include "Selectable.hpp"
#include <vector>

// Manages tabbing between different Selectable elements
class SelectManager
{
public:
	static SelectManager* getInstance();
	void init();
	void add(Selectable* selectable);
	void clear();
	void update();

	// Vector of Selectable pointers that we'll be manipulating
	std::vector<Selectable*> selectables;
private:	
	SelectManager(){};
	SelectManager(SelectManager const&){};
	SelectManager& operator=(SelectManager const&){};

	static SelectManager* instance;
};

#endif//SELECTMANAGER_HPP