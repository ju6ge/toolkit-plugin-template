#include "{{ plugin_name }}ModelExtension.h"

{% if qt3d -%}
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>

using namespace Qt3DCore;
using namespace Qt3DRender;
using namespace Qt3DExtras;
{%- endif %}

{{ plugin_name }}ModelExtension::{{ plugin_name }}ModelExtension() : WrapperExtension() 
{
}

std::string {{ plugin_name }}ModelExtension::getExtensionName() {
	return "{{ plugin_name }}";
}

void {{ plugin_name }}ModelExtension::update(float current_time) {
	//nothing to update in sync with time
}

