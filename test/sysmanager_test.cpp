#include <gtest/gtest.h>
#include <base/manager.hpp>

class sysmanager_test : public ::testing::Test {
public:
	sysmanager_test() { }
	virtual ~sysmanager_test() { }

	void SetUp() {
		manager = cossb_system_manager;
	}

	void TearDown() {
		manager->destroy();
	}

protected:
	cossb::manager::system_manager* manager = nullptr;
};

TEST_F(sysmanager_test, instance) { EXPECT_NE(nullptr, cossb_system_manager); }
TEST_F(sysmanager_test, setup) { EXPECT_EQ(false, cossb_system_manager->setup(nullptr)); }
