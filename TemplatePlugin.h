#ifndef {{ plugin_name | upper }}PLUGIN_H_INCLUDED
#define {{ plugin_name | upper }}PLUGIN_H_INCLUDED

#include <QWidget>
#include <QString>

#include "toolkit_interfaces.h"
#include "toolkit_errors.h"
#include "util.h"

{% if add_extention -%}
#include "{{ plugin_name }}ModelExtention.h"
{%- endif %}

{% if core -%}
class {{ plugin_name }}Plugin : public QObject, public CoreInterface {
	Q_OBJECT
	Q_INTERFACES(CoreInterface)
	Q_PLUGIN_METADATA(IID CoreInterface_iid FILE "metadata.json")
{%- else %}
class {{ plugin_name }}Plugin : public QObject, public OptionalInterface {
	Q_OBJECT
	Q_INTERFACES(OptionalInterface)
	Q_PLUGIN_METADATA(IID OptionalInterface_iid FILE "metadata.json")
{%- endif %}
	public:
		{{ plugin_name }}Plugin();
		virtual ~{{ plugin_name }}Plugin();

		void init(ToolkitApp* app);
		{% if add_extention and filereader -%}
		{{ plugin_name }}ModelExtention* load{{ plugin_name }}File(QString path);
		{%- endif %}
	private:
		ToolkitApp* parentApp;
		{% if filereader -%}
		QAction* load_file_trigger;
		{%- endif %}
		{% if settings -%}
		void load{{ plugin_name }}Settings();
		{%- endif %}
		{% if add_extention and reload -%}
		std::map<RBDLModelWrapper*, QString> model_file_map;
		{%- endif %}
	public Q_SLOTS:
		{% if filereader -%}
		void action_load_data();
		{%- endif %}
		{% if reload -%}
		void reload(RBDLModelWrapper* model);
		{%- endif %}

};

#endif 

