#ifndef BASEINFOCLASS_H
#define BASEINFOCLASS_H
#include <QString>
#include <QDebug>
#include <QJsonObject>
#include <QList>
#include <memory>

class BaseInfoClass
{

typedef QList<BaseInfoClass*> RefList;
protected:
    RefList mReferenceList;
    RefList deletable_refs;
    QString mId;

    void setId(QString& id);

    void setRefList(QList<BaseInfoClass*>& reflist);
public:

    BaseInfoClass(QString id);

    BaseInfoClass();

    ~BaseInfoClass();

    bool fromJson(QJsonObject& obj);

    QJsonObject toJson() const;

    void appendToRefs(BaseInfoClass* ref=nullptr);

    QStringList gRefsStr() const;

    bool operator == (BaseInfoClass& a) const;

    bool operator == (BaseInfoClass a) const;

    QString toString() const;

    QString getId() const;

    RefList* getRefList() {
        return &mReferenceList;
    }

    void clearOwnedPtrs() {
        if (!this->deletable_refs.empty()) {
            for (auto && k : this->deletable_refs) {
                delete k;
            }
            this->deletable_refs.clear();
        }
    }

// "*reference" must be allocated elsewhere because we won't be deleting it here
    bool updateReference(BaseInfoClass* reference);
};

#endif
