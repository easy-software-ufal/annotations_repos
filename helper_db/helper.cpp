#include "helper.h"

Helper::Helper() {}

Helper::~Helper() {
    for (auto && k : this->allocated) {
        delete k;
    }
}

void Helper::procInput(QString project, QString annotation) {
    Project* prj = gProject(project);
    Annotation* ann = gAnnotation(annotation);
    prj->appendToRefs(ann);
    ann->appendToRefs(prj);
}

QString Helper::gProjectAnnotations(QString &project) {
    Project * prj = gProject(project);
    QString f;
    for(auto && ann : prj->gRefsStr() ) {
        f += ann + " ";
    }
    return f;
}

QString Helper::gAnnotationsProjectRefs(QString &ann) {
    Annotation * an_i = gAnnotation(ann);
    QString f;
    for(auto && prj : an_i->gRefsStr() ) {
        f += prj + " ";
    }
    return f;
}

Project &Helper::getProject(QString strprj) {
    return *mProjectStringtoObj[strprj];
}

Annotation &Helper::getAnnotation(QString strannotation) {
    return *mAnnotationStringtoObj[strannotation];
}

QJsonDocument Helper::serializeProjects() const {
    QJsonArray allPrjsArr;
    auto allprjs = mProjectStringtoObj.values();
    for (auto && prjptr : allprjs) {
        allPrjsArr.append(prjptr->toJson());
    }
    return QJsonDocument(allPrjsArr);
}

QJsonDocument Helper::serializeAnnotations() const {
    QJsonArray allAnnotations;
    auto allAnn = mAnnotationStringtoObj.values();
    for (auto && annptr : allAnn) {
        allAnnotations.append(annptr->toJson());
    }
    return QJsonDocument(allAnnotations);
}

bool Helper::deserializeProjects(QJsonDocument doc) {
    QJsonArray projectsArray = doc.array();
    for (QJsonValue o : projectsArray) {
        auto obj = o.toObject();
        auto project = new Project(obj);
        mProjectStringtoObj[project->getId()] = project;
        allocated.push_back(project);
    }
    return projectsArray.empty();
}

bool Helper::deserializeAnnotations(QJsonDocument doc) {
    QJsonArray annotationsArray = doc.array();
    for (QJsonValue o : annotationsArray) {
        auto obj = o.toObject();
        auto annotation = new Annotation(obj);
        mAnnotationStringtoObj[annotation->getId()] = annotation;
        allocated.push_back(annotation);
    }
    return !annotationsArray.empty();
}

bool Helper::annotationExists(QString annotation)
{
    return mAnnotationStringtoObj.keys().contains(annotation);
}

const Annotation *Helper::getAnnotationPtr(QString annotation)
{
   if (this->annotationExists(annotation))
       return mAnnotationStringtoObj[annotation];
}

bool Helper::deserialize(QJsonDocument annotationJsonDocument, QJsonDocument projectJsonDocument) {
    bool ok = deserializeAnnotations(annotationJsonDocument) && deserializeProjects(projectJsonDocument);
    updateReferences();
    return ok;
}

void Helper::updateReferences() {
    //for each pointer to project
    for(auto&& ptr : mProjectStringtoObj.values()){
        //for each reference to annotation
        for (auto i = 0; i < ptr->getRefList()->size(); ++i) {
            auto ref = ptr->getRefList()->at(i);
            //replace old reference with new reference
            ptr->getRefList()->replace(i,mAnnotationStringtoObj[ref->getId()]);
        }
        ptr->clearOwnedPtrs();
    }

    //for each pointer to annotation
    for(auto&& ptr : mAnnotationStringtoObj.values()) {
        //for each reference to project
        for (auto i = 0; i < ptr->getRefList()->size(); ++i) {
            auto ref = ptr->getRefList()->at(i);
            //replace old reference with new reference
            ptr->getRefList()->replace(i,mProjectStringtoObj[ref->getId()]);
        }
        ptr->clearOwnedPtrs();
    }
}

Annotation *Helper::gAnnotation(QString strannotation) {
    if (!mAnnotationStringtoObj.contains(strannotation)) {
        auto alloc_an = new Annotation(strannotation,"");
        mAnnotationStringtoObj[strannotation] = alloc_an;
        this->allocated.append(alloc_an);
    }
    return mAnnotationStringtoObj[strannotation];
}

Project *Helper::gProject(QString strprj) {
    if (!mProjectStringtoObj.contains(strprj)) {
        auto alloc_prj = new Project(strprj);
        mProjectStringtoObj[strprj] = alloc_prj;
        this->allocated.append(alloc_prj); // Store all pointers, so we can delete them later
    }
    return mProjectStringtoObj[strprj];
}
