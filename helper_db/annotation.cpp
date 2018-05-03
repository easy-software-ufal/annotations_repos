#include "annotation.h"

void Annotation::setTarget(const QString &target)
{
    mTarget = target;
}

void Annotation::setRetentionPolicy(const QString &retentionPolicy)
{
    mRetentionPolicy = retentionPolicy;
}

void Annotation::setFramework(const QString &framework)
{
    mFramework = framework;
}

Annotation::Annotation(QString id, QString framework) {
    Annotation::Annotation();
    BaseInfoClass::mId = id;
    mFramework = framework;
}

Annotation::Annotation() {
    mFramework = "";
    mDescription = "";
    mTarget = "";
    mRetentionPolicy = "";
}

Annotation::Annotation(QJsonObject o) {
    Annotation::Annotation();
    this->fromJson(o);
}

bool Annotation::fromJson(QJsonObject &obj) {

    if (obj.contains(ann_id_ref) &&
            obj.contains(used_at_ref) &&
            obj.contains(framework_ref) &&
            obj.contains(dscr_ref)) {
        auto annId     = obj[ann_id_ref].toString();
        auto prjRefArr = obj[used_at_ref].toArray();
        auto framework = obj[framework_ref].toString();
        auto dscr      = obj[dscr_ref].toString();

        for (auto && k : prjRefArr) { // adds projects refs to ref list
            auto ref = new BaseInfoClass(k.toString());
            deletable_refs.append(ref);
            mReferenceList.append(ref);
        }

        this->setId(annId); //sets annotation name
        this->mFramework   = framework; // then framework
        this->mDescription = dscr; // then the description
        this->mTarget = obj[target_ref].toString();
        this->mRetentionPolicy = obj[target_ref].toString();
        return true; // if everything is ok
    }
    return false;
}

QJsonObject Annotation::toJson() const {
    QJsonObject serialized;
    QJsonArray prjRefArray;
    for (auto && k : BaseInfoClass::mReferenceList) {
        prjRefArray.append(QJsonValue(k->toString()));
    }
    serialized[ann_id_ref]    = BaseInfoClass::mId;
    serialized[used_at_ref]   = prjRefArray;
    serialized[framework_ref] = QJsonValue(mFramework);
    serialized[dscr_ref]      = QJsonValue(mDescription);
    serialized[retentionPolicy_ref]      = QJsonValue(mRetentionPolicy);
    serialized[target_ref]      = QJsonValue(mTarget);

    return serialized;
}
