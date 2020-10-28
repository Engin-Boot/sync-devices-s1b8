import unittest
from PythonClient.patient import Patient

class TestPatient(unittest.TestCase):

    def test_create_default_patient(self):
        p = Patient()
        self.assertEqual(p.getName(), "")
        self.assertEqual(p.getAge(), 0)
        self.assertEqual(p.getGender(), "")
        self.assertEqual(p.getProcedureName(), "")
        self.assertEqual(p.getConsumables(), "")
        self.assertEqual(p.getReportIds(), "")
        self.assertFalse(p.getBusyStatus())
    

    def test_create_patient(self):
        p = Patient("ABC", 30, "Male", "Cardiac")
        self.assertEqual(p.getName(), "ABC")
        self.assertEqual(p.getAge(), 30)
        self.assertEqual(p.getGender(), "Male")
        self.assertEqual(p.getProcedureName(), "Cardiac")
    

    def test_setters_and_getters(self):
        p = Patient()
        p.setId("ABC123")
        p.setName("ABC")
        p.setAge(25)
        p.setGender("Female")
        p.setProcedureName("Cardiac")
        p.setReportIds("ECG123")
        p.setConsumables("Catheter")
        p.setBusyStatus(1)

        self.assertEqual(p.getId(), "ABC123")
        self.assertEqual(p.getName(), "ABC")
        self.assertEqual(p.getAge(), 25)
        self.assertEqual(p.getGender(), "Female")
        self.assertEqual(p.getProcedureName(), "Cardiac")
        self.assertEqual(p.getReportIds(), "ECG123")
        self.assertEqual(p.getConsumables(), "Catheter")
        self.assertEqual(p.getBusyStatus(), 1)


    def test_add_multiple_consumables(self):
        p = Patient()
        p.addConsumables("Gloves")
        p.addConsumables("Mask")

        self.assertEqual(p.getConsumables(), "Gloves,Mask")
    
    def test_add_multiple_report_ids(self):
        p = Patient()
        p.addReportIds("ECG123")
        p.addReportIds("ECG124")

        self.assertEqual(p.getReportIds(), "ECG123,ECG124")
    

    def test_to_string_method(self):
        p = Patient()
        p.setName("ABC")
        p.setAge(25)
        p.setGender("Female")
        p.setProcedureName("Cardiac")
        p.setReportIds("ECG123")
        p.setConsumables("Catheter")

        expected_string = ";ABC;Female;25;Cardiac;Catheter;ECG123;0"
        self.assertEqual(p.toString(), expected_string)
    

    def test_equality_operator(self):
        p1 = Patient("ABC", 25, "Male", "Xray")
        p2 = Patient("ABC", 25, "Male", "Xray")
        p3 = Patient()

        self.assertTrue(p1 == p2)
        self.assertFalse(p2 == p3)


    def test_pateint_repr(self):
        p = Patient()
        p.setName("ABC")
        p.setAge(25)
        p.setGender("Female")
        p.setProcedureName("Cardiac")
        p.setReportIds("ECG123")
        p.setConsumables("Catheter")
        expected_string = ";ABC;Female;25;Cardiac;Catheter;ECG123;0"

        self.assertEqual(repr(p), expected_string)
