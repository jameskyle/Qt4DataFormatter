/*
 *  Qt4DataFormatterTest.cpp
 *  Qt4DataFormatter
 *
 *  Created by James Kyle on 5/12/10.
 *  Copyright 2010 KSpace MRI. All rights reserved.
 *
 */

#include <QtCore/QString>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QList>

#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtXml/QDomDocument>

void testReference(QString& test)
{
  test = "foobar";
};

int main() {
  // xml stuff
  QDomElement *ele = new QDomElement;
  ele->setTagName(QString("testTag"));
  
  
  QString st("This is a string");
  QString *p_st = new QString("This is a string pointer");
  
  testReference(st);
  QModelIndex index;
  QModelIndex *p_index = new QModelIndex;
  
  QVariant variant;
  variant.setValue(QString("A very interesting variant"));
  QVariant *p_variant = new QVariant;
  p_variant->setValue(QString("A very interesting variant pointer"));
  
  QFile file("/tmp/foo.txt");
  QFile *p_file = new QFile("/tmp/pfoo.txt");
  
  QDomDocument dom;
  dom.setContent(QString("<root><child>some text</child></root>"));
  QDomNode root = dom.firstChild();
  qDebug() << root.toElement().tagName();
  return 0;
}

