#ifndef QUERYDATA_H
#define QUERYDATA_H
#include <QString>
#include "helper.h"
class QueryData : public Helper
{

public:

    QueryData();

    QStringList allProjects ();

    QStringList allAnnotations ();

    QStringList queryProject(QString query);

    QStringList queryAnnotation(QString query);

    
};

#endif // QUERYDATA_H
