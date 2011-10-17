#include "QueryLogSearchService.h"

#include <mining-manager/query-correction-submanager/QueryCorrectionSubmanager.h>
#include <util/singleton.h>

namespace sf1r
{

QueryLogSearchService::QueryLogSearchService()
{
}

QueryLogSearchService::~QueryLogSearchService()
{
}

bool QueryLogSearchService::getRefinedQuery(
    const std::string& collectionName,
    const UString& queryUString,
    UString& refinedQueryUString
)
{
    return QueryCorrectionSubmanager::getInstance().getRefinedQuery(
			collectionName, queryUString,
			refinedQueryUString);
}

QueryLogSearchService *QueryLogSearchService::instance()
{
    return ::izenelib::util::Singleton<QueryLogSearchService>::get();
}

}