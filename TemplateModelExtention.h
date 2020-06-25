#ifndef {{ plugin_name | upper }}MODELEXTENTION_H_INCLUDED
#define {{ plugin_name | upper }}MODELEXTENTION_H_INCLUDED

#include <rbdl_wrapper.h>
{% if qt3d -%}
#include <Qt3DRender>
#include <Qt3DCore>
{%- endif %}

class {{ plugin_name }}ModelExtention : public WrapperExtention {
	private:
		// Vars
		// 
		// int dof;
		// float max_time;
	public:
		{{ plugin_name }}ModelExtention();

		// These Functions need to be implemented
		std::string getExtentionName();
		void update(float current_time);

		// Optional Model wrapper virtual functions
		// Qt3DCore::QEntity* getVisual();
		// void exportData();

		// Getter and Setter functions
		// int getDOF();
		// float getMaxTime();

};

#endif
