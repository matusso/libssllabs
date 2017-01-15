#include <gtest/gtest.h>
#include "ssllabs_gtest.h"
#include "../include/ssllabs/ssllabs.h"

TEST(BasicInfo__Test, BasicInfo__Test_CorrectReturnValue) {
    ssllabs::SSLlabs ssllabsObject;
    ssllabs::labsReport_t report;

    ssllabsObject.analyze("www.google.com", report);
    EXPECT_EQ("www.google.com", report.Host);
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}