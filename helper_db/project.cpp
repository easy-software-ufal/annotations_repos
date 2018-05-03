#include "project.h"

Project::Project(QString id) {
    BaseInfoClass::mId = id;
}

Project::Project(QJsonObject jsonobject)
{
    this->fromJson(jsonobject);
}

Project::Project() {}

bool Project::fromJson(QJsonObject &obj) {
    if (obj.contains(an_str_ref) && obj.contains(prjid_str_ref)) {
        QJsonArray annotations = obj[an_str_ref].toArray();
        for (auto && k : annotations ) {
            auto ref = new BaseInfoClass (k.toString());
            mReferenceList.append(ref);
            deletable_refs.append(ref);
        }
        QString id = obj[prjid_str_ref].toString();
        this->setId(id);

        return true; // Successfully loaded json
    }
    return false;
}

QJsonObject Project::toJson() const {
    QJsonArray annotationsReferences;
    for (auto && v : BaseInfoClass::mReferenceList) {
        annotationsReferences.append(v->toString());
    }
    QJsonObject seralized;
    seralized.insert(prjid_str_ref,this->toString());
    seralized.insert(an_str_ref,annotationsReferences);
    return seralized;
}
