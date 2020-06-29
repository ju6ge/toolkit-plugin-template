#include "{{ plugin_name }}Plugin.h"
#include <iostream>

{% if filereader -%}
#include <QFileDialog>
#include <QMessageBox>
{%- endif %}
{% if cmd -%}
#include <QCommandLineParser>
#include <QCommandLineOption>
{%- endif %}
{% if add_extention -%}
#include <rbdl_wrapper.h>
{%- endif %}

{{ plugin_name }}Plugin::{{ plugin_name }}Plugin() {
	parentApp = NULL;
}

{{ plugin_name }}Plugin::~{{ plugin_name }}Plugin() {
}

void {{ plugin_name }}Plugin::init(ToolkitApp* app) {
	//save reference to parent ToolkitApp 
	parentApp = app;

	{% if filereader -%}
	load_file_trigger = new QAction("Load {{ plugin_name }}");
	parentApp->addFileAction(load_file_trigger);

	connect(load_file_trigger, SIGNAL(triggered(bool)), this, SLOT(action_load_data()));
	{%- endif %}

	{% if cmd -%}
	QCommandLineOption {{ plugin_name | lower }}_option( QStringList() << "{{ plugin_name | lower }}",
	                                 "Load {{ plugin_name }} files <file>", 
	                                 "file"
	                               );
	parentApp->addCmdOption({{ plugin_name | lower }}_option, [this](QCommandLineParser& parser){
		auto data_list = parser.values("{{ plugin_name | lower }}");
		{% if add_extention -%}
		for (int i=0; i<data_list.size(); i++) {
			if (i < parentApp->getLoadedModels()->size() ) {
				auto file = data_list[i];
				{{ plugin_name }}ModelExtention* ext = nullptr;
				try {
					ext = load{{ plugin_name }}File(file);
				} catch (RigidBodyDynamics::Errors::RBDLError& e){
					ToolkitApp::showExceptionDialog(e);
					if (ext != nullptr)
						delete ext;
					continue;
				}
				RBDLModelWrapper* rbdl_model = parentApp->getLoadedModels()->at(i);
				rbdl_model->addExtention(ext);
				{% if reload -%}
				model_file_map[rbdl_model] = file;
				{%- endif %}
			} else {
				std::cout << QString("{{ plugin_name }} file %1 can not be mapped to a model ... Ignoring!").arg(data_list[i]).toStdString() << std::endl;
			}
		}
		{% else -%}
		// implement cmd function here
		{%- endif %}
	});
	{%- endif %}

	{% if settings -%}
	load{{ plugin_name }}Settings();
	{%- endif %}

	std::cout << "{{ plugin_name }}Plugin loaded" << std::endl;

	{% if reload -%}
	connect(parentApp, &ToolkitApp::reloaded_model, this, &{{ plugin_name }}Plugin::reload);
	{%- endif %}
}

{% if settings -%}
void {{ plugin_name }}Plugin::load{{ plugin_name }}Settings() {
	parentApp->toolkit_settings.beginGroup("{{ plugin_name }}Options");

	// example read/write of setting

	//QVariant val = parentApp->toolkit_settings.value("marker.color");
	//if (val.isNull()) {
	//	marker_color = QColor::fromRgbF(0., 0., 1., 1.);
	//	parentApp->toolkit_settings.setValue("marker.color", marker_color.rgba());
	//} else {
	//	marker_color = QColor::fromRgba(val.toUInt());
	//}
	//parentApp->toolkit_settings.setType("marker.color", marker_color);

	parentApp->toolkit_settings.endGroup();
}
{%- endif %}

{% if filereader -%}
void {{ plugin_name }}Plugin::action_load_data() {
	if (parentApp != NULL) {
		QFileDialog file_dialog (parentApp, "Select {{ plugin_name }} File");

		//file_dialog.setNameFilter(tr("{{ plugin_name }} File (*.txt)"));
		file_dialog.setFileMode(QFileDialog::ExistingFile);

		{% if add_extention -%}
		{{ plugin_name }}ModelExtention* ext;
		{%- endif %}
		if (file_dialog.exec()) {
			QString filepath;
			try {
				filepath = file_dialog.selectedFiles().at(0);
				{%- if add_extention -%}
				ext = load{{ plugin_name }}File(filepath);
				{%- endif %}
			} catch (RigidBodyDynamics::Errors::RBDLError& e){
				ToolkitApp::showExceptionDialog(e);
				{%- if add_extention -%}
				delete ext;
				{%- endif %}
			}
			{% if add_extention -%}
			if (parentApp->getLoadedModels()->size() != 0) {
				RBDLModelWrapper* rbdl_model = nullptr;

				if (parentApp->getLoadedModels()->size() == 1) {
					rbdl_model = parentApp->getLoadedModels()->at(0);
				} else {
					rbdl_model = parentApp->selectModel(nullptr);
				}

				if (rbdl_model != nullptr) {
					rbdl_model->addExtention(ext);
					{% if reload -%}
					model_file_map[rbdl_model] = file_dialog.selectedFiles().at(0);
					{%- endif %}
				} else {
					delete ext;
				}
			}
			{%- endif %}
		}	
	} else {
		//should never happen
		throw RigidBodyDynamics::Errors::RBDLError("{{ plugin_name }}Plugin was not initialized correctly!");
	}
}
{%- endif %}

{% if filereader and add_extention -%}
{{ plugin_name }}ModelExtention* {{ plugin_name }}Plugin::load{{ plugin_name }}File(QString path) {
	{{ plugin_name }}ModelExtention* extention = new {{ plugin_name }}ModelExtention();

	//implement open of file + read data + put in extention here

	return extention;
}
{%- endif %}

{% if reload -%}
void {{ plugin_name }}Plugin::reload(RBDLModelWrapper *model) {
	{% if add_extention -%}
	for (auto it = model_file_map.begin(); it != model_file_map.end(); it++) {
		if ( it->first == model ) {
			auto ext = load{{ plugin_name }}File(it->second);
			model->addExtention(ext);
		}
	}
	{%- endif %}
}
{%- endif %}
