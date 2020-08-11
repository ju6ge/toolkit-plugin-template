#ifndef {{ plugin_name | upper }}MODELEXTENSION_H_INCLUDED
#define {{ plugin_name | upper }}MODELEXTENSION_H_INCLUDED

#include <rbdl_wrapper.h>
{% if qt3d -%}
#include <Qt3DRender>
#include <Qt3DCore>
{%- endif %}

class {{ plugin_name }}ModelExtension : public WrapperExtension {
	private:
		// Vars
		// 
		// int dof;
		// float max_time;
	public:
		{{ plugin_name }}ModelExtension();

		// These Functions need to be implemented
		std::string getExtensionName();
		void update(float current_time);

		// Optional Model wrapper virtual functions
		// Qt3DCore::QEntity* getVisual();
		// void exportData();

		// Getter and Setter functions
		// int getDOF();
		// float getMaxTime();

};

#endif
