#include "Selectable.hpp"
#include "SelectManager.hpp"

Selectable::Selectable()
{
	// When a Selectable is made it is put into the SelectManager
	// and then updated from there
	SelectManager::getInstance()->add(this);
}