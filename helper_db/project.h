#ifndef PROJECT_H
#define PROJECT_H
#include <QStringList>
#include <QString>
#include <QJsonObject>
#include "baseinfoclass.h"
#include <QJsonArray>

class Project : public BaseInfoClass
{
public:
    Project(QString id);
    Project(QJsonObject jsonobject);
    Project();

    bool fromJson(QJsonObject& obj);

    QJsonObject toJson() const;

    static constexpr const char * an_str_ref = "annotations";
    static constexpr const char * prjid_str_ref = "project_id";
};
#endif // PROJECT_H
