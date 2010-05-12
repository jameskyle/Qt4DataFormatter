/*
 *  QtFormatter.cpp
 *  Qt4DataFormatter
 *
 *  Created by James Kyle on 5/4/10.
 *  Copyright 2010 KSpace MRI. All rights reserved.
 *
 */
#include "/Developer/Applications/Xcode.app/Contents/PlugIns/GDBMIDebugging.xcplugin/Contents/Headers/DataFormatterPlugin.h"
#include <string.h>
#include <stdlib.h>
#include <QtCore/QString>

#include <string>

/* definition of the plugin function list is required here */
_pbxgdb_plugin_function_list *_pbxgdb_plugin_functions = NULL;

const char* printQString(QString *data, int ID) {
  std::string result;
	
  if (NULL != _pbxgdb_plugin_functions ) {
    result = _pbxgdb_plugin_functions->message(ID, "%s", qPrintable(*data));
  }
  return result.c_str();    
}
