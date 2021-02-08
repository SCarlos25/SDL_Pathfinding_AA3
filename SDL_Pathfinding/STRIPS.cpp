#include "STRIPS.h"

bool STRIPS::ConditionsAccomplished(std::unordered_map<std::string, bool>& currConditions) {
	for (auto it = conditions.begin(); it != conditions.end(); it++) {
		if (it->second != currConditions[it->first])
			return false;
	}

	/*for (auto it = conditions.begin(); it != conditions.end(); it++) {
		if (it->second != blackboard->conditions[it->first])
			return false;
	}*/

	return true;
}

void STRIPS::TriggerEffects(std::unordered_map<std::string, bool>& currConditions) {
	for (auto it = effects.begin(); it != effects.end(); it++) {
		currConditions[it->first] = it->second;
	}

	/*for (auto it = effects.begin(); it != effects.end(); it++) {
		blackboard->conditions[it->first] = it->second;
	}*/
}













