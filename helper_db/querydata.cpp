#include "querydata.h"

QueryData::QueryData()
{

}

QStringList QueryData::allProjects() {
    QStringList strlist;
    if (!Helper::mProjectStringtoObj.isEmpty()) {
        strlist = QStringList(mProjectStringtoObj.keys());
    } else {
        strlist << QStringLiteral("No projects available");
    }
    return strlist;
}

QStringList QueryData::allAnnotations() {
    QStringList strlist;
    if (!Helper::mAnnotationStringtoObj.isEmpty()) {
        strlist = QStringList(mAnnotationStringtoObj.keys());
    } else {
        strlist << QStringLiteral("No annotations available");
    }
    return strlist;
}

QStringList QueryData::queryProject(QString query) {
    QStringList strlist;
    if (mProjectStringtoObj.keys().contains(query)) {
        strlist << query << Helper::getProject(query).gRefsStr();
    } else {
        strlist << query << QStringLiteral(" Doesn't exists");
    }
    return strlist;
}

QStringList QueryData::queryAnnotation(QString query) {
    QStringList strlist;
    if (mAnnotationStringtoObj.keys().contains(query)) {
        strlist << query << Helper::getAnnotation(query).gRefsStr();
    } else {
        strlist << query << QStringLiteral(" Doesn't exists");
    }
    return strlist;
}
