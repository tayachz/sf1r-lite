#ifndef SF1R_MINING_SUFFIX_MATCHMANAGER_H_
#define SF1R_MINING_SUFFIX_MATCHMANAGER_H_

#include "SuffixMatchMiningTask.hpp"

#include <common/type_defs.h>
#include <am/succinct/fm-index/fm_index.hpp>
#include <query-manager/ActionItem.h>
#include <mining-manager/group-manager/GroupParam.h>
#include <common/ResultType.h>

#include <boost/shared_ptr.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace cma
{
class Analyzer;
class Knowledge;
}

namespace sf1r
{

class DocumentManager;
class FilterManager;
class FMIndexManager;
namespace faceted
{
    class GroupManager;
    class AttrManager;
}
class NumericPropertyTableBuilder;

class SuffixMatchManager
{
public:
    SuffixMatchManager(
            const std::string& homePath,
            const std::string& dicpath,
            boost::shared_ptr<DocumentManager>& document_manager,
            faceted::GroupManager* groupmanager,
            faceted::AttrManager* attrmanager,
            NumericPropertyTableBuilder* numeric_tablebuilder);

    ~SuffixMatchManager();
    void addFMIndexProperties(const std::vector<std::string>& property_list, int type, bool finished = false);
    void setGroupFilterProperties(std::vector<std::string>& property_list);
    void setAttrFilterProperties(std::vector<std::string>& property_list);
    void setDateFilterProperties(std::vector<std::string>& property_list);
    void setNumericFilterProperties(std::vector<std::string>& property_list, std::vector<int32_t>& amp_list);
    void buildCollection();
    void buildTokenizeDic();
    bool isStartFromLocalFM() const;

    size_t longestSuffixMatch(
            const izenelib::util::UString& pattern,
            std::vector<std::string> search_in_properties,
            size_t max_docs,
            std::vector<std::pair<double, uint32_t> >& res_list) const;

    size_t AllPossibleSuffixMatch(
            const izenelib::util::UString& pattern,
            std::vector<std::string> search_in_properties,
            size_t max_docs,
            const SearchingMode::SuffixMatchFilterMode& filter_mode,
            const std::vector<QueryFiltering::FilteringType>& filter_param,
            const faceted::GroupParam& group_param,
            std::vector<std::pair<double, uint32_t> >& res_list) const;

    MiningTask* getMiningTask();
    bool buildMiningTask();

private:
    typedef izenelib::am::succinct::fm_index::FMIndex<uint16_t> FMIndexType;
    typedef FMIndexType::MatchRangeListT  RangeListT;

    bool getAllFilterRangeFromGroupLable_(
            const faceted::GroupParam& group_param,
            std::vector<size_t>& prop_id_list,
            std::vector<RangeListT>& filter_range_list) const;
    bool getAllFilterRangeFromAttrLable_(
            const faceted::GroupParam& group_param,
            std::vector<size_t>& prop_id_list,
            std::vector<RangeListT>& filter_range_list) const;
    bool getAllFilterRangeFromFilterParam_(
            const std::vector<QueryFiltering::FilteringType>& filter_param,
            std::vector<size_t>& prop_id_list,
            std::vector<RangeListT>& filter_range_list) const;

    std::string data_root_path_;

    std::vector<std::string> group_property_list_;
    std::vector<std::string> attr_property_list_;
    std::set<std::string> numeric_property_list_;
    std::vector<std::string> date_property_list_;
    std::string tokenize_dicpath_;
    boost::shared_ptr<DocumentManager> document_manager_;
    size_t last_doc_id_;

    cma::Analyzer* analyzer_;
    cma::Knowledge* knowledge_;

    boost::shared_ptr<FMIndexManager> fmi_manager_;
    boost::shared_ptr<FilterManager> filter_manager_;

    MiningTask* suffixMatchTask_;

    typedef boost::shared_mutex MutexType;
    typedef boost::shared_lock<MutexType> ReadLock;
    typedef boost::unique_lock<MutexType> WriteLock;

    mutable MutexType mutex_;
};

}

#endif
