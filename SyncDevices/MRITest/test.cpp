#include "pch.h"
#include "../MRI/Menu.cpp"
#include "../MRI/PatientWrapper.cpp"
#include "../MRI/Procedure.cpp"
#include "../MRI/Publisher.cpp"
#include "../MRI/Subscription.cpp"
#include "../MRI/PatientCounterFileOperations.cpp"
#include "../MRI/inc/Patient.h"


TEST(MRI_PublishAndSetPatientDetails, TestPatientDetails) {

	subscribe();
	connectPublisher();
	
	Sleep(5000);

	temporaryPatientDetails.setName("Monty");
	temporaryPatientDetails.setGender("Male");
	temporaryPatientDetails.setAge(20);
	temporaryPatientDetails.setProcedureName("HeartSurgery");

	publishPatientDetails("Patient/Details");

	Sleep(5000);

	EXPECT_EQ(temporaryPatientDetails.getName(), originalPatientDetails.getName());
	EXPECT_EQ(temporaryPatientDetails.getAge(), originalPatientDetails.getAge());
	EXPECT_EQ(temporaryPatientDetails.getGender(), originalPatientDetails.getGender());
	EXPECT_EQ(temporaryPatientDetails.getProcedureName(), originalPatientDetails.getProcedureName());
 
}