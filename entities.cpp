#include "entities.h"

Entity::Entity()
{
}

int Entity::get_number()
{
	return number;
}

string & Entity::get_name()
{
	return name;
}

bool Entity::compare_number(int number_to_compare)
{
	return false;
}

void Entity::update_data(Entity& to_copy)
{
}

Member::Member(): status("") {}

void Member::update_data(Member & to_copy)
{
}

Provider::Provider()
{
}

void Provider::update_data(Provider& to_copy)
{
}
