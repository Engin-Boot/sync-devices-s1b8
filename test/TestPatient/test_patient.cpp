#include <iostream>
#include <gtest/gtest.h>
#include "../../Patient/Patient.cpp"

using namespace std;

TEST(CreatePatientObject, create_default_patient)
{
    string expected_name = "none";
    string expected_gender = "none";
    int expected_age = 0;
    string expected_procedure = "none";

    Patient default_patient;

    EXPECT_STREQ(expected_name.c_str(), default_patient.getName().c_str());
    EXPECT_STREQ(expected_gender.c_str(), default_patient.getGender().c_str());
    EXPECT_STREQ(expected_procedure.c_str(), default_patient.getProcedureName().c_str());
    EXPECT_EQ(expected_age, default_patient.getAge());
    EXPECT_FALSE(default_patient.getBusyStatus());
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
    EXPECT_FALSE(custom_patient.getBusyStatus());
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
