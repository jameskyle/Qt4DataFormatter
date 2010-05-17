/*
 *  QtFormatter.cpp
 *  Qt4DataFormatter
 *
 *  Created by James Kyle on 5/4/10.
 *  Copyright 2010 KSpace MRI. All rights reserved.
 *
 */
#include "/Developer/Applications/Xcode.app/Contents/PlugIns/GDBMIDebugging.xcplugin/Contents/Headers/DataFormatterPlugin.h"
#include <QtCore/QString>
#include <QtCore/QModelIndex>
#include <QtXml/QDomNode>
#include <QtCore/QVariant>
#include <QtCore/QFile>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QList>

#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
// XML stuff

#include <QtXml/QDomElement>

// #define _DEBUG_
/* definition of the plugin function list is required here */
_pbxgdb_plugin_function_list *_pbxgdb_plugin_functions = NULL;

char* stringToFromatBuff(std::string message, int ID)
{
  int bufLen = message.size() + 1;
  char *formatBuff;
  formatBuff = (char *)(_pbxgdb_plugin_functions->allocate(ID, bufLen));
  strncpy(formatBuff, message.data(), bufLen);
  formatBuff[bufLen - 1] = '\0';
  
  // some debug output
#ifdef _DEBUG_
  std::cout << message << std::endl;
#endif
  return formatBuff;
}

char* printQString(QString *data, int ID) 
{
  std::string result;

  if (NULL != _pbxgdb_plugin_functions ) {
    result = _pbxgdb_plugin_functions->message(ID, "%s", qPrintable(*data));
  } else
  {
    result = "Could not map object to QString";
  }
  
  return stringToFromatBuff(result, ID);   
}

char* printQDomNode(QDomNode *data, int ID)
{
  QString msg = QString("tagName: %1, text: %2")
  .arg(data->toElement().tagName()).arg(data->toElement().text());
  
  return printQString(&msg, ID);
}

char* printQModelIndex(QModelIndex *index, int ID) 
{
  QString *result = new QString;

  if (NULL != _pbxgdb_plugin_functions)
  {
    *result = _pbxgdb_plugin_functions->message(ID, "row: %i, col: %i", 
                                               index->row(), index->column());
  } else
  {
    *result = "Could not map object to QModelIndex";
  }
  
  return printQString(result, ID);
}

char* printQVariant(QVariant *variant, int ID)
{
  QString *st = new QString(variant->toString());
  
  return printQString(st, ID);
}

char* printQAbstractItemModel(QAbstractItemModel *model, int ID)
{
  QString *repr = new QString("%1: rows %2, cols %3");
  QString cl = model->metaObject()->className();
  *repr = repr->arg(cl).arg(model->rowCount()).arg(model->columnCount());
  
  return printQString(repr, ID);
}

char* printQFile(QFile *file, int ID)
{
  QString *f = new QString(file->fileName());
  
  return printQString(f, ID);
}

char* printQDomElement(QDomElement *e, int ID)
{
  QString out = e->tagName();
  
  return printQString(&out, ID);
}