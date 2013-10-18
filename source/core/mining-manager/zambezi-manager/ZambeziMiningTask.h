/**
 * @file ZambeziMiningTask.h
 * @brief the mining task for zambezi inverted index.
 */

#ifndef SF1R_ZAMBEZI_MINING_TASK_H
#define SF1R_ZAMBEZI_MINING_TASK_H

#include "../MiningTask.h"
#include <ir/Zambezi/AttrScoreInvertedIndex.hpp>
#include <string>

namespace sf1r
{
class DocumentManager;
class ZambeziConfig;

class ZambeziMiningTask : public MiningTask
{
public:
    ZambeziMiningTask(
            const ZambeziConfig& config,
            DocumentManager& documentManager,
            izenelib::ir::Zambezi::AttrScoreInvertedIndex& indexer);

    virtual bool buildDocument(docid_t docID, const Document& doc);

    virtual bool preProcess(int64_t timestamp);

    virtual bool postProcess();

    virtual docid_t getLastDocId() { return startDocId_; }

private:
    const ZambeziConfig& config_;

    DocumentManager& documentManager_;

    izenelib::ir::Zambezi::AttrScoreInvertedIndex& indexer_;

    docid_t startDocId_;
};

} // namespace sf1r

#endif // SF1R_ZAMBEZI_MINING_TASK_H