/**
 * @file process/controllers/CollectionHandler.cpp
 * @author Ian Yang
 * @date Created <2011-01-25 18:40:12>
 */
#include <process/common/XmlConfigParser.h>
#include <process/common/CollectionManager.h>

#include <bundles/index/IndexSearchService.h>
#include <bundles/index/IndexTaskService.h>
#include <bundles/mining/MiningSearchService.h>
#include <bundles/recommend/RecommendTaskService.h>
#include <bundles/recommend/RecommendSearchService.h>

#include "CollectionHandler.h"
#include "DocumentsGetHandler.h"
#include "DocumentsSearchHandler.h"

#include <common/Keys.h>
#include <common/JobScheduler.h>

#include <boost/bind.hpp>

namespace sf1r
{

using driver::Keys;

using namespace izenelib::driver;
using namespace izenelib::osgi;

CollectionHandler::CollectionHandler(const string& collection)
        : collection_(collection)
        , TOP_K_NUM(4000)
        , indexSearchService_(0)
        , miningSearchService_(0)
        , recommendTaskService_(0)
        , recommendSearchService_(0)
{
}


CollectionHandler::~CollectionHandler()
{
}

void CollectionHandler::search(::izenelib::driver::Request& request, ::izenelib::driver::Response& response)
{
    DocumentsSearchHandler handler(request,response,*this);
    handler.search();
}

void CollectionHandler::get(::izenelib::driver::Request& request, ::izenelib::driver::Response& response)
{
    DocumentsGetHandler handler(request, response,*this);
    handler.get();
}

void CollectionHandler::similar_to(::izenelib::driver::Request& request, ::izenelib::driver::Response& response)
{
    DocumentsGetHandler handler(request, response,*this);
    handler.similar_to();
}

void CollectionHandler::duplicate_with(::izenelib::driver::Request& request, ::izenelib::driver::Response& response)
{
    DocumentsGetHandler handler(request, response,*this);
    handler.duplicate_with();
}

void CollectionHandler::similar_to_image(::izenelib::driver::Request& request, ::izenelib::driver::Response& response)
{
    DocumentsGetHandler handler(request, response,*this);
    handler.similar_to_image();
}

bool CollectionHandler::create(const std::string& collectionName, const ::izenelib::driver::Value& document)
{
    collection_ = collectionName;

    std::string bundleName = "IndexBundle-" + collection_;
    IndexTaskService* indexService = static_cast<IndexTaskService*>(
                                         CollectionManager::get()->getOSGILauncher().getService(bundleName, "IndexTaskService"));
    if (!indexService)
    {
        return false;
    }
    task_type task = boost::bind(&IndexTaskService::createDocument, indexService, document);
    JobScheduler::get()->addTask(task);
    return true;
}

bool CollectionHandler::update(const std::string& collectionName, const ::izenelib::driver::Value& document)
{
    collection_ = collectionName;
    std::string bundleName = "IndexBundle-" + collection_;
    IndexTaskService* indexService = static_cast<IndexTaskService*>(
                                         CollectionManager::get()->getOSGILauncher().getService(bundleName, "IndexTaskService"));
    if (!indexService)
    {
        return false;
    }
    task_type task = boost::bind(&IndexTaskService::updateDocument, indexService, document);
    JobScheduler::get()->addTask(task);
    return true;
}

bool CollectionHandler::destroy(const std::string& collectionName, const ::izenelib::driver::Value& document)
{
    collection_ = collectionName;
    std::string bundleName = "IndexBundle-" + collection_;
    IndexTaskService* indexService = static_cast<IndexTaskService*>(
                                         CollectionManager::get()->getOSGILauncher().getService(bundleName, "IndexTaskService"));
    if (!indexService)
    {
        return false;
    }
    task_type task = boost::bind(&IndexTaskService::destroyDocument, indexService, document);
    JobScheduler::get()->addTask(task);
    return true;
}

} // namespace sf1r
