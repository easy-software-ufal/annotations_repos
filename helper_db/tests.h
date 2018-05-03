#ifndef TESTS_H
#define TESTS_H
#include "helper.h"
#include <QDebug>
#include <QTemporaryFile>


#ifdef _ENABLE_TESTS
namespace test {

namespace data  {
static const auto test_prj1 = QString("usr/test");
static const auto test_prj2 = QString("usr/test2");
static const auto ann_test1 = QString("@Test1");
static const auto ann_test2 = QString("@Test2");
static const auto ann_test3 = QString("@Test3");


static const char* json_saved_annotations= R"([
                                           {
                                           "annotation": "@Test1",
                                           "description": "",
                                           "framework": "",
                                           "used_at": [
                                           "usr/test"
                                           ]
                                           },
                                           {
                                           "annotation": "@Test2",
                                           "description": "",
                                           "framework": "",
                                           "used_at": [
                                           "usr/test",
                                           "usr/test2"
                                           ]
                                           },
                                           {
                                           "annotation": "@Test3",
                                           "description": "",
                                           "framework": "",
                                           "used_at": [
                                           "usr/test"
                                           ]
                                           }
                                           ])";


static const char* json_saved_projects= R"([
                                        {
                                        "annotations": [
                                        "@Test1",
                                        "@Test2",
                                        "@Test3"
                                        ],
                                        "project_id": "usr/test"
                                        },
                                        {
                                        "annotations": [
                                        "@Test2"
                                        ],
                                        "project_id": "usr/test2"
                                        }
                                        ])";


}

bool testSuite();
bool testAnnotationSerialization();
bool testAnnotationDeserialization();
bool testProjectSerialization();
bool testProjectDeserialization();
bool testHelperAnnotationSerialization();
bool testHelperAnnotationDeserialization();
bool testHelperProjectSerialization();
bool testHelperProjectDeserialization();
bool testFileSaving();
bool testDeserialization(char**);
}
#endif

#endif // TESTS_H
