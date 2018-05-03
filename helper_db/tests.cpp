#include "tests.h"

#ifdef _ENABLE_TESTS
#define TESTMSG(x) if(x) qDebug() << #x << "SUCCESS"; else qDebug() << #x << "FAILURE";

void initHelper(Helper& h) {
    h.procInput(test::data::test_prj1,test::data::ann_test1);
    h.procInput(test::data::test_prj1,test::data::ann_test2);
    h.procInput(test::data::test_prj1,test::data::ann_test3);
    h.procInput(test::data::test_prj2,test::data::ann_test2);
}

Helper& initHelper() {
    Helper h;
    h.procInput(test::data::test_prj1,test::data::ann_test1);
    h.procInput(test::data::test_prj1,test::data::ann_test2);
    h.procInput(test::data::test_prj1,test::data::ann_test3);
    h.procInput(test::data::test_prj2,test::data::ann_test2);
    return h;
}

bool test::testAnnotationSerialization() {
    Helper helper;
    initHelper(helper);

    auto a = helper.getAnnotation(test::data::ann_test1);
    auto a_json = a.toJson();
    qDebug() << "a_json:" << a_json;
    return !a_json.isEmpty(); //TODO - VALID IF EQUAL TO STRING
}

bool test::testAnnotationDeserialization() {
    Helper helper;
    initHelper(helper);
    auto a = helper.getAnnotation(test::data::ann_test1);
    auto a_json = a.toJson();

    Annotation b;
    b.fromJson(a_json);
    if (b.toJson() == a_json) {
        qDebug() << "OK" << "Annotation successfully serialized and deserialized";
    } else {
        qDebug() << "FAIL" << "Failed to serialized and/or deserialize annotation";
    }
    return !b.toJson().empty(); //TODO - VALID IF EQUAL TO STRING
}

bool test::testProjectSerialization() {
    Helper helper ;
    initHelper(helper);
    auto p1 = helper.getProject(test::data::test_prj1);
    auto p1_json = p1.toJson();
    qDebug() << "p1_json" << p1_json;
    return !p1_json.empty(); //TODO - VALID IF EQUAL TO STRING
}

bool test::testProjectDeserialization() {
    Helper helper ;
    initHelper(helper);
    auto p1 = helper.getProject(test::data::test_prj1);
    auto p1_json = p1.toJson();
    qDebug() << "p1_json" << p1_json;
    auto p2 = Project();
    p2.fromJson(p1_json);

    if (p2.toJson() == p1_json) {
        qDebug() << "OK: " << "Successfully serialized and deserialized Project";
    } else {
        qDebug() << "FAIL: " << "Failed to serialized and/or deserialize Project";

    }
    return !p1_json.empty() && !p2.toJson().empty() && (p2.toJson() == p1_json); //TODO - VALID IF EQUAL TO STRING
}

bool test::testSuite() {
    bool testAnnotationSerialization   = test::testAnnotationSerialization();
    bool testAnnotationDeserialization = test::testAnnotationDeserialization();
    bool testProjectSerialization      = test::testProjectSerialization();
    bool testProjectDeserialization    = test::testProjectDeserialization();

    TESTMSG(testAnnotationSerialization)
            TESTMSG(testAnnotationDeserialization)
            TESTMSG(testProjectSerialization)
            TESTMSG(testProjectDeserialization)
            return testAnnotationDeserialization &&
            testAnnotationSerialization &&
            testProjectDeserialization &&
            testProjectSerialization;
}

bool test::testHelperAnnotationSerialization()
{
    Helper h;
    initHelper(h);
    auto serialized = h.serializeAnnotations();
    qDebug() << serialized;
    return true;
}

bool test::testHelperProjectSerialization()
{
    Helper h;
    initHelper(h);
    auto serialized = h.serializeProjects();
    qDebug() << serialized;
    return true;
}

bool test::testFileSaving()
{
    //   Helper h = initHelper();
    Helper h;
    initHelper(h);
    QJsonDocument doc1 = h.serializeAnnotations();
    QJsonDocument doc2 = h.serializeProjects();

    auto f1json = doc1.toJson();
    auto f2json = doc2.toJson();

    QTemporaryFile file1;
    if (file1.open()) {
        file1.write(f1json.constData(),f1json.size());
    }
    auto name = file1.fileName();
    file1.close();

    QFile file2(name);
    if (file2.open(QFile::ReadOnly)) {
        qDebug() << file2.readAll();
    }
    file2.close();


    QTemporaryFile temp;
    if (temp.open()) {
        temp.write(f2json.constData(),f2json.size());
    }
    auto tempname = temp.fileName();
    temp.close();
    QFile f2(tempname);
    if (f2.open(QFile::ReadOnly)) {
        qDebug() << f2.readAll();
    }

    return true;
}

bool test::testDeserialization(char** argv)
{
    Helper h;
    QFile annotationsJsonFile(argv[1]);
    QFile projectsJsonFile(argv[2]);

    if(annotationsJsonFile.open(QFile::ReadOnly|QIODevice::Text)) {
        auto jdata = QString(annotationsJsonFile.readAll());
        QJsonDocument doc = QJsonDocument::fromJson(jdata.toUtf8());
        h.deserializeAnnotations(doc);
    }

    if(projectsJsonFile.open(QFile::ReadOnly)) {
        auto jdata = QString(projectsJsonFile.readAll());
        QJsonDocument doc = QJsonDocument::fromJson(jdata.toUtf8());
        h.deserializeProjects(doc);
    }
    auto annjsondoc = h.serializeAnnotations();
    auto prjjsondoc = h.serializeProjects();

    auto annstr = annjsondoc.toJson();
    auto prjstr = prjjsondoc.toJson();

    h.updateReferences();
    return true;
}
#endif
