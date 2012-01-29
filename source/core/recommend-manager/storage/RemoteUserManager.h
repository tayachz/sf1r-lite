/**
 * @file RemoteUserManager.h
 * @author Jun Jiang
 * @date 2012-01-10
 */

#ifndef REMOTE_USER_MANAGER_H
#define REMOTE_USER_MANAGER_H

#include "UserManager.h"
#include "CassandraAdaptor.h"

#include <string>

namespace sf1r
{
struct User;

class RemoteUserManager : public UserManager
{
public:
    RemoteUserManager(
        const std::string& keyspace,
        const std::string& columnFamily,
        libcassandra::Cassandra* client
    );

    virtual bool addUser(const User& user);

    virtual bool updateUser(const User& user);

    virtual bool removeUser(const std::string& userId);

    virtual bool getUser(const std::string& userId, User& user);

private:
    CassandraAdaptor cassandra_;
};

} // namespace sf1r

#endif // REMOTE_USER_MANAGER_H
