#ifndef ANNOTATION_H
#define ANNOTATION_H
#include "baseinfoclass.h"
#include <QJsonArray>
#include <QJsonObject>


class Annotation : public BaseInfoClass
{
    QString mFramework;
    QString mDescription;
    QString mTarget;
    QString mRetentionPolicy;
public:
    Annotation(QString id, QString framework);
    Annotation();
    Annotation(QJsonObject o);

    bool fromJson(QJsonObject& obj);

    QJsonObject toJson() const;

    static constexpr const char * ann_id_ref    = "annotation";
    static constexpr const char * used_at_ref   = "used_at";
    static constexpr const char * framework_ref = "framework";
    static constexpr const char * dscr_ref      = "description";
    static constexpr const char * target_ref      = "target";
    static constexpr const char * retentionPolicy_ref      = "retentionpolicy";

    void setTarget(const QString &target);
    void setRetentionPolicy(const QString &retentionPolicy);
    void setFramework(const QString &framework);
};

#endif // ANNOTATION_H
