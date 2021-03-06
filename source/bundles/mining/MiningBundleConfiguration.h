#ifndef MINING_BUNDLE_CONFIGURATION_H
#define MINING_BUNDLE_CONFIGURATION_H

#include <configuration-manager/MiningConfig.h>
#include <configuration-manager/MiningSchema.h>
#include <configuration-manager/CollectionPath.h>
#include <configuration-manager/PropertyConfig.h>

#include <util/osgi/BundleConfiguration.h>

namespace sf1r
{
class MiningBundleConfiguration : public ::izenelib::osgi::BundleConfiguration
{
public:
    MiningBundleConfiguration(const std::string& collectionName);

    std::string collectionName_;

    // <MiningBundle><Schema>
    bool isSchemaEnable_;

    bool isMasterAggregator_;

    CollectionPath collPath_;

    static std::string system_resource_path_;

    static std::string system_working_path_;

    std::vector<std::string> collectionDataDirectories_;

    DocumentSchema documentSchema_;

    MiningConfig mining_config_;

    MiningSchema mining_schema_;
};
}

#endif
