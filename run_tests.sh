# Test Patient

exec ./build_and_runtest.sh TestPatient patient_test_coverage

# Unit Tests

exec ./build_and_runtest.sh UnitTests unit_test_coverage

# Integration Test

exec ./build_and_runtest.sh IntegrationTests integration_test_coverage
