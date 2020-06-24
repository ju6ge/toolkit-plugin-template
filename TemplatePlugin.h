#ifndef {{ plugin_name | upper }}PLUGIN_H_INCLUDED
#define {{ plugin_name | upper }}PLUGIN_H_INCLUDED

#include <QWidget>

#include "toolkit_interfaces.h"

class {{ plugin_name }}Plugin : public QObject, public OptionalInterface {
	Q_OBJECT
	Q_INTERFACES(OptionalInterface)
	Q_PLUGIN_METADATA(IID OptionalInterface_iid FILE "metadata.json")

	public:
		{{ plugin_name }}Plugin();
		virtual ~{{ plugin_name }}Plugin();

		void init(ToolkitApp* app);

	private:
		ToolkitApp* parentApp;

	public slots:
};

#endif 

