#include "baseinfoclass.h"

void BaseInfoClass::setId(QString &id) {
    this->mId = id;
}

void BaseInfoClass::setRefList(QList<BaseInfoClass *> &reflist) {
    this->mReferenceList = reflist;
}

BaseInfoClass::BaseInfoClass(QString id) : mId(id) {}

BaseInfoClass::BaseInfoClass(){}

bool BaseInfoClass::fromJson(QJsonObject &obj) {
    return false;
}

QJsonObject BaseInfoClass::toJson() const {return QJsonObject();}

BaseInfoClass::~BaseInfoClass() {
   clearOwnedPtrs();
   mReferenceList.clear();
}

void BaseInfoClass::appendToRefs(BaseInfoClass *ref) {
    if (ref != nullptr) {
        if (!mReferenceList.contains(ref)) {
            mReferenceList.append(ref);
        }
    }
}

QStringList BaseInfoClass::gRefsStr() const {
    QStringList strList;
    for(auto&& ref : mReferenceList) {
        strList.append(ref->toString());
    }
    return strList;
}

QString BaseInfoClass::toString() const {return mId;}

QString BaseInfoClass::getId() const
{
   return mId;
}

bool BaseInfoClass::updateReference(BaseInfoClass *reference) {
    int i = deletable_refs.indexOf(reference);
    int i2 = mReferenceList.indexOf(reference);
    //Delete owned reference
    if (i >= 0 ) {
        delete deletable_refs.at(i);
        if (i2 >= 0 ) {
            //Update reference
            mReferenceList[i2] = reference;
        }
        return true;
    }
    //Haven't found related reference, can't update
    return false;
}

bool BaseInfoClass::operator ==(BaseInfoClass &a) const{
    return (this->mId == a.mId) && (a.mReferenceList == this->mReferenceList);
}

bool BaseInfoClass::operator ==(BaseInfoClass a) const{
    return (this->mId == a.mId) && (a.mReferenceList == this->mReferenceList);
}
