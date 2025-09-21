#include <gtest/gtest.h>
using namespace ::testing;

#include <Work.h>

// [----------] 8 tests from AWorkObject
class AWorkObject : public Test
{
};

TEST_F(AWorkObject, DefaultsFunctionToNullObject)
{
    Work work;
    try
    {
        work.execute();
    }
    catch (...)
    {
        ASSERT_ANY_THROW("unable to execute function");
    }
}

TEST_F(AWorkObject, DefaultsFunctionToNullObjectWhenConstructedWithId)
{
    Work work(1);
    try
    {
        work.execute();
    }
    catch (...)
    {
        ASSERT_ANY_THROW("unable to execute function");
    }
}

TEST_F(AWorkObject, CanBeConstructedWithAnId)
{
    Work work(1);

    ASSERT_EQ(1, work.id());
}

TEST_F(AWorkObject, DefaultsIdTo0)
{
    Work work;

    ASSERT_EQ(0, work.id());
}

TEST_F(AWorkObject, DefaultsIdTo0WhenFunctionSpecified)
{
    Work work{[] {}};

    ASSERT_EQ(0, work.id());
}

TEST_F(AWorkObject, CanBeConstructedWithAFunctionAndId)
{
    Work work{[] {}, 1};

    ASSERT_EQ(1, work.id());
}

TEST_F(AWorkObject, ExecutesFunctionStored)
{
    bool wasExecuted{false};
    auto executeFunction = [&wasExecuted]()
    { wasExecuted = true; };

    Work work(executeFunction);

    work.execute();

    ASSERT_TRUE(wasExecuted);
}

TEST_F(AWorkObject, CanExecuteOnDataCapturedWithFunction)
{
    std::vector<std::string> data{"a", "b"};
    std::string result;

    auto callbackFunction = [&result](std::string s)
    {
        result.append(s);
    };

    auto executeFunction = [&data, callbackFunction]()
    {
        std::stringstream s;
        s << data[0] << data[1];
        callbackFunction(s.str());
    };

    Work work(executeFunction);
    work.execute();
    ASSERT_EQ("ab", result);
}