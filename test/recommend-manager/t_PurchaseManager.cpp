/// @file t_PurchaseManager.cpp
/// @brief test PurchaseManager in purchase operations
/// @author Jun Jiang
/// @date Created 2011-04-19
///

#include "PurchaseManagerTestFixture.h"
#include <recommend-manager/storage/RecommendStorageFactory.h>
#include <configuration-manager/CassandraStorageConfig.h>
#include <recommend-manager/storage/LocalPurchaseManager.h>
#include <recommend-manager/storage/RemotePurchaseManager.h>
#include <recommend-manager/storage/CassandraAdaptor.h>
#include <log-manager/CassandraConnection.h>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <string>

using namespace std;
using namespace sf1r;

namespace bfs = boost::filesystem;

namespace
{
const string TEST_DIR_STR = "recommend_test/t_PurchaseManager";
const string TEST_CASSANDRA_URL = "cassandra://localhost";
const string KEYSPACE_NAME = "test_recommend";
const string COLLECTION_NAME = "example";
}

BOOST_AUTO_TEST_SUITE(PurchaseManagerTest)

BOOST_FIXTURE_TEST_CASE(checkLocalPurchaseManager, PurchaseManagerTestFixture)
{
    bfs::remove_all(TEST_DIR_STR);
    bfs::create_directories(TEST_DIR_STR);

    CassandraStorageConfig config;
    RecommendStorageFactory factory(config, COLLECTION_NAME, TEST_DIR_STR);

    {
        BOOST_TEST_MESSAGE("1st add purchase...");

        boost::scoped_ptr<PurchaseManager> purchaseManager(factory.createPurchaseManager());
        BOOST_CHECK(dynamic_cast<LocalPurchaseManager*>(purchaseManager.get()) != NULL);
        setPurchaseManager(purchaseManager.get());

        addPurchaseItem("1", "20 10 40");
        addPurchaseItem("1", "10");
        addPurchaseItem("2", "20 30");
        addPurchaseItem("3", "20 30 20");

        addRandItem("1", 99);
        addRandItem("2", 100);
        addRandItem("3", 101);
        addRandItem("4", 1234);

        checkPurchaseManager();
    }

    {
        BOOST_TEST_MESSAGE("2nd add purchase...");

        boost::scoped_ptr<PurchaseManager> purchaseManager(factory.createPurchaseManager());
        setPurchaseManager(purchaseManager.get());

        checkPurchaseManager();

        addPurchaseItem("1", "40 50 60");
        addPurchaseItem("2", "40");
        addPurchaseItem("3", "30 40 50");
        addPurchaseItem("4", "20 30");

        checkPurchaseManager();
    }
}

BOOST_FIXTURE_TEST_CASE(checkRemotePurchaseManager, PurchaseManagerTestFixture)
{
    CassandraConnection& connection = CassandraConnection::instance();
    if (! connection.init(TEST_CASSANDRA_URL))
    {
        cerr << "warning: exit test case as failed to connect " << TEST_CASSANDRA_URL << endl;
        return;
    }

    CassandraStorageConfig config;
    config.enable = true;
    config.keyspace = KEYSPACE_NAME;
    RecommendStorageFactory factory(config, COLLECTION_NAME, TEST_DIR_STR);

    {
        libcassandra::Cassandra* client = connection.getCassandraClient(KEYSPACE_NAME);
        CassandraAdaptor adaptor(factory.getPurchaseColumnFamily(), client);
        adaptor.dropColumnFamily();
    }

    {
        BOOST_TEST_MESSAGE("1st add purchase...");

        boost::scoped_ptr<PurchaseManager> purchaseManager(factory.createPurchaseManager());
        BOOST_CHECK(dynamic_cast<RemotePurchaseManager*>(purchaseManager.get()) != NULL);
        setPurchaseManager(purchaseManager.get());


        addPurchaseItem("1", "20 10 40");
        addPurchaseItem("1", "10");
        addPurchaseItem("2", "20 30");
        addPurchaseItem("3", "20 30 20");

        addRandItem("1", 99);
        addRandItem("2", 100);
        addRandItem("3", 101);
        addRandItem("4", 1234);

        checkPurchaseManager();
    }

    {
        BOOST_TEST_MESSAGE("2nd add purchase...");

        boost::scoped_ptr<PurchaseManager> purchaseManager(factory.createPurchaseManager());
        setPurchaseManager(purchaseManager.get());

        checkPurchaseManager();

        addPurchaseItem("1", "40 50 60");
        addPurchaseItem("2", "40");
        addPurchaseItem("3", "30 40 50");
        addPurchaseItem("4", "20 30");

        checkPurchaseManager();
    }
}

BOOST_AUTO_TEST_CASE(checkCassandraNotConnect)
{
    CassandraConnection& connection = CassandraConnection::instance();
    const char* TEST_CASSANDRA_NOT_CONNECT_URL = "cassandra://localhost:9161";
    BOOST_CHECK(connection.init(TEST_CASSANDRA_NOT_CONNECT_URL) == false);

    CassandraStorageConfig config;
    config.enable = true;
    config.keyspace = KEYSPACE_NAME;
    RecommendStorageFactory factory(config, COLLECTION_NAME, TEST_DIR_STR);

    boost::scoped_ptr<PurchaseManager> purchaseManager(factory.createPurchaseManager());

    string userId = "aaa";
    std::vector<itemid_t> orderItemVec;
    orderItemVec.push_back(1);
    orderItemVec.push_back(2);

    BOOST_CHECK(purchaseManager->addPurchaseItem(userId, orderItemVec, NULL) == false);

    ItemIdSet itemIdSet;
    BOOST_CHECK(purchaseManager->getPurchaseItemSet(userId, itemIdSet) == false);
}

BOOST_AUTO_TEST_SUITE_END() 
