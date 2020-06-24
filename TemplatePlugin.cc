#include "TemplatePlugin.h"
#include <iostream>

TemplatePlugin::TemplatePlugin() {
	parentApp = NULL;
}

TemplatePlugin::~TemplatePlugin() {
}

void TemplatePlugin::init(ToolkitApp* app) {
	//save reference to parent ToolkitApp 
	parentApp = app;

	std::cout << "TemplatePlugin loaded" << std::endl;
}

