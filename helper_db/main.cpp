#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "helper.h"
#include <QDebug>
#include "tests.h"
#include "querydata.h"
#include <QCommandLineParser>

#include <iostream>
#include <string>
#include <QRegularExpressionValidator>
static QueryData qData;
static QRegularExpressionValidator rvalidateAnnotation(QRegularExpression(QString("@[A-Z][A-z]+")));
static QRegularExpressionValidator rvalidateProject(QRegularExpression(QString("\\S{3,}\\/\\S{3,}")));

bool validateProject(QString& project) {
    int vpos = 0;
    return rvalidateProject.validate(project,vpos) == QValidator::Acceptable;
}

bool validateAnnotation(QString& annotation) {
    int vpos = 0;
    return rvalidateAnnotation.validate(annotation,vpos) == QValidator::Acceptable;
}


enum FUNCSTATE {
    CONTINUE,
    EXIT
};

enum cliselection {
    s,
    q,
    cnew,
    p,
    a,
    i,
    none
};

cliselection trcliselection(QString str) {
    cliselection ret = cliselection::none;
    if (str == "s") {
        ret = cliselection::s;
    } else if (str == "q") {
        ret = cliselection::q;
    } else if (str == "new") {
        ret = cliselection::cnew;
    } else if (str == "p") {
        ret = cliselection::p;
    } else if (str == "a") {
        ret = cliselection::a;
    } else if (str == "i") {
        ret = cliselection::i;
    }
    return ret;
}


QStringList readLine() {
    QString line = "";
    std::string buffer;
    std::getline(std::cin,buffer);
    line = QString(buffer.c_str());
    return line.split(QRegularExpression("\\s+"));
}

void strOutput(QStringList strlist) {
    for (auto&& str : strlist) {
        qWarning() << str;
    }
}

FUNCSTATE queryProject() {
    qWarning() << "q to exit, project to display a project.";

    auto func = []()-> FUNCSTATE {
            FUNCSTATE state = FUNCSTATE::CONTINUE;
            auto option = readLine();
            if (!option.empty())

            switch (trcliselection(option[0])) {
        case cliselection::s:
            if (option.size() == 2) {
                strOutput(qData.queryProject(option[1]));
            } else {
                qWarning() << "Must type a project name.";
            }
            break;
        case cliselection::q:
            state = FUNCSTATE::EXIT;
            break;
        default:
            qWarning() << "Not recognized. Type (q)uit or (s)elect pro/ject.";
            break;
    }
        return state;
    };

    if (func() != FUNCSTATE::EXIT)
        return queryProject();
    else return FUNCSTATE::EXIT;
}

FUNCSTATE queryAnnotation() {

    qWarning() << "'q' to exit,'s' @Annotation to display an annotation.";
    qWarning() << "'p' to dump to file.";

    auto func = []()-> FUNCSTATE { FUNCSTATE state = FUNCSTATE::CONTINUE;
    QStringList option = readLine();

    if (!option.empty())

        switch (trcliselection(option[0])) {
        case cliselection::s:
            if (option.size() == 2) {
                strOutput(qData.queryAnnotation(option[1]));
            } else {
                qWarning() << "Type at least one annotation.";
            }
            break;
        case cliselection::q:
            state = FUNCSTATE::EXIT;
            break;
        default:
            //if "p"

            if(option[0] == "p") {
                qWarning() << "Type where to save";
                auto whr = readLine().at(0);
                QFile file(whr);
                if (file.open(QFile::WriteOnly | QIODevice::Text) ) {
                    QTextStream stream(&file);
                    for (auto&& i : qData.allAnnotations()) {
                        stream << i << '\n';
                    }
                    file.close();
                    qWarning() << "Wrote all annotations to " << whr;
                } else {
                    qWarning() << "Couldn't open file.";
                }
            }
            else if (option[0] == "e") {
                qWarning() << "Type which annotation you wish to edit.";
                qWarning() << "Type q to end edition.";

                auto line = readLine();
                if(validateAnnotation(option[1]) && qData.annotationExists(option[1])) {
                    auto soption = readLine();
                    if (soption[0] == "f") {
                        qWarning() << "Framework selected";
                        qWarning() << "Current:" <<
                    } else if (soption[0] == "f") {

                    } else if () {

                    }
                    } else {
                        qWarning() << option[1] << "Doesn't exists or is invalid";
                    }

            }


            else {
                qWarning() << "Not recognized. Type (q)uit or (s)elect annotation.";
            }
                break;
        }

    return state;
    };
    if (func() != FUNCSTATE::EXIT)
        return queryAnnotation();
    else
        return FUNCSTATE::EXIT;
}

FUNCSTATE annotationSelection() {
    strOutput(qData.allAnnotations());
    return queryAnnotation();
}


FUNCSTATE projectSelection() {
    strOutput(qData.allProjects());
    return queryProject();
}



FUNCSTATE insertData() {
    qWarning() << "q to exit, new to insert new project.";
    qWarning() << "nothing after 'new' to add to same project.";
    FUNCSTATE state = FUNCSTATE::CONTINUE;
    QString project;

    while (1) {
        auto option = readLine(); // "option" "project" "annotation"+
        if (option[0] == "new" && option.size() >= 3) { // see if option is "new"
            if (validateProject(option[1])) { // See if option[1] is a valid project
                project = option[1];// if it is
                for(auto i = 2; i != option.size(); ++i) {
                    auto annotation = option[i];
                    if (validateAnnotation(annotation)) { // if annotation is a valid annotation
                        qData.procInput(project,annotation);
                    } else { // warn it's not
                        qWarning() << "Ignoring" << annotation;
                    }
                }
            } else { // Warns it's not
                qWarning() << option[1] << " is not a valid project.";
            }
        } else { //handle q and adding annotations continuation
            if (project.size() > 0) { // if theres some string stored in project

                if(option[0] == "q") {
                    goto gexit;
                } else {
                    if (validateProject(project)) { //if it's a valid project
                        for(auto&& i : option) {
                            if (validateAnnotation(i)) {
                                qData.procInput(project,i);
                            } else {
                                qWarning() << "Ignoring " << i;
                            }
                        }
                    } else {
                        qWarning() << project << " is not a valid project.";
                    }
                }
            } else { // handle for q and for unreconized
                gexit:
                if(option[0] == "q") {
                    state = FUNCSTATE::EXIT;
                    goto loopend;
                } else {
                    qWarning() << option[0] << " is unrecognized.";
                }
            }
        }
    }
    loopend:
    return state;
}

int initialSelection() {
    int ret = 0;
    qWarning() << "Type\t\tFor";
    qWarning() << "(p) rojects\t\tDisplay all projects";
    qWarning() << "(a) nnotations\t\tDisplay all annotations";
    qWarning() << "(i)\t\tTo insert data";
    qWarning() << "(q)\t\tTo exit";
    auto line = readLine();

    if (line[0] == "p") {
        system("tput reset");
        projectSelection();
        system("tput reset");
    } else if (line[0] == "a") {
        system("tput reset");
        annotationSelection();
        system("tput reset");
    } else if (line[0] == "i") {
        system("tput reset");
        insertData();
        system("tput reset");
    } else if (line[0] == "q") {
        ret = 1;
    } else {
        system("tput reset");
        qWarning() << "Command " << line[0] << "not recognized.";
    }
    return ret;
}

void startEverything() {
    QFile annotations("/home/easylab1pedro/annotations.json");
    QFile projects("/home/easylab1pedro/projects.json");


    if (annotations.open(QFile::ReadOnly | QIODevice::Text) &&
            projects.open(QFile::ReadOnly | QIODevice::Text)) {
        if (annotations.size() > 0 && projects.size() > 0) {

            //deserializate

            auto jdataAnnotations = QString(annotations.readAll());
            auto jdataProjects = QString(projects.readAll());
            auto jdataAnnotationsJDoc = QJsonDocument::fromJson(jdataAnnotations.toUtf8());
            auto jdataProjectsJDoc = QJsonDocument::fromJson(jdataProjects.toUtf8());

            qData.deserializeAnnotations(jdataAnnotationsJDoc);
            qData.deserializeProjects(jdataProjectsJDoc);
            qData.updateReferences();

            qWarning() << "Everything has been loaded.";

        } else {
            // nothing to deserialiate
            qWarning() << "Fresh start.";
//            qData.procInput("test/test1","@Aa");
//            qData.procInput("test/test1","@Ab");
//            qData.procInput("test/test1","@Ac");
//            qData.procInput("test/test2","@Aa");
//            qData.procInput("test/test2","@Af");
//            qData.procInput("test/test3","@Gf");
        }
    } else {
        //no json files
        qWarning() << "No Json files.";
        return;
    }

    annotations.close();
    projects.close();

    while( initialSelection() == 0){}
    if (annotations.open(QFile::WriteOnly | QIODevice::Text) &&
            projects.open(QFile::WriteOnly | QIODevice::Text)) {
        annotations.write(qData.serializeAnnotations().toJson());
        projects.write(qData.serializeProjects().toJson());
    } else {
        qWarning() << "Couldn't save to file.";
    }
}


int main(int argc, char *argv[])
{
    startEverything();
    return EXIT_SUCCESS;
}
