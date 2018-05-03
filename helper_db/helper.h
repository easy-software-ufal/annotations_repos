#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include "project.h"
#include "annotation.h"
#include <QJsonDocument>

class Helper
{
    friend class QueryData;
public:
    Helper();

    ~Helper();

    void procInput(QString project, QString annotation);

    QString gProjectAnnotations(QString& project);

    QString gAnnotationsProjectRefs(QString& ann);

    Project& getProject(QString strprj);

    Annotation& getAnnotation(QString strannotation);

    QJsonDocument serializeProjects() const;

    QJsonDocument serializeAnnotations() const;

    bool deserialize(QJsonDocument annotationJsonDocument, QJsonDocument projectJsonDocument);

    void updateReferences();

    bool deserializeProjects(QJsonDocument doc);

    bool deserializeAnnotations(QJsonDocument doc);

    bool annotationExists(QString annotation);

    const Annotation* getAnnotationPtr(QString annotation);

private:


    Annotation* gAnnotation(QString strannotation);

    Project* gProject(QString strprj);

    QHash<QString,Project*> mProjectStringtoObj;
    QHash<QString,Annotation*> mAnnotationStringtoObj;
    QList<BaseInfoClass*> allocated;
};

#endif // HELPER_H
