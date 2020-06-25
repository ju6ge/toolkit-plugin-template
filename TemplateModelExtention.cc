#include "{{ plugin_name }}ModelExtention.h"

{{ plugin_name }}ModelExtention::{{ plugin_name }}ModelExtention() : WrapperExtention() 
{
}

std::string {{ plugin_name }}ModelExtention::getExtentionName() {
	return "{{ plugin_name }}";
}

void {{ plugin_name }}ModelExtention::update(float current_time) {
	//nothing to update in sync with time
}

