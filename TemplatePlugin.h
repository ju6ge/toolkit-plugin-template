#ifndef CAMERAOPERATORPLUGIN_H_INCLUDED
#define CAMERAOPERATORPLUGIN_H_INCLUDED

#include <QWidget>

#include "toolkit_interfaces.h"

class TemplatePlugin : public QObject, public OptionalInterface {
	Q_OBJECT
	Q_INTERFACES(OptionalInterface)
	Q_PLUGIN_METADATA(IID OptionalInterface_iid FILE "metadata.json")

	public:
		TemplatePlugin();
		virtual ~TemplatePlugin();

		void init(ToolkitApp* app);

	private:
		ToolkitApp* parentApp;

	public slots:
};

#endif 

