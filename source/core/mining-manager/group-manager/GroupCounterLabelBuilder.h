///
/// @file GroupCounterLabelBuilder.h
/// @brief create instance of GroupFilter
/// @author Jun Jiang <jun.jiang@izenesoft.com>
/// @date Created 2011-09-05
///

#ifndef SF1R_GROUP_COUNTER_LABEL_BUILDER_H
#define SF1R_GROUP_COUNTER_LABEL_BUILDER_H

#include "GroupParam.h"
#include <common/type_defs.h> // PropertyDataType

#include <vector>
#include <string>

namespace sf1r
{
class GroupConfig;
class NumericPropertyTableBuilder;
}

NS_FACETED_BEGIN

class GroupManager;
class GroupCounter;
class GroupLabel;
class PropSharedLockSet;

class GroupCounterLabelBuilder
{
public:
    GroupCounterLabelBuilder(
        const std::vector<GroupConfig>& groupConfigs,
        const GroupManager* groupManager,
        NumericPropertyTableBuilder* numericTableBuilder);

    GroupCounter* createGroupCounter(
        const GroupPropParam& groupPropParam,
        PropSharedLockSet& sharedLockSet);

    GroupLabel* createGroupLabel(
        const GroupParam::GroupLabelParam& labelParam,
        PropSharedLockSet& sharedLockSet);

private:
    PropertyDataType getPropertyType_(const std::string& prop) const;
    const GroupConfig* getGroupConfig_(const std::string& prop) const;

    GroupCounter* createValueCounter_(
        const GroupPropParam& groupPropParam,
        PropSharedLockSet& sharedLockSet,
        GroupCounter* subCounter = NULL) const;

    GroupCounter* createNumericRangeCounter_(const std::string& prop) const;

    GroupCounter* createStringCounter_(
        const std::string& prop,
        PropSharedLockSet& sharedLockSet,
        GroupCounter* subCounter) const;

    GroupCounter* createNumericCounter_(
        const std::string& prop,
        GroupCounter* subCounter) const;

    GroupCounter* createDateCounter_(
        const std::string& prop,
        const std::string& unit,
        PropSharedLockSet& sharedLockSet,
        GroupCounter* subCounter) const;

    GroupLabel* createStringLabel_(
        const GroupParam::GroupLabelParam& labelParam,
        PropSharedLockSet& sharedLockSet) const;

    GroupLabel* createNumericRangeLabel_(const GroupParam::GroupLabelParam& labelParam) const;
    GroupLabel* createNumericLabel_(const GroupParam::GroupLabelParam& labelParam) const;
    GroupLabel* createRangeLabel_(const GroupParam::GroupLabelParam& labelParam) const;

    GroupLabel* createDateLabel_(
        const GroupParam::GroupLabelParam& labelParam,
        PropSharedLockSet& sharedLockSet) const;

private:
    const std::vector<GroupConfig>& groupConfigs_;
    const GroupManager* groupManager_;
    NumericPropertyTableBuilder* numericTableBuilder_;
};

NS_FACETED_END

#endif
