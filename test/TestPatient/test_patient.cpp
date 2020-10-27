#include <iostream>
#include <gtest/gtest.h>
#include "../../Patient/Patient.cpp"

using namespace std;

TEST(CreatePatientObject, create_default_patient)
{
    string expected_name = "";
    string expected_gender = "";
    int expected_age = 0;
    string expected_procedure = "";

    Patient default_patient;

    EXPECT_STREQ(expected_name.c_str(), default_patient.getName().c_str());
    EXPECT_STREQ(expected_gender.c_str(), default_patient.getGender().c_str());
    EXPECT_STREQ(expected_procedure.c_str(), default_patient.getProcedureName().c_str());
    EXPECT_EQ(expected_age, default_patient.getAge());
}


TEST(CreatePatientObject, create_custom_patient)
{
    string expected_name = "XYZ";
    string expected_gender = "Male";
    int expected_age = 20;
    string expected_procedure = "Cardiac";

    Patient custom_patient("XYZ", "Male", 20, "Cardiac");

    EXPECT_STREQ(expected_name.c_str(), custom_patient.getName().c_str());
    EXPECT_STREQ(expected_gender.c_str(), custom_patient.getGender().c_str());
    EXPECT_STREQ(expected_procedure.c_str(), custom_patient.getProcedureName().c_str());
    EXPECT_EQ(expected_age, custom_patient.getAge());
}


TEST(APITest, test_getters_and_setters)
{
    Patient patient;
    patient.setName("ABC");
    patient.setAge(20);
    patient.setGender("Male");
    patient.setProcedureName("Cardiac");
    patient.setBusyStatus(1);

    EXPECT_STREQ("ABC", patient.getName().c_str());
    EXPECT_STREQ("Male", patient.getGender().c_str());
    EXPECT_STREQ("Cardiac", patient.getProcedureName().c_str());
    EXPECT_EQ(20, patient.getAge());
    EXPECT_EQ(1,patient.getBusyStatus());
}

TEST(APITest, test_to_string_method)
{
    Patient patient;
    patient.setName("ABC");
    patient.setAge(20);
    patient.setGender("Male");
    patient.setProcedureName("Cardiac");
    string expected_string = "0;ABC;Male;20;Cardiac;;;0";
    EXPECT_STREQ(expected_string.c_str(), patient.toString().c_str());
}

TEST(APITest, test_add_single_report_id)
{
    Patient patient;
    EXPECT_STREQ("", patient.getReportIds().c_str());
    patient.addReportId("12");
    EXPECT_STREQ("12", patient.getReportIds().c_str());
}

TEST(APITest, test_add_single_consumable)
{
    Patient patient;
    EXPECT_STREQ("", patient.getConsumables().c_str());
    patient.addConsumable("Gloves");
    EXPECT_STREQ("Gloves", patient.getConsumables().c_str());
}

TEST(APITest, test_add_multiple_report_ids)
{
    Patient patient;
    patient.addReportId("11");
    EXPECT_STREQ("11", patient.getReportIds().c_str());
    patient.addReportId("12");
    EXPECT_STREQ("11,12", patient.getReportIds().c_str());
    patient.addReportId("13");
    EXPECT_STREQ("11,12,13", patient.getReportIds().c_str());
}

TEST(APITest, test_add_multiple_consumables)
{
    Patient patient;
    patient.addConsumable("Gloves");
    EXPECT_STREQ("Gloves", patient.getConsumables().c_str());
    patient.addConsumable("Mask");
    EXPECT_STREQ("Gloves,Mask", patient.getConsumables().c_str());
}


TEST(Operator_Test, Assignment_Operator)
{
    Patient p1("ABC", "Male", 20, "Cardiac");
    Patient p2;
    p2 = p1;
    EXPECT_STREQ(p1.getName().c_str(), p2.getName().c_str());
    EXPECT_STREQ(p1.getGender().c_str(), p2.getGender().c_str());
    EXPECT_STREQ(p1.getProcedureName().c_str(), p2.getProcedureName().c_str());
    EXPECT_EQ(p1.getAge(), p2.getAge());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
