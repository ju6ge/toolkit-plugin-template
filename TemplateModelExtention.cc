#include "{{ plugin_name }}ModelExtention.h"

{% if qt3d -%}
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>

using namespace Qt3DCore;
using namespace Qt3DRender;
using namespace Qt3DExtras;
{%- endif %}

{{ plugin_name }}ModelExtention::{{ plugin_name }}ModelExtention() : WrapperExtention() 
{
}

std::string {{ plugin_name }}ModelExtention::getExtentionName() {
	return "{{ plugin_name }}";
}

void {{ plugin_name }}ModelExtention::update(float current_time) {
	//nothing to update in sync with time
}

